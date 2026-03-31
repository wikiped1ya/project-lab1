//Определение классов

#include <iostream>
#include "rect.hpp"

//Конструктор по умолчанию
Rect::Rect() : x(0), y(0), width(0), height(0) {
    std::cout << "Constructor this=" << this << "(x, y) = " << x << "," << y << ", width = " << width << ", height = " << height << std::endl;
}
//Rect::Rect() : left(0), right(0), top(0), bottom(0) {
//    std::cout << "Constructor  this="  << this << " values=(" << left << "," << right << "," << top << "," << bottom << ")" << std::endl;
//}

//Конструктор с параметрами
Rect::Rect(int l, int r, int t, int b) {
    if (l > r) {
	int temp = l;
	l = r;
	r = temp;
	std::cout << "Левая граница больше правой, меняю их метами" << std::endl;
    }

    if (t > b) {
	int temp = t;
	t = b;
	b = temp;
	std::cout << "Верхняя граница больше нижней, меня их местами" << std::endl;
    }

    x = l;
    y = b;
    width = r - l;
    height = b - t;

    std::cout << "Constructor  this=" << this << "(x, y) = " << x << "," << y << ", width = " << width << ", height = " << height << std::endl;
}
//Rect::Rect(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b){
//    std::cout << "Constructor  this=" << this << " values=(" << left << "," << right << "," << top << "," << bottom << ")" << std::endl;
//}

//Констуктор копирования
Rect::Rect(const Rect& other) : x(other.x), y(other.y), width(other.width), height(other.height) {
    std::cout << "Constructor  this=" << this << "(x, y) = " << x << "," << y << ", width = " << width << ", height = " << height << std::endl;
}
//Rect::Rect(const Rect& other) : left(other.left), right(other.right), top(other.top), bottom(other.bottom) {
//    std::cout << "Constructor  this=" << this << " values=(" << left << "," << right << "," << top << "," << bottom << ")" << std::endl;
//}

//Деструктор
Rect::~Rect() {
    std::cout << "Destructor Уничтожен прямоугольник - " << "(x, y) = " << x << "," << y << ", width = " << width << ", height = " << height << std::endl;
}
//Rect::~Rect() {
//    std::cout << "Destructor Уничтожен прямоугольник - " << left << "," << right << "," << top << "," << bottom << " по адресу " << this << std::endl;
//}

//Методы чтения полей
int Rect::get_left() const {
    return x;
}

int Rect::get_right() const {
    return x + width;
}

int Rect::get_top() const {
    return y - height;
}

int Rect::get_bottom() const {
    return y;
}

//int Rect::get_left() const {
//    return left;
//}
//
//int Rect::get_right() const {
//    return right;
//}
//
//int Rect::get_top() const {
//    return top;
//}
//
//int Rect::get_bottom() const {
//    return bottom;
//}

//Метод для изменения полей
void Rect::set_all(int l, int r, int t, int b) {
     if (l > r) {
         int temp = l;
         l = r;
         r = temp;
         std::cout << "Левая граница больше правой, меняю их метами" << std::endl;
     }

     if (t > b) {
         int temp = t;
         t = b;
         b = temp;
         std::cout << "Верхняя граница больше нижней, меняю их местами" << std::endl;
     }

    x = l;
    y = b;
    width = r - l;
    height = b - t;
}

//void Rect::set_all(int l, int r, int t, int b) {
//    left = l;
//    right = r;
//    top = t;
//    bottom = b;
//}

