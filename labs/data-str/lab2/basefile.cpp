#include "basefile.hpp"
#include <cstring>
#include <cstdio>

//Конструктор по умолчанию
BaseFile::BaseFile() : file(nullptr) {
    mode[0] = '\0';
    std::cout << "Constructor Создан пустой обект" << std::endl;
}

//Метод для копирования
void BaseFile::copy_mode(const char* src_mode) {
    if (src_mode) {
	int i = 0;
	while (i < 3 and src_mode[i] != '\0') {
	    mode[i] = src_mode[i];
	    i++;
	}
	mode[i] = '\0';
    } else {
	mode[0] = '\0';
    }
}

//Второй конструктр
BaseFile::BaseFile(const char* filename, const char* mode) { 
    std::cout << "Constructor Октрывается файл " << filename << " в режиме " << mode << std::endl;

    file = fopen(filename, mode);
    copy_mode(mode);
}

//Третий конструктор
BaseFile::BaseFile(FILE* existing_file) : file(existing_file) {
    std::cout << "Constructor Создан объект на основе FILE" << std::endl;

    mode[0] = '?';
    mode[1] = '\0';
}

//Деструтор
BaseFile::~BaseFile() {
    if (file) {
	std::cout << "Destructor Файл закрыт" << std::endl;
	fclose(file);
	file = nullptr;
    } else {
	std::cout << "Ничего не открыто" << std::endl;
    }
}
//В деструкторе нужно щакрыть файл, тк класс обладает ресурсом и его надо освободить 

//Открыт ли файл
bool BaseFile::is_open() const {
    return file != nullptr;
}

//Можно ли читать
bool BaseFile::can_read() const {
    if (!file) return false;

    for (int i = 0; mode[i] != '\0'; i++) {
	if (mode[i] == 'r') return true;
    }

    return false;
}

//Можно ли писать
bool BaseFile::can_write() const {
    if (!file) return false;

    for (int i = 0; mode[i] != '\0'; i++) {
	if (mode[i] == 'w' or mode[i] == 'a' or mode[i] == '+') return true;
    }

    return false;
}

//Запись данных
size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!file or !can_write()) {
	std::cout << "Ошибка: файл закрыт или недоступен для записи" << std::endl;
	return 0;
    }

    size_t written = fwrite(buf, 1, n_bytes, file); 

    return written;
}

//Чтение данных
size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!file or !can_read()) {
	std::cout << "Ошибка: файл закрыт или недоступен для чтения" << std::endl;
        return 0;
    }

    size_t read = fread(buf, 1, max_bytes, file);

    return read;
}

//Позиция в файле
long BaseFile::tell() const {
    if (!file) {
	std::cout << "Ошибка: файл закрыт" << std::endl;
	return -1;
    }

    long pos = ftell(file);
    std::cout << "Текущая позиция: " << pos << std::endl;
    return pos;
}

//Перемещение по файлу
bool BaseFile::seek(long offset) {
    if (!file) {
	std::cout << "Ошибка: файл закрыт" << std::endl;
        return false;
    }

    int res = fseek(file, offset, SEEK_SET); 

    if (res == 0) {
	std::cout << "Позиция: " << offset << std::endl;
	return true;
    } else {
	std::cout << "Не удалось переместиться" << std::endl;
	return false;
    }
}



//Для Base32File

const char Base32File::DEF_ALPH[33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";

//Преобразование символа в число
int Base32File::char_to_value(char c) const {
    if (c >= 'A' and c <= 'Z') {
	return c - 'A';
    } else if (c >= '1' and c <= '6') {
	return 26 + (c - '1');
    } else {
	return -1;
    }
}

//Завершение клдирования
bool Base32File::flush_encode() {
    if (code_cou > 0) {
	int index = (code_buff << (5-code_cou)) & 0x1F;
	char encoded_char = alphabet[index];

	size_t written = BaseFile::write(&encoded_char, 1);
	if (written != 1) {
	    return false;
	}

	code_buff = 0;
	code_cou = 0;
    }
    return true;
}

//Запись с кодированием
size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!is_open() or !can_write()) {
	std::cout << "Ошибка - файл не открыт" << std::endl;
	return 0;
    }

    const unsigned char* raw_data = (const unsigned char*)buf;
    size_t bytes = 0;

    for (size_t i = 0; i < n_bytes; i++) {
	code_buff = (code_buff << 8) | raw_data[i];
	code_cou += 8;

	while (code_cou >= 5) {
	    int ind = (code_buff >> (code_cou - 5)) & 0x1F;
	    char encoded_char = alphabet[ind];

	    size_t written = BaseFile::write(&encoded_char, 1);
	    if (written != 1) {
		return bytes;
	    }

	    code_cou -= 5;
	}

	bytes++;
    }

    return bytes;
}

