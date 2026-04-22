#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "point.hpp"

class Circle {
    private:
	Point center;
	double radius;

    public:
	//Конструкторы
	Circle() : center(), radius(0) {}
	Circle(const Point& p, double r) : center(p), radius(r) {}
	Circle(const Circle& other) : center(other.center), radius(other.radius) {}

	//Получить значения
	Point get_center() const { return center; }
	double get_radius() const { return radius; }

	//Установить центр
	void set_center(const Point& p) { center = p; }
	void set_radius(double r) { radius = r; }

	//Площадь круга
	double get_area() const {
	    return 3.14159 * radius * radius;
	}

	//Оператор присваивания
	Circle& operator=(const Circle& other) {
	    if (this!= &other) {
		center = other.center;
		radius = other.radius;
	    }

	    return *this;
	}

	//Сравнение кругов
	bool operator==(const Circle& other) const {
	    return (center == other.center and fabs(radius - other.radius) < 1e-9);
	}

	//Вывод круга в поток
	friend std::ostream& operator<<(std::ostream& os, const Circle& c) {
	    os << c.center << ", " << c.radius;
	    return os;
	}

	//Ввод из потока
	friend std::istream& operator>>(std::istream& is, Circle& c) {
	    is >> c.center >> c.radius;
	    return is;
	}
};

#endif






































