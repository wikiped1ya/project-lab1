#ifndef LIST_HPP
#define LIST_HPP

#include "circle.hpp"
#include <iostream>
#include <fstream>

class Node {
    private:
	Node* pPrev; //Предыдущий узел
	Node* pNext; //Следующий узел
	Circle m_Data; //Данные

    public:
	//Конструкторы
	Node();
	Node(const Circle& data, Node* prev, Node* next);

	//Деструктор
	~Node();

	//Для сортировки
	friend Node* split_list(Node* head);
	friend Node* merge_list(Node* left, Node* right);
	friend Node* merge_sort(Node* head);

	friend class List;
};

class List {
    private:
	Node Head;
	Node Tail; 
	size_t m_size; //Кол-во элементов в списке

	//Поиск узла с заданным кругом
	Node* find_node(const Circle& data) const;

    public:
	//Конструктор
	List();
	
	//Деструктор
	~List();

	// TODO: переопределить то, что компилятор неявно определил неверно

	//Конструктор копирования
	List(const List& other);

	//Оператор присваивания
	List& operator=(const List& other);

	//Конструктор перемещения
	List(List&& other);

	//Оператор присваивания(перемещения)
	List& operator=(List&& other);

	//Добавление элемента в начало списка
	void push_front(const Circle& data);
	
	//Добавление элемента в конец списка
	void push_back(const Circle& data);

	//Удаление элемента с заданным значением
	bool remove_first(const Circle& data);
	
	//Удаление всех таких элементов
	size_t remove_all(const Circle& data);

	//Очистить список
	void clear();

	//Размер списка
	size_t size() const;

	//Пуст ли список
	bool empty() const;

	//Сортировка по возрастанию
	void sort_by_area();

	//Вывод в поток
	void print(std::ostream& os) const;

	//Опреатор вывода
	friend std::ostream& operator<<(std::ostream& os, const List& l);

	//Чтение списка из файла и запись в файл
	void read_file(const char* filename);
	void write_file(const char* filename) const;

	//Новые методы
	void read(std::istream& is);
	void write(std::ostream& os) const;

	//Применяет функцию к каждому элементу
	void for_each(void (*func)(Circle&));
};

// TODO: будет ли ваш метод работать с таким объектом или с lambda функцией
// TODO: если нет, то использовать std::function
struct Functional {
	void operator()(Circle& c);
};

// TODO: добавить интерфейс в класс, который позволил бы выполнить такую
// операцию эффективно
void increase_all_radiuses(List &list, double k);


#endif




























