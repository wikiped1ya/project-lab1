#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    //move
    {
	Rect r(10, 20, 30, 40);
	r.move(5, 10);
	assert(r.get_left() == 15);
	assert(r.get_right() == 25);
	assert(r.get_top() == 40);
	assert(r.get_bottom() == 50);
    }

    //inflate
    {
	Rect r(50, 60, 70, 80);
	r.inflate(2, 3, 4, 5);
	assert(r.get_left() == 48);
	assert(r.get_right() == 63);
	assert(r.get_top() == 66);
	assert(r.get_bottom() == 85);
    }

    return 0;
}
