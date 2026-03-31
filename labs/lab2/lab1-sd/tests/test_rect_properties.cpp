#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    //Проверка get_width и get_height
    {
	Rect r(10, 20, 30, 40);
	assert(r.get_width() == 10);
	assert(r.get_height() == 10);
    }

    //Проверка get_square
    {
	Rect r(50, 60, 70, 80);
	assert(r.get_square() == 100);
    }

    //Проверка set_width и set_heigth
    {
	Rect r(90, 100, 110, 120);
	r.set_width(5);
	assert(r.get_left() == 90);
	assert(r.get_right() == 95);
	r.set_height(15);
	assert(r.get_top() == 105);
	assert(r.get_bottom() == 120);
    }

    return 0;
}
