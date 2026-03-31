//Объявление классов

#include <iostream>
#ifndef RECT_HPP
#define RECT_HPP

class Rect {
    private:
	int x;
	int y;
	int width;
	int height;

//	int left;
//	int right;
//	int top;
//	int bottom;

    public:
	//Конструкторы
	// TODO: добавить проверку на перепутанность координат во всех местах публичного интерфейса
	//       по возможности избежать повторения кода
	Rect();
	Rect (int l, int r, int t, int b);
	Rect(const Rect& other); //Копирование

	//Деструкторы
	~Rect();

	//Для доступа к полям
	int get_left() const; //Получение значения
	int get_right() const;
	int get_top() const;
	int get_bottom() const;

	void set_all(int let, int right, int top, int bottom); //Изменение значений

	//Перегруженные методы
	void inflate(int amount);
	void inflate(int dw, int dh);
	void inflate(int d_left, int d_right, int d_top, int d_bottom);

	//Еще методы
	void move(int dx, int dy = 0);

	//Для ширины, высоты, площади
	int get_width() const;
	int get_height() const;
	int get_square() const;

	//Для установки ширины и высоты
	void set_width(int new_w);
	void set_height(int new_h);
};

Rect bounding_rect(const Rect& r1, const Rect& r2);

//Для вывода информации
void print_rect(const Rect &r);

#endif

