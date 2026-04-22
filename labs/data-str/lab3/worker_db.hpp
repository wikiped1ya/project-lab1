#ifndef WORKER_DB_HPP
#define WORKER_DB_HPP

#include "worker.hpp"

//Размер таблицы
static const int TABLE_SIZE = 1009;

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
	WorkerNode** buckets; //Указатель на массив корзин
	int bucketIndex; //Индекс текущей корзины
	int tableSize; //Размер таблицы

	//Поиск следующей непустой корзины
	void findNext() {
	    while (current == nullptr and bucketIndex < tableSize) {
		current = buckets[bucketIndex];
		bucketIndex++;
	    }
	}

    public:
	//Конструктор
	WorkerDbIt(WorkerNode* node = nullptr, WorkerNode** b = nullptr, int size = 0, int idx = 0) : current(node), buckets(b), tableSize(size), bucketIndex(idx) {
	    //Поиск первого непустого элемента в массиве корзин
	    if (current == nullptr and buckets != nullptr) {
		findNext();
	    }
	}
	
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
		//Если в этой корзине элементы закончились
		if (current == nullptr) {
		    findNext();
		}
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
	WorkerNode* buckets[TABLE_SIZE]; //Массив указателей на начала списков
	int count; //Кол-во элементов

	//Хэш функция
	int hash(const char* lastName) const {
	    unsigned long h = 0;
	    for (int i = 0; lastName[i] != '\0'; i++) {
		h = (h * 31 + lastName[i]) % TABLE_SIZE;
	    }

	    return h;
	}

	//Поиск по фамилии (в конкретной корзине)
	WorkerNode* findInBucket(int index, const char* last_name) const {
	    WorkerNode* current = buckets[index];
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
	    return WorkerDbIt(nullptr, buckets, TABLE_SIZE, 0);
	}

	WorkerDbIt end() {
	    return WorkerDbIt(nullptr, nullptr, TABLE_SIZE, TABLE_SIZE);
	}
};

#endif




































































