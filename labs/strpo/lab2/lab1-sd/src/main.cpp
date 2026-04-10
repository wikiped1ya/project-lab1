#include <iostream>
#include "rect.hpp"
#include "barrel.hpp"
#include "matrix.hpp"
#include "my_string.hpp"
#include "text_wrapper.hpp"

class C {
	MyString s;
	MyString s1;
	MyString s2;
};

int main () {

    //Задание 1.2
    {
        Rect rect;
        std::cout << rect.get_left() << std::endl;
        std::cout << rect.get_right() << std::endl;
        std::cout << rect.get_top() << std::endl;
        std::cout << rect.get_bottom() << std::endl;
    }
    //Поля содержат случайные значения, которые были в памяти
    //Вызывается конструктор по умолчанию, ко орый создается автоматически
    //Он определен компилятором с++
    //Поля не инициализируются и содержат мусор
    //В общем случае такой код либо не инициализирует поля(для встроенных типов), либо вызывает конструктор по умолчанию(для
    //объектов классов и массивов)

    //Задание 1.3
    {
        Rect rect(1, 2, 3, 4);

	int l, r, t, b;
	std::cout << "Введите стороны прямоугольника: " << std::endl;
	std::cin >> l >> r >> t >> b;

	Rect myRect(l, r, t, b);

	std::cout << "left: " << myRect.get_left() << std::endl;
        std::cout << "right: " << myRect.get_right() << std::endl;
        std::cout << "top: " << myRect.get_top() << std::endl;
        std::cout << "bottom: " << myRect.get_bottom() << std::endl;
    }

    //Задание 1.4
    {
        Rect rect1(1, 2, 3, 4);
        Rect rect2 = rect1;
        Rect rect3(rect1);

	//В первой строке вызывается конструктор Rect и создается новый объект
	//Во второй - вызывается конструктор копирования и создает новый
	//rect2 - копию rect1
	//В третье строчке точно так же копируется

	//Конструктор Rect определен мною, а конструктор копирования определен
	//автоматически

	//В этом случае выделяется память для rect2, туда копируются все поля
	//В общем случае для встроенных типов копируется значение, для объектов
	//классов вызывается конструктор копирования этого класса
    }

    //Задание 1.5
    {
	//Деструктор - специальный метод класса, который вызывается автматически
	//при уничтожении объекта
	//Он вызывается: при выходе из области видимости блока(для стековых п.), при
	//вызове оператора delete(для динамических), после завершения выражения,
	//в котором созданы временные объекты, при завершении программы(для глобальных)
	//Есть неявный деструктор, который компилятор автоматически генерирует
	//Тут он ничего не делает, тк int не требует специальной очистки
	//А в общем случае: для объектов классов вызывает их деструктор, для
	//указателей и динамической памяти не освоождает память(надо самому)

	//В задании 1.2 деструтор вызывается при выходе из блока, в 1.3 - так же,
	//в 1.4 - для всех трех объектов в обратном порядке
    }

    //Задание 1.6
    {
        Rect r1; // Конструктор по умолчанию - 1
        Rect *pR = new Rect(1,2,1,2); // Конструктор с параметрами - 2
        {
            Rect r2(r1); //Конструктор копирования - 3
            Rect arRect[2]; //Конструктор по умолчанию(два раза, тк два элемента) - 5
            for(int i = 0; i < 3; i++)
            {
                static Rect r3 (i,i,i,i) ; //Конструктор с параметрами - 6
                Rect r4(*pR); //Конструктор копирования(три раза, каждую итерацию) - 9
                Rect r5(i,i,i,i); //Конструктор с параметрами(тоже три) - 12
            } //Деструктор(уничтожаются r4 и r5 при каждой итерации +6) - 18
        } //Деструктор(уничтожаются r2, srRect[0], srRect[1] +3) - 21
        delete pR; //Деструтор - 22
    } //Деструктор(уничтожается r1) - 23

    //Задание 1.7
    {
        Rect r1;
        //std::cout << r1.left << std::endl;
	std::cout << r1.get_left() << std::endl;
	//Ошибка происходит, тк доступ к приватным полям есть только внутри класса
    }

    //Задание 1.8
    {
       Rect r;
       std::cout << r.get_left() << "; " << r.get_right() << '\n';
       r.set_all(1, 2, 3, 4);
       std::cout << r.get_top() << "; " << r.get_bottom() << '\n';
    }
    //Функция-член в отличие от обычной: принадлежит классу, имеет параметр this, вызывается через объект, объявляется внутри класса и
    //имеет доступ к его скрытым полям

    //Задание 1.10
    {
	// TODO: сделать функцию `bounding_rect(Rect r1, Rect r2)` (чтобы она
	// принимала аргументы по значению) и посмотреть, какони будут переданы
	Rect r1(10, 20, 30, 40), r2(50, 60, 70, 80);
        Rect r3 = bounding_rect(r1, r2);
        print_rect(r3);
    }

    //Задание 1.11
    {
	Rect rect(10, 50, 20, 60);
	std::cout << "Исходный прямоугольник: " << std::endl;
	print_rect(rect);

	std::cout << "Ширина: " << rect.get_width() << std::endl;
        std::cout << "Высота: " << rect.get_height() << std::endl;
        std::cout << "Площадь: " << rect.get_square() << std::endl;

	rect.set_width(4);
	std::cout << "Новая ширина: " << rect.get_width() << std::endl;

	rect.set_height(5);
	std::cout << "Новая высота: " << rect.get_height() << std::endl;

	print_rect(rect);
    }

    //Задание 2.1
    {
        Barrel alch(10.0, 9.0, 0.96); // бочка со спиртом
        Barrel water(10.0, 9.0, 0.0);

	int i = 0;

        while(alch.get_alch_conc() > 0.5)
        {
	    i++;
            alch.pour(water);
            water.pour(alch);
        }
	std::cout << "Концентрация стала меньше 50% на итерации: " << i << std::endl;
    }

    //Задание 2.2
    {
	Matrix q(2, 2, 0.0);
	q.set(0, 0, 1.0);
        q.set(0, 1, 1.0);
        q.set(1, 0, 1.0);

	Matrix v(2, 1, 0.0);
	v.set(0, 0, 1.0);

	std::cout << "Числа Фибоначчи:" << std::endl;
	std::cout << "F(0) = 0" << std::endl;
        std::cout << "F(1) = 1" << std::endl;

	Matrix current = v;

	for (int n = 2; n <= 40; n++) {
	    Matrix next = q.multiply(current);
	    double Fn = next.get(0, 0);
	    std::cout << "F(" << n << ") = " << Fn << std::endl;
	    current = next;
	}
    }
    {
	Rect r1(1, 2, 3, 4), r2;
 	r2 = r1;
    }
    {
        Rect *r1 = new Rect(1, 2, 3, 4), *r2 = nullptr;
        r2 = r1;
    }

    //Задание 2.3
    {
	MyString s1;
	std::cout << "s1 = ";
	s1.print();

	// TODO: какие проблемы будут, если не определить оператор присваивания
	// для класса MyString (тут и вообще) 
	// TODO: что делает определенный неявно оператор присваивания и
	// конструктор копирования

	MyString s2 = s1;
        std::cout << "s2 = ";
        s2.print();

	MyString s3("This is my string");
	std::cout << "s3 = ";
	s3.print();

	MyString s4 = s3;
        std::cout << "s4 = ";
        s4.print();

	std::cout << "s3.get(3) = " << s3.get(3) << std::endl;

	s2.set(1, 'a');
	std::cout << "s2.set(1, 'a') -> ";
	s2.print();

	s1.set_new_string("New string");
	std::cout << "s1.set_new_string(New string'); -> ";
	s1.print();
    }

    //Задание 2.4
    {
	int line_width = 40;
        MyString input;
	std::cin.ignore(10000, '\n');
        input.read_line();
        TextWrapper wrapper(input, line_width);
        wrapper.print_wrapped();
    }


    return 0 ;
}


























