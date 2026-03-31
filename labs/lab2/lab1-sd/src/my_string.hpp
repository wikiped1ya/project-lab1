#ifndef MY_STRING
#define MY_STRING
#include <iostream>

class MyString {
    private:
	char* data; //Указатель на дин память
	// TODO: понять, это длинна с терминирующим нулем или нет
	int length; //Длина строки
    public:
	//Конструкторы
	MyString(); //По умолчанию
	MyString(const char* str); //Выделяет память
	MyString(const MyString& other); //Конструктор копирования

	//Деструктор
	~MyString();

	//Оператор присваивания
	MyString& operator=(const MyString& other);

	//Другие методы
	char get(int i); //Получение i-того элемента
	void set(int i, char c); //Установка i-того элемента
	void set_new_string(const char *str); //Замена
	void print(); //Вывод строки
	void read_line(); //Замена с консоли
	int get_length(); //Получение длины
};

#endif
