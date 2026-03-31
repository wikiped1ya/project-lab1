#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

int main() {
    //Обычный случай
    {
	Rect r1(10, 20, 30, 40);
	Rect r2(15, 25, 35, 45);
	Rect res = bounding_rect(r1, r2);

	assert(res.get_left() == 10);
	assert(res.get_right() == 25);
	assert(res.get_top() == 30);
	assert(res.get_bottom() == 45);
    }

    //При перепутанных координатах
    {
	Rect r1(20, 10, 40, 30);
	Rect r2(15, 25, 35, 45);
	Rect res = bounding_rect(r1, r2);

	assert(res.get_left() == 10);
        assert(res.get_right() == 25);
        assert(res.get_top() == 30);
        assert(res.get_bottom() == 45);
    }

    return 0;
}
