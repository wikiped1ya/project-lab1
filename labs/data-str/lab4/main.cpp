#include "list.hpp"
#include <iostream>

int main() { 
    List l;

    //Добавление кругов в конец и в начало
    l.push_back(Circle(Point(0, 0), 5));
    l.push_back(Circle(Point(0, 0), 3));
    l.push_front(Circle(Point(1, 2), 4));
    l.push_front(Circle(Point(-1, 0), 6));

    std::cout << "Исходный список:" << std::endl;
    std::cout << l;
    std::cout << std::endl;

    //Сортировка по площади
    l.sort_by_area();
    std::cout << "Сортировка по площади:" << std::endl;
    std::cout << l;
    std::cout << std::endl;

    //Удаление круга
    l.remove_first(Circle(Point(0, 0), 3));
    std::cout << "Удаление круга (0, 0, 3):" << std::endl;
    std::cout << l;
    std::cout << std::endl;

    //Запись в файл
    l.write_file("circle.txt");
    std::cout << "Список записан в файл 'circle.txt'" << std::endl;

    //Чтение из файла
    List l2;
    l2.read_file("circle.txt");
    std::cout << "Список прочитан из файла 'circle.txt'" << std::endl;
    std::cout << l2;
    std::cout << std::endl;

    return 0;
}











