//Чтение с декодированием
size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!is_open() or !can_read()) {
	std::cout << "Ошибка - файл не открыт" << std::endl;
	return 0;
    }

    unsigned char* output = (unsigned char*)buf;
    size_t bytes = 0;

    while (bytes < max_bytes) {
	while (decode_cou < 8) {
	    char c;
	    size_t read = BaseFile::read(&c, 1);
	    if (read != 1) {
		return bytes;
	    }

	    //Преобразует символ в число
	    int value = char_to_value(c);
	    if (value == -1) {
		std::cout << "Неверный символ" << std::endl;
		continue;
	    }

	    decode_buff = (decode_buff << 5) | value;
	    decode_cou += 5;
	}

	//Извлекает полный байт
	output[bytes++] = (decode_buff >> (decode_cou - 8)) & 0xFF;
	decode_cou -= 8;
    }

    return bytes;
}



//Для RleFile

//Конструктор
RleFile::RleFile() : BaseFile(), encode_filled(0), decode_pos(0), decode_filled(0), current_byte(0), current_cou(0), 
has_current(false) {
    std::cout << "Constructor RleFile по умолчанию" << std::endl;
}

//Второй конструктор
RleFile::RleFile(const char* filename, const char* mode) : BaseFile(filename, mode), encode_filled(0), decode_pos(0),
decode_filled(0), current_byte(0), current_cou(0), has_current(false) {
    std::cout << "Constructor RleFile с параметрами" << std::endl;
}

//Третий конструктор
RleFile::RleFile(FILE* existing_file) : BaseFile(existing_file), encode_filled(0), decode_pos(0), decode_filled(0), 
current_byte(0), current_cou(0), has_current(false) {
    std::cout << "Constructor RleFile с FILE" << std::endl;
}

//Деструктор
RleFile::~RleFile() {
    std::cout << "Destructor RleFile" << std::endl;
}

//Сжаьие блока
void RleFile::compress_block(const unsigned char* input, size_t input_size) {
    size_t in_pos = 0; //Позиция входных данных

    //Пока не обработаны все данные и есть место в буфере 
    while (in_pos < input_size and encode_filled < BUFFER_SIZE - 1) {
	unsigned char current = input[in_pos];
	size_t len = 1; //Длина последовательности

	//Сколько раз подряд встречается этот байт
	while (in_pos + len < input_size and input[in_pos + len] == current and len < 255) {
	    len++;
	}

	encode_buffer[encode_filled++] = len;
	encode_buffer[encode_filled++] = current;

	in_pos += len; //К следующей группе
    }   
}

//Распаковка блока
void RleFile::decompress_block() {
    unsigned char comp[BUFFER_SIZE]; //Буфер данных

    size_t comp_size = BaseFile::read_raw(comp, BUFFER_SIZE); //Данные читаются из файла

    if (comp_size == 0) {
	decode_filled = 0;
	return;
    }

    size_t in_pos = 0;
    decode_filled = 0;

    while (in_pos < comp_size and decode_filled < BUFFER_SIZE) { //Распаковка всех данных
	unsigned char len = comp[in_pos++]; //Длина
	unsigned char value = comp[in_pos++]; //Байт

	for (int i = 0; i < len and decode_filled < BUFFER_SIZE; i++) {
	    decode_buffer[decode_filled++] = value;
	}
    } 

    decode_pos = 0; //Читаем буфер с начала
}

//Ззапись со сжатием
size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!is_open() or !can_write()) {
	std::cout << "Ошибка - файл не открыт" << std::endl;
	return 0;
    }

    const unsigned char* data = (const unsigned char*)buf;
    size_t bytes = 0;

    //Обработка входных данных
    while (bytes < n_bytes) {
	if (encode_filled >= BUFFER_SIZE - 2) {
	    flush();
	}

	size_t to_process = n_bytes - bytes;
	if (to_process > (BUFFER_SIZE-encode_filled) / 2) {
	    to_process = (BUFFER_SIZE-encode_filled) / 2;
	}
	compress_block(data + bytes, to_process);
	bytes += to_process;
    }

    return bytes;
}

//Чтение с распаковкой
size_t RleFile::read(void* buf, size_t max_bytes) {
    if  (!is_open() or !can_read()) {
        std::cout << "Ошибка - файл не открыт" << std::endl;
        return 0;
    }

    unsigned char* output = (unsigned char*)buf;
    size_t bytes = 0;

    //Пока не прочитали то, что просили
    while (bytes < max_bytes) {
	if (decode_pos < decode_filled) {
	    size_t cou = decode_filled - decode_pos; //Осталось в буфере
	    size_t to_copy = max_bytes - bytes; //Можно скопировать
	    if (to_copy > cou) {
		to_copy = cou;
	    }

	    for (size_t i = 0; i < to_copy; i++) {
		output[bytes + i] = decode_buffer[decode_pos + i];
	    }

	    decode_pos += to_copy;
	    bytes += to_copy;
	} else {
	    decompress_block();
	    if (decode_filled == 0) {
		break;
	    }
	}
    }

    return bytes;
}

