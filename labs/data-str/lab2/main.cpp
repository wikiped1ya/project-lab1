#include <iostream>
#include <cstring>
#include "../lab1/src/my_string.hpp"
#include "basefile.hpp"

//Для задания 2.5
void write_int(IFile &file, int n) {
    if (n < 0) {
        file.write("-", 1);
        n = -n;
    }

    char digits[20];
    int cou = 0;

    while (n > 0) {
        digits[cou++] = '0' + (n%10);
        n /= 10;
    }

    for (int i = cou-1; i >=0; i--) {
        file.write(&digits[i], 1);
    }

    file.write("\n", 1);
}

int main() {
    //Задание 1ю1
    {
	MyString ar[3] = {MyString("First"), MyString("Second"), MyString("Third")};

	std::cout << "Элементы массива MyString:" << std::endl;
	for (int i = 0; i < 3; i++) {
	    ar[i].print();
	}

	std::cout << std::endl;
    }

    {
	MyString ar[5] = {MyString("First"), MyString("Second"), MyString("Third")};

	std::cout << "Элементы массива MyString:" << std::endl;
        for (int i = 0; i < 5; i++) {
            ar[i].print();
        }

	std::cout << std::endl;
    }

    //Последние два значения были созданы конструктором по умолчанию - пустая строка. В моем случае в списке
    //инициализаторов может быть сама строка(явный вызово конструктора), тоже строка, но с неявным вызовом 
    //конструктора или же пустая строка. А в общем случае - вызывается конструкторс параметрами, или конструктор
    //копирования другого класса, или конструктор по умолчанию, может быть неявное преобразование к нужному типу

    //Задание 1.2
    {
	MyString* arPtr[3];
	arPtr[0] = new MyString("First ptr");
	arPtr[1] = new MyString("Second ptr");
 	arPtr[2] = new MyString("Third ptr");

	std::cout << "Элементы через указатели:" << std::endl;
	for (int i = 0; i < 3; i++) {
	    (*arPtr[i]).print();
	}

	for (int i = 0; i < 3; i++) {
	    delete arPtr[i];
	    arPtr[i] = nullptr;
	}
    }

    //Задание 2.1
    {
	BaseFile file("test.txt", "w");

	if (file.is_open()) {
	    std::cout << "Файл открыт успешно" << std::endl;
	}

	const char* text = "Text for the file";
	file.write_raw(text, strlen(text));
	file.tell();
    }

    {
	BaseFile file("test.txt", "r");

	if (file.is_open()) {
	    std::cout << "Файл открыт для чтения" << std::endl;
	}

	char buf[100] = {0};
	size_t bytes_read = file.read_raw(buf, sizeof(buf)-1);
	std::cout << buf << std::endl;
	file.tell();
    }

    {
	BaseFile file("test.txt", "r+");

	if (file.is_open()) {
	    file.seek(7);
	    file.tell();

	    char buf[100] = {0};
	    file.read_raw(buf, 20);
	    std::cout << "Прочитано с 7 позиции: " << buf << std::endl;
	}
    }

    //Задание 2.2
    //В нашем случае наследовать нужно через publiс, тк все методы должны отстаься доступными. Так же можно наследовать через
    //private, protected. 

    //Задание 2.2.1
    {
	struct TestCase {
	    const char* name;
	    const unsigned char* data;
	    int size;
	    const char* filename;
	};

	//Тестовые данные
	unsigned char test1[] = {0x46, 0x47}; //"FG"
        unsigned char test2[] = {0x41}; //"A"
        unsigned char test3[] = {0x48, 0x65, 0x6C}; //"Hel"
        unsigned char test4[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; //"Hello"

	//Массив тестов
	TestCase tests[] = {
	    {"2 байта", test1, sizeof(test1), "test1.bin"},
            {"1 байт", test2, sizeof(test2), "test2.bin"},
            {"3 байта", test3, sizeof(test3), "test3.bin"},
            {"5 байтов", test4, sizeof(test4), "test4.bin"},
	};

	int num_tests = sizeof(tests)/sizeof(tests[0]);

	for (int i = 0; i < 4; i++) {
	    Base32File b32out(tests[i].filename, "w"); //Файл с кодированием

	    size_t written = b32out.write(tests[i].data, tests[i].size);
	    
	b32out.flush_encode();
	}

	for (int j = 0; j < 4; j++) {
	    Base32File b32in(tests[j].filename, "r");

	    unsigned char decoded[100] = {0};
	    size_t read = b32in.read(decoded, sizeof(decoded) - 1);

	    std::cout << "Данные: ";
	    for (size_t k = 0; k < read; k++) {
		std::cout << std::hex << (int)decoded[k] << " ";
	    }
	    std::cout << std::endl;
	}
    }

    //Задание 2.2.2
    {
	const char* kitten =  "  _____________________________________\n"
        " / Here user input is shown. This line \\\n"
        " \\ must be at most 40 characters long. /\n"
        "  ------------------------------------\n"
        "     \\\n"
        "      \\\n"
        "        /\\_/\\  (\n"
        "       ( ^.^ ) _)\n"
        "         \\\"/  (\n"
        "       ( | | )\n"
        "      (d b)\n";;

	size_t original_size = strlen(kitten);
	std::cout << "Размер исходных данных: " << original_size << std::endl;

	{
	    //Сжатие
	    RleFile rle_out("kitten.rle", "w");
	    size_t written = rle_out.write(kitten, original_size);
	    rle_out.flush();
	}

	{
	    //Проверка размера
	    BaseFile check("kitten.rle", "r");
	    char compressed[2000] = {0};
	    size_t compressed_size = check.read_raw(compressed, sizeof(compressed)-1);
	    std::cout << "Размер сжатых данных: " << compressed_size << std::endl;
	}
    }

    //Задание 2.3
    {
        std::cout << "Вход в блок" << std::endl;
	RleFile rle1;
	std::cout << "Выход из блока" << std::endl;
    }
        std::cout << "За блоком" << std::endl;

    {
        std::cout << "Вход в блок (с параметрами)" << std::endl;
        RleFile rle2("test.rle", "w");
        std::cout << "Выход из блока" << std::endl;
    }
        std::cout << "За блоком" << std::endl;

    //Задание 2.4
    {
	BaseFile bf("number_base.txt", "w");
        Base32File b32f("number_b32.bin", "w");
        RleFile rf("number_rle.bin", "w");

        int n = 123456;
        if (n < 0) { 
	    bf.write("-", 1); 
	    n = -n;
	}
	char digits[20];
	int count = 0;
        while (n > 0) {
            digits[count++] = '0' + (n%10);
	    n /= 10;
        }
	for (int i = count-1; i>=0; i--) {
	    bf.write(&digits[i], 1);
	}	
	bf.write("\n", 1);

        n = 123456;
        if (n < 0) { 
	    b32f.write("-", 1); 
	    n = -n;
	}
        while (n > 0) {
            digits[count++] = '0' + (n%10);
            n /= 10;
        }
        for (int i = count-1; i>=0; i--) {
            b32f.write(&digits[i], 1);
        }
        b32f.write("\n", 1);
	b32f.flush_encode();

        n = 123456;
        if (n < 0) { 
	    rf.write("-", 1); 
	    n = -n;
	}
        while (n > 0) {
            digits[count++] = '0' + (n%10);
            n /= 10;
        }
        for (int i = count-1; i>=0; i--) {
            rf.write(&digits[i], 1);
        }
        rf.write("\n", 1);
	rf.flush();
    }

    //Задание 2.5
    {
	BaseFile bf("n_base.txt", "w");
        Base32File b32f("n_b32.bin", "w");
        RleFile rf("n_rle.bin", "w");

	write_int(bf, 123456);
	write_int(b32f, 123456);
	write_int(rf, 123456);

	b32f.flush_encode();
	rf.flush();

	//Результат вызова будет разным, тк в функцию передается параметр BaseFile, а значит и метод write будет из этого 
	//класса в любом случае. Данные других классов просто не сохранятся, тк метод предназначем не для них
    }

    //Задание 2.6
    {
	//Теперь для каждого класса будет вызываться свой метод в ф-ции. Размер классов увеличился, тк теперь
	//каждый объект получает скрытый указатель на методы и хранит его в классе, он занимает 4/8 байт в 
	//зависимости от системы. Теперь выбирается метод в функции не на этапе компиляции, а позже, так что 
	//для каждого класса он будет свой
    }

    //Задание 2.7
    {
	BaseFile *files[] = { 
            new BaseFile("file1.txt", "w"), 
            new RleFile("file2.rle", "w"), 
            new Base32File("file3.b32", "w"), 
        };

        for (int i = 0; i < 3; ++i) {
            files[i]->write("Hello!", 6);
        }

	for (int i = 0; i < 3; i++) {
	    delete files[i];
	}

	//Если деструктор не виртуальный, то память не освобождается и происходит утечка. Вызывается только деструктор
	//базового класса. 
    }

    //Задание 2.8
    /* {
        BaseFile *base_files = new BaseFile[2] { BaseFile("file1.txt", "w"), BaseFile("file2.txt", "w") };
        BaseFile *b32_files = new Base32File[2] { Base32File("b32_1.bin", "w"), Base32File("b32_2.bin", "w") };
        for (int i = 0; i < 2; ++i) {
            base_files[i].write("Hello!", 6);
            b32_files[i].write("Hello!", 6);
        }
        delete [] base_files;
        delete [] b32_files;
    } */
    {
	//При компиляции все хорошо, тк указатель на базовый класс вполне может указывать на объект производного класса. Но при 
	//выполнении появляются проблемы из-за разного размера классов и выделяемой под них памяти.
	
	BaseFile* files[3];
	files[0] = new BaseFile("base.txt", "w");
	files[1] = new RleFile("rle.bin", "w");
	files[2] = new Base32File("b32.bin", "w");

	for (int i = 0; i < 3; i++) {
	    files[i]->write("Hello!", 6);
	}

	//Освобождение буфера
	for (int i = 0; i < 3; i++) {
	    if (RleFile* rle = dynamic_cast<RleFile*>(files[i])) {
		rle->flush();
	    } else if (Base32File* b32 = dynamic_cast<Base32File*>(files[i])) {
		b32->flush_encode();
	    }
	}

	for (int i = 0; i < 3; i++) {
	    delete files[i];
	}
    }

    //Задание 3.1
    {
	BaseFile bf("test_base.txt", "w");
	Base32File b32("test_b32.txt", "w");
	RleFile rf("test_rle.txt", "w");

	IFile* files[3] = { &bf, &b32, &rf };

	for (int i = 0; i < 3; i++) {
	    write_int(*files[i], 12345+i);
	}

	b32.flush_encode();
	rf.flush();

	//Из ограничений: нельзя создать объект, производные классы должны реализовать все чисто виртуальные
	//методы
    }

    //Задание 3.2
    {
	Base32File2 b32f(new BaseFile("b32_test.txt", "w"));
        RleFile2 rf(new BaseFile("rle_test.txt", "w"));
        write_int(b32f, 123456);
        write_int(rf, 123456);	
    }

    //Задание 3.3
    {
	//файл->Rle->Base32->Base32
	//Базовый файл
	BaseFile* realfile = new BaseFile("new_test.bin", "w"); //Пишет на диск

	//Rle
	RleFile2* rle = new RleFile2(realfile); //Пишет в realfile

	//Base32
	Base32File2* b32_first = new Base32File2(rle); //Пишет в rle

	//Base32
	Base32File2* b32_second = new Base32File2(b32_first); //В предыдущий

	const char* text = "Hello, World!";
	write_int(*b32_second, 123456);

	b32_second->flush_encode();
	b32_first->flush_encode();
	rle->flush();
    }

    return 0;
}











































