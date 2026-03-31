#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    std::cout << "Тесты" << std::endl;

    //Констурктор по умолчанию
    {
	Rect r;
	assert(r.get_left() == 0);
	assert(r.get_right() == 0);
	assert(r.get_top() == 0);
	assert(r.get_bottom() == 0);
    }

    //Констурктор с параметрами
    {
	Rect r(10, 20, 30, 40);
	assert(r.get_left() == 10);
	assert(r.get_right() == 20);
	assert(r.get_top() == 30);
	assert(r.get_bottom() == 40);
    }

    //Констурктор копирования
    {
	Rect r1(10, 20, 30, 40);
	Rect r2 = r1;
	assert(r2.get_left() == 10);
	assert(r2.get_right() == 20);
	assert(r2.get_top() == 30);
	assert(r2.get_bottom() == 40);
    }

    //Метод set_all
    {
	Rect r;
	r.set_all(10, 20, 30, 40);
	assert(r.get_left() == 10);
	assert(r.get_right() == 20);
	assert(r.get_top() == 30);
	assert(r.get_bottom() == 40);
    }
}