//Для сброса 
void RleFile::flush() {
    if (encode_filled > 0) {
	BaseFile::write_raw(encode_buffer, encode_filled);
	encode_filled = 0;
    }
}



//Для Base32File2
int Base32File2::char_to_value(char c) const {
    if (c >= 'A' and c <= 'Z') {
	return c - 'A';
    } else if (c >= '1' and c <= '6') {
	return 26 + (c - '1');
    }
    return -1;
}

void Base32File2::flush_encode() {
    if (code_cou > 0) {
	int index = (code_buf << (5-code_cou)) & 0x1F;
	char encoded_char = alphabet[index];

	file->write(&encoded_char, 1);

	code_buf = 0;
	code_cou = 0;
    }
}

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    if (!file or !file->can_write()) {
	std::cout << "Ошибка записи" << std::endl;
	return 0;
    }

    const unsigned char* data = (const unsigned char*)buf;
    size_t bytes = 0;

    for (size_t i = 0; i < n_bytes; i++) {
	code_buf = (code_buf << 8) | data[i];
	code_cou += 8;

	while (code_cou >= 5) {
	    int index = (code_buf >> (code_cou - 5)) & 0x1F;
	    char encoded_char = alphabet[index];

	    file->write(&encoded_char, 1);
	    code_cou -= 5;
	}
	bytes++;
    }
    return bytes;
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    if (!file or !file->can_read()) {
	std::cout << "Ошибка чтения" << std::endl;
	return 0;
    }

    unsigned char* output = (unsigned char*)buf;
    size_t bytes = 0;

    while (bytes < max_bytes) {
	while (decode_cou < 8) {
	    char c;
	    if (file->read(&c, 1) != 1) {
		return bytes;
	    }

	    int value = char_to_value(c);
	    if (value == -1) {
		std::cout << "Неверный символ" << std::endl;
		continue;
	    }

	    decode_buf = (decode_buf << 5) | value;
	    decode_cou += 5;
	}
	output[bytes++] = (decode_buf >> (decode_cou - 8)) & 0xFF;
	decode_cou -= 8;
    }
    return bytes;
}



//Для RleFile2

void RleFile2::compress_block(const unsigned char* input, size_t input_size) {
    size_t in_pos = 0;

    while (in_pos < input_size and encode_filled < BUFFER_SIZE - 2) {
        unsigned char current = input[in_pos];
        size_t len = 1;

        while (in_pos + len < input_size and input[in_pos + len] == current and len < 255) {
            len++;
        }

        encode_buffer[encode_filled++] = len;
        encode_buffer[encode_filled++] = current;

        in_pos += len;
    }
}

void RleFile2::decompress_block() {
    unsigned char comp[BUFFER_SIZE];
    size_t comp_size = file->read(comp, BUFFER_SIZE);

    if (comp_size == 0) {
        decode_filled = 0;
        return;
    }

    size_t in_pos = 0;
    decode_filled = 0;

    while (in_pos < comp_size and decode_filled < BUFFER_SIZE) {
        unsigned char len = comp[in_pos++];
        unsigned char value = comp[in_pos++];

        for (int i = 0; i < len and decode_filled < BUFFER_SIZE; i++) {
            decode_buffer[decode_filled++] = value;
        }
    }
    decode_pos = 0;
}

void RleFile2::flush() {
    if (encode_filled > 0) {
        file->write(encode_buffer, encode_filled);
        encode_filled = 0;
    }
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (!file or !file->can_write()) {
        std::cout << "Ошибка - файл не открыт" << std::endl;
        return 0;
    }

    const unsigned char* data = (const unsigned char*)buf;
    size_t bytes = 0;

    //Обработка входных данных
    while (bytes < n_bytes) {
        if (encode_filled >= BUFFER_SIZE - 2) {
            flush();
        }

        size_t to_process = n_bytes - bytes;
        if (to_process > (BUFFER_SIZE-encode_filled) / 2) {
            to_process = (BUFFER_SIZE-encode_filled) / 2;
        }
        compress_block(data + bytes, to_process);
        bytes += to_process;
    }

    flush();

    return bytes;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    if  (!file or !file->can_read()) {
        std::cout << "Ошибка - файл не открыт" << std::endl;
        return 0;
    }

    unsigned char* output = (unsigned char*)buf;
    size_t bytes = 0;

    //Пока не прочитали то, что просили
    while (bytes < max_bytes) {
        if (decode_pos < decode_filled) {
            size_t cou = decode_filled - decode_pos; //Осталось в буфере
            size_t to_copy = max_bytes - bytes; //Можно скопировать
            if (to_copy > cou) {
                to_copy = cou;
            }

            for (size_t i = 0; i < to_copy; i++) {
                output[bytes + i] = decode_buffer[decode_pos + i];
            }
            decode_pos += to_copy;
            bytes += to_copy;
        } else {
            decompress_block();
            if (decode_filled == 0) {
                break;
            }
        }
    }

    return bytes;
}



























































































