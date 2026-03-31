#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>

class Matrix {
    private:
	int height;
	int width;
	double** data;

    public:
	//Конструторы
	Matrix(int n); //Единичная матрица
	Matrix(int n, int m, double fill_value = 0); //Матрица m*n
	Matrix(const Matrix& other); //Конструтор копирования

	//Деструктор
	~Matrix();

	//Оператор присваивания
	Matrix& operator=(const Matrix& other);

	//Еще методы
	double get(int i, int j) const; //Получить значение элемента
	void set(int i, int j, double value); //Установить значение элемента
	int get_height() const; //Получить высоту
	int get_width() const; //Получить ширину
	void negate(); //-A
	void add_in_place(Matrix &other); //Сложение
	Matrix multiply(Matrix& other) const; //Умножение

    private:
	void memory();
};

#endif