//Метод для печати прямоугольника
void print_rect(const Rect& r) {
    std::cout << "Прямоугольник: L=" << r.get_left() << ", R=" << r.get_right() << ", T=" << r.get_top() << ", B=" << r.get_bottom() << std::endl;

    int left = r.get_left();
    int right = r.get_right();
    int top = r.get_top();
    int bottom = r.get_bottom();

    if (left >= right or top >= bottom) {
	std::cout << "Прямоугольник некорректный" << std::endl;
    } else {
	for (int i = 0; i < right - left; i++) {
	    std::cout << "*";
	}
	std::cout << std::endl;
	for (int i = 0; i < bottom-top-2; i++) {
	    std::cout << "*";
	    for (int j = 0; j < right-left-2; j++) {
		std::cout << " ";
	    }
	    std::cout << "*" << std::endl;
	}
        for (int i = 0; i < right - left; i++) {
            std::cout << "*";
        }
	std::cout << std::endl;
    }
}

//Методы перегруженные
void Rect::inflate(int amount) {
    x -= amount;
    y += amount;
    width += 2*amount;
    height += 2*amount;
}
//void Rect::inflate(int amount) {
//    left -= amount;
//    right += amount;
//    top += amount;
//    bottom -= amount;
//}

void Rect::inflate(int dw, int dh) {
    x -= dw;
    y += dh;
    width += 2*dw;
    height += 2*dh;
}
//void Rect::inflate(int dw, int dh) {
//    top += dh;
//    bottom -= dh;
//    left -= dw;
//    right += dw;
//}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    x -= d_left;
    y += d_bottom;
    width += d_left + d_right;
    height += d_top + d_bottom;
}
//void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
//    left -= d_left;
//    right += d_right;
//    top -= d_top;
//    bottom += d_bottom;
//}

//Другие методы
void Rect::move(int dx, int dy) {
    x += dx;
    y += dy;
}
//void Rect::move(int dx, int dy) {
//    left += dx;
//    right += dx;
//    top += dy;
//    bottom += dy;
//}

Rect bounding_rect(const Rect& r1, const Rect& r2) {
    int r1_l = std::min(r1.get_left(), r1.get_right());
    int r1_r = std::max(r1.get_left(), r1.get_right());
    int r1_t = std::min(r1.get_top(), r1.get_bottom());
    int r1_b = std::max(r1.get_top(), r1.get_bottom());

    int r2_l = std::min(r2.get_left(), r2.get_right());
    int r2_r = std::max(r2.get_left(), r2.get_right());
    int r2_t = std::min(r2.get_top(), r2.get_bottom());
    int r2_b = std::max(r2.get_top(), r2.get_bottom());

    int min_left = std::min(r1_l, r2_l);
    int max_right = std::max(r1_r, r2_r);
    int min_top = std::min(r1_t, r2_t);
    int max_bottom = std::max(r1_b, r2_b);

    std::cout << "Границы: L=" << min_left << ", R=" << max_right << ", T=" << min_top << ", B=" << max_bottom << std::endl;

    return Rect(min_left, max_right, min_top, max_bottom);
}

//Ширина, высота, площадь
int Rect::get_width() const {
    return width;
}
//int Rect::get_width() const {
//    return right - left;
//}

int Rect::get_height() const {
    return height;
}
//int Rect::get_height() const {
//    return bottom - top;
//}

int Rect::get_square() const {
    return width*height;
}
//int Rect::get_square() const {
//    return (right - left)*(bottom - top);
//}

//Установка ширины, высоты
void Rect::set_width(int new_w) {
    if (new_w > 0) {
	width = new_w;
    } else {
	std::cout << "Ошибка (ширина должна быть положительной)";
    }
}
//void Rect::set_width(int new_w) {
//    if (new_w > 0) {
//        right = left + new_w;
//    } else {
//        std::cout << "Ошибка (ширина должна быть положительной)";
//    }
//}

void Rect::set_height(int new_h) {
    if (new_h > 0) {
	height = new_h;
    } else {
	std::cout << "Ошибка (высота должна быть положительной)";
    }
}
//void Rect::set_height(int new_h) {
//    if (new_h > 0) {
//        bottom = top + new_h;
//    } else {
//        std::cout << "Ошибка (высота должна быть положительной)";
//    }
//}


























































