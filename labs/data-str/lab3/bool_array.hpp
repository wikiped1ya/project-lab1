#ifndef BOOL_ARRAY_HPP
#define BOOL_ARRAY_HPP

#include <iostream>
#include <cstring>

class BoolArray {
    private:
	unsigned char* data; //Массив байтов
	int arr_size; //Кол-во бит

	int getByteIndex(int index) const { return index/8; } //Номер байта
	int getBitIndex(int index) const { return index % 8; } //Номер бита
	unsigned char getMask(int index) const { return 1 << getBitIndex(index); }

    public:
	//Конструктор
	BoolArray(int size, bool defaultValue = false) : arr_size(size) {
	    int bytes = (size+7)/8; //Сколько нужно для округления
	    data = new unsigned char[bytes];

	    unsigned char fill = defaultValue ? 0xFF : 0x00;
	    for (int i = 0; i < bytes; i++) {
		data[i] = fill;
	    }

	    if (defaultValue == false and size % 8 != 0) {
		data[bytes-1] &= (1 << (size%8))-1;
	    }
	}

	//Копирование
	BoolArray(const BoolArray& other) : arr_size(other.arr_size) {
	    int bytes = (arr_size + 7) / 8;
	    data = new unsigned char[bytes];
	    for (int i = 0; i < bytes; i++) {
		data[i] = other.data[i];
	    }
	}

	//Деструктор
	~BoolArray() {
	    delete[] data;
	}

	//Присваивание
	BoolArray& operator=(const BoolArray& other) {
	    if (this != &other) {
		delete[] data;
		arr_size = other.arr_size;
		int bytes = (arr_size + 7) / 8;
		data = new unsigned char[bytes];
		for (int i = 0; i < bytes; i++) {
		    data[i] = other.data[i];
		}
	    }
	
	    return *this;
	}

	//Класс для оператора []
	class Reference {
	    private:
		BoolArray& array; //Ссылка на массив
		int index; //Индекс элемента

	    public:
		Reference(BoolArray& arr, int idx) : array(arr), index(idx) {}

		//Запрект копирования
		Reference(const Reference&) = default;
		Reference& operator=(const Reference&) = default;

		//Запись значения
		Reference& operator=(bool value) {
		    if (value) {
			array.data[array.getByteIndex(index)] |= array.getMask(index);
		    } else {
			array.data[array.getByteIndex(index)] &= ~array.getMask(index);
		    }

		    return *this;
		}	

		//Чтение
		operator bool() const {
		    return (array.data[array.getByteIndex(index)] & array.getMask(index)) != 0;
		}
	};

	//Опреатор []
	Reference operator[](int index) {
	    return Reference(*this, index);
	}

	//Опрератор [] возвращающий bool
	bool operator[](int index) const {
	    return (data[getByteIndex(index)] & getMask(index)) != 0;
	}

	int size() const {
	    return arr_size;
	}

	//Изменение размера
	void resize(int newSize, bool defaultValue = false) {
	    int oldBytes = (arr_size + 7) / 8;
	    int newBytes = (newSize + 7) / 8;

	    unsigned char* newData = new unsigned char[newBytes];

	    //Копирование старых данных
	    int copyBytes = oldBytes < newBytes ? oldBytes : newBytes;
	    for (int i = 0; i < copyBytes; i++) {
		newData[i] = data[i];
	    }

	    unsigned char fill = defaultValue ? 0xFF : 0x00;
	    for (int i = copyBytes; i < newBytes; i++) {
		newData[i] = fill;
	    } 

	    //Если размер не кратек 8 и значение false
	    if (defaultValue == false and newSize % 8 != 0) {
	        newData[newBytes - 1] &= (1 << (newSize % 8)) - 1;
	    }

	    delete[] data;
	    data = newData;
	    arr_size = newSize;
	}
};

#endif












































