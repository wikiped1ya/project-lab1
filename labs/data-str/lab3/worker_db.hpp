#ifndef WORKER_DB_HPP
#define WORKER_DB_HPP

#include "worker.hpp"

//Структура для элемента базы данных
struct WorkerNode {
    MyString last_name;
    WorkerData data;
    WorkerNode* next; //Указатель на следующий элемент

    WorkerNode(const char* key, const WorkerData& value) : last_name(key), data(value), next(nullptr) {}
};

//Итератор
class WorkerDbIt {
    private:
	WorkerNode* current; //Текущий узел

    public:
	//Конструктор
	WorkerDbIt(WorkerNode* node = nullptr) : current(node) {}

	//Оператор разыменования
	WorkerData& operator*() {
	    return current->data;
	}

	//Указатель на данные
	WorkerData* operator->() {
	    return &current->data;
	}

	//Возвращает фамилию
	const MyString& key() const {
	    return current->last_name;
	}

	//Постфиксный ++
	WorkerDbIt operator++(int) {
	    WorkerDbIt temp = *this;
	    ++(*this);
	    return temp;
	}

	//Префиксный ++
	WorkerDbIt& operator++() {
	    if (current != nullptr) {
		current = current->next;
	    }
	    return *this;
	}

	//Сравнение
	bool operator==(const WorkerDbIt& other) const {
	    return current == other.current;
	}

	bool operator!=(const WorkerDbIt& other) const {
	    return current != other.current;
	}
};



class WorkerDb {
    private:
	WorkerNode* head; //Первый элемент списка

	//Поиск по фамилии
	WorkerNode* findNode(const char* last_name) const {
	    WorkerNode* current = head;
	    while (current != nullptr) {
		if (current->last_name == last_name) {
		    return current;
		}
		current = current->next;
	    }
	    return nullptr;
	}

    public:
	WorkerDb();
	~WorkerDb();

	//Оператор []
	WorkerData& operator[](const char* last_name);

	//Существует ли работник
	bool contains(const char* last_name) const;

	//Итераторы
	WorkerDbIt begin() {
	    return WorkerDbIt(head);
	}

	WorkerDbIt end() {
	    return WorkerDbIt(nullptr);
	}
};

#endif




































































