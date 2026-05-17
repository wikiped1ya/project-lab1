#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <cmath>

class Point {
    private:
	double x;
	double y;

    public:
	Point() : x(0), y(0) {}
	Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

	double get_x() const { return x; }
	double get_y() const { return y; }

	//Установить значения
	void set_x(double val) { x = val; }
	void set_y(double val) { y = val; }

	//Опреатор присваивания
	Point& operator=(const Point& other) {
	    if (this != &other) {
		x = other.x;
		y = other.y;
	    }

	    return *this;
	}

	//Сравнение двух точек
	bool operator==(const Point& other) const {
	    return (fabs(x - other.x) < 1e-9 and fabs(y-other.y) < 1e-9);
	}

	//Вывод точки в поток
	friend std::ostream& operator<<(std::ostream& os, const Point& p) {
	    os << p.x << ", " << p.y;
	    return os;
	} 

	//Ввод точки из потока
	friend std::istream& operator>>(std::istream& is, Point& p) {
	    is >> p.x >> p.y;
	    return is;
	}
};

#endif














































