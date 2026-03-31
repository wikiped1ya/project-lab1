#include "my_string.hpp"
#include <iostream>
#include <cstring>

//По умолчанию
MyString::MyString() : data(nullptr), length(0) {
    std::cout << "Constructor Создана пустая строка" << std::endl;
}

//Выделяет память
MyString::MyString(const char* str) : data(nullptr), length(0) {
    std::cout << "Cjnstructor MyString - " << str << std::endl;
    if (str != nullptr) {
	length = strlen(str);
	data = new char[length + 1];
	for (int i = 0; i <= length; i++) {
	    data[i] = str[i];
	}
    }
}

//Конструктор копирования
MyString::MyString(const MyString& other) : data(nullptr), length(0) {
    std::cout << "Constructor Копирование" << std::endl;
    if (other.data != nullptr) {
	length = other.length;
	data = new char[length + 1];
	for (int i = 0; i <= length; i++) {
	    data[i] = other.data[i];
	}
    }
}

//Деструктор
MyString::~MyString() {
    std::cout << "Destructor Удалена строка" << std::endl;
    if (data != nullptr) {
	delete[] data;
    }
}

//Оператор присваивания
MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
	return *this;
    }

    //Освобождается старая память
    if (data != nullptr) {
	delete[] data;
	data = nullptr;
    }

    //Копируется новая
    if (other.data != nullptr) {
	length = other.length;
	data = new char[length + 1];
	for (int i = 0; i <= length; i++) {
	    data[i] = other.data[i];
	}
    } else {
	length = 0;
	data = nullptr;
    }

    return *this;
}

//Получение i-того элемента
char MyString::get(int i) {
    if (i < 0 or i >= length or data == nullptr) {
	std::cout << "Ошибка (индекс вне границ)" << std::endl;
	return '\0';
    }

    return data[i];
}

//Установка i-того элемента
void MyString::set(int i, char c) {
    if (i < 0 or i >= length or data == nullptr) {
	std::cout << "Ошибка (индекс вне границ)" << std::endl;
	return;
    }

    data[i] = c;
}

//Замена
void MyString::set_new_string(const char *str) {
    if (data!=nullptr) {
	delete[] data;
	data = nullptr;
    }

    if (str != nullptr) {
	length = strlen(str);
	data = new char[length + 1];
	for (int i = 0; i <= length; i++) {
	    data[i] = str[i];
	}
    } else {
	length = 0;
    }
}

//Вывод строки
void MyString::print() {
    if (data==nullptr or length == 0) {
	std::cout << "Строка пуста" << std::endl;
    } else {
	std::cout << "Строка: " << data << std::endl;
	std::cout << "Длина строки: " << length << std::endl;
    }
}

//Замена с консоли
void MyString::read_line() {
    std::cout << "Введите строку: ";

    //Чтение строки
    int capacity = 10;
    char* buff = new char[capacity];
    int pos = 0;
    char c;

    while (std::cin.get(c) and c!='\n') {
	if (pos >= capacity - 1) {
	    capacity *= 2;
	    char* new_buff = new char[capacity];
	    for (int i = 0; i < pos; i++) {
		new_buff[i] = buff[i];
	    }
	    delete[] buff;
	    buff = new_buff;
	}
	buff[pos++] = c;
    }
    buff[pos] = '\0';

    if (data != nullptr) {
	delete[] data;
    }

    length = pos;
    data = new char[length + 1];
    for (int i = 0; i <= length; i++) {
	data[i] = buff[i];
    }

    delete[] buff;
}

//Получение длины
int MyString::get_length() {
    return length;
}
































