#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <iostream>
#include <cstdio>
#include <cstring>
#include "ifile.hpp"

class BaseFile : public IFile {
    private:
	FILE* file;
	char mode[4];

    public:
	//Конструкторы
	BaseFile(); //Поу молчанию
	BaseFile(const char* filename, const char* mode); //Открывает файл
	BaseFile(FILE* existing_file); //С готовым указателем

	//Деструктор
	virtual ~BaseFile();

	//Прочие методы
	bool is_open() const; //Открыт ли файл
	bool can_read() const; //Можно ли считать данные
	bool can_write() const; //Можно ли записать данные

	size_t write_raw(const void* buf, size_t n_bytes); //Записывает данные
	size_t read_raw(void* buf, size_t max_bytes); //Читает данные

	long tell() const; //Возращает сдвиг файла
	bool seek(long offset); //Устанавливает сдвиг файла

	virtual size_t read(void* buf, size_t max_bytes) { return read_raw(buf, max_bytes); }
	virtual size_t write(const void* buf, size_t n_bytes) { return write_raw(buf, n_bytes); }

    private:
	//Для копирования
	void copy_mode(const char* src_mode);

	//Запрет другого копирования
	BaseFile(const BaseFile&) = delete;
	BaseFile& operator=(const BaseFile&) = delete;
};

class Base32File : public BaseFile {
    private:
	static const char DEF_ALPH[33]; //Алфавит по умолчанию
	char alphabet[33]; //Алфавит

	int code_buff; //Накопленные биты
	int code_cou; //Сколько бит накоплено

	int decode_buff; //Накопленные биты
	int decode_cou; //Сколько бит накоплено

	//Ищет номер символа
	int char_to_value(char c) const;

    public:
	//Конструкторы
	Base32File() : BaseFile(), code_buff(0), code_cou(0), decode_buff(0), decode_cou(0) {
	    strcpy(alphabet, DEF_ALPH);
	}	

	Base32File(const char* filename, const char* mode) : BaseFile(filename, mode), code_buff(0), code_cou(0), decode_buff(0),
	decode_cou(0) {
	    strcpy(alphabet, DEF_ALPH); //Копирует
	}

	Base32File(const char* filename, const char* mode, const char* custom_alph) : BaseFile(filename, mode),
	code_buff(0), code_cou(0), decode_buff(0), decode_cou(0) {
	    strncpy(alphabet, custom_alph, 32); //Копирует с ограничением
	    alphabet[32] = '\0';
	}

	size_t write(const void* bu, size_t n_bytes);
	size_t read(void* buf, size_t max_bytes);

	//Для сброса состояния, если нужно записать файл с нуля
	void reset_encode() { code_buff = 0; code_cou = 0; }
	void reset_decode() { decode_buff = 0; decode_cou = 0; }
	void reset() { reset_encode(); reset_decode(); }

	//Для завершения кодировния
	bool flush_encode();
};

class RleFile : public BaseFile {
    private:
	//Буферы для хранения данных
	static const int BUFFER_SIZE = 1014;

	//Для сжатия (запись)
	unsigned char encode_buffer[BUFFER_SIZE]; //Накопление данных 
	int encode_filled; //Сколько уже накоплено

	//Для распаковки (чтение)
	unsigned char decode_buffer[BUFFER_SIZE]; //Для распаковки данных
	int decode_pos; //Позиция чтения
	int decode_filled; //Сколько байт в буфере

	//Чтобы читать последовательно
	unsigned char current_byte; //Текущий байт
	unsigned char current_cou; //Сколько раз его над повторять
	bool has_current; //Есть ли текущий блок

	//Методы
	void compress_block(const unsigned char* input, size_t input_size); //Сжимает данные
	void decompress_block(); //Разжимает

    public:
	//Конструкторы
	RleFile();
	RleFile(const char* filename, const char* mode);
	RleFile(FILE* existing_file);

	//Деструктор
	~RleFile();

	//Другие методы
	size_t write(const void* buf, size_t n_bytes);
	size_t read(void* buf, size_t max_bytes);

	void reset();	

	void flush();
};


class Base32File2 : public IFile {
    private:
	IFile* file;
	char alphabet[33];
	bool owner;
	int code_buf;
	int code_cou;
	int decode_buf;
	int decode_cou;
	int char_to_value(char c) const;
    public:
	//Конструктор
	Base32File2(IFile* f) : file(f), code_buf(0), code_cou(0), decode_buf(0), decode_cou(0), owner(true) {
	    strcpy(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
	    std::cout << "Constructor Base32File2" << std::endl;
	} 

	//Другой конструктор
	Base32File2(IFile* f, bool take_o) : file(f), code_buf(0), code_cou(0), decode_buf(0), decode_cou(0), owner(take_o) {
            strcpy(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
            std::cout << "Constructor Base32File2" << std::endl;
        }	

	//Деструктор
	virtual ~Base32File2() {
	    std::cout << "Destructor Base32File2" << std::endl;
	    if (owner and file) {
		delete file;
		file = nullptr;
	    }
	}

	bool can_read() const {
	    return file ? file->can_read() : false;
	}

	bool can_write() const {
	    return file ? file->can_write() : false;
	}

	size_t read(void* buf, size_t max_bytes);
	size_t write(const void* buf, size_t n_bytes);

	long tell() const {
	    return file ? file->tell() : -1;
	}

	bool seek(long offset) {
	    return file ? file->seek(offset) : false;
	}

	void flush_encode();
};


class RleFile2 : public IFile {
    private:
	IFile* file;
	bool owner;
	static const int BUFFER_SIZE = 1024;
	unsigned char encode_buffer[BUFFER_SIZE];
	int encode_filled;
	unsigned char decode_buffer[BUFFER_SIZE];
	int decode_pos;
	int decode_filled;
	void compress_block(const unsigned char* input, size_t input_size);
	void decompress_block();

    public:
	//Конструктор
	RleFile2(IFile* f) : file(f), owner(true), encode_filled(0), decode_pos(0), decode_filled(0) {
	    std::cout << "Constructor RleFile2" << std::endl;
	}

	//Другой конструктор
	RleFile2(IFile*f, bool take_o) : file(f), owner(take_o), encode_filled(0), decode_pos(0), decode_filled(0) {
            std::cout << "Constructor RleFile2" << std::endl;
        }

	//Деструктор
	virtual ~RleFile2() {
	    std::cout << "Destructor RleFile2" << std::endl;
	    if (owner and file) {
		delete file;
		file = nullptr;
	    }
	}

	bool can_read() const {
	    return file ? file->can_read() : false;
	}

	bool can_write() const {
	    return file ? file->can_write() : false;
	}

	size_t read(void* buf, size_t max_bytes);
	size_t write(const void* buf, size_t n_bytes);

	long tell() const {
	    return file ? file->tell() : -1;
	}

	bool seek(long offset) {
	    return file ? file->seek(offset) : false;
	}

	void flush();
};



#endif


















































