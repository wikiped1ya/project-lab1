#include "matrix.hpp"
#include <iostream>

void Matrix::memory() {
    data = new double*[height];
    for (int i = 0; i < height; i++) {
	data[i] = new double[width];
    }
}

Matrix::Matrix(int n) : height(n), width(n) {
    memory();

    for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    if (i==j) {
		data[i][j] = 1.0;
	    } else {
	        data[i][j] = 0.0;
	    }
	}
    }

    std::cout << "Создана единичная матрица " << height << "x" << width << std::endl;
}

Matrix::Matrix(int n, int m, double fill_value) : height(n), width(m) {
    memory();

    for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    data[i][j] = fill_value;
	}
    }

    std::cout << "Создана матрица " << height << "x" << width << std::endl;
}

Matrix::Matrix(const Matrix& other) : height(other.height), width(other.width) {
    memory();

    for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    data[i][j] = other.data[i][j];
	}
    }

    std::cout << "Создана копия матрицы " << height << "x" << width << std::endl;
}

Matrix::~Matrix() {
    for (int i = 0; i < height; i++) {
	delete[] data[i];
    }
    delete[] data;

    std::cout << "Уничтожена матрица " << height << "x" << width << std::endl;
}

double Matrix::get(int i, int j) const {
    if (i < 0 or i>=height or j < 0 or j >= width) {
	throw std::out_of_range("Индекс вне границ");
    }
    return data[i][j];
}

void Matrix::set(int i, int j, double value) {
    if (i < 0 or i >= height or j < 0 or j >= width) {
	throw std::out_of_range("Индекс вне границ");
    }
    data[i][j] = value;
}

int Matrix::get_height() const {
    return height;
}

int Matrix::get_width() const {
    return width;
}

void Matrix::negate() {
    for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    data[i][j] = -data[i][j];
	}
    }
}

void Matrix::add_in_place(Matrix& other) {
    if (height !=other.height or width != other.width) {
	throw std::invalid_argument("Должны быть одинаковые размеры");
    }

    for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    data[i][j] += other.data[i][j];
	}
    }
}

Matrix Matrix::multiply(Matrix& other) const {
    if (width != other.height) {
	throw std::invalid_argument("Размеры не подходят");
    }

    Matrix result(height, other.width, 0.0);

    for (int i = 0; i < height; i++) {
	for (int j = 0; j < other.width; j++) {
	    double res = 0.0;
	    for (int k = 0; k < width; k++) {
		res += data[i][k]*other.data[k][j];
	    }
	    result.data[i][j] = res;
	}
    }

    return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
	return *this;
    }

    for (int i = 0; i < height; i++) { //Освобождается старая память объекта
	delete[] data[i];
    }
    delete[] data;

    height = other.height;
    width = other.width;

    memory();
    for (int i = 0; i < height; i++) {//Копируются данные
	for (int j = 0; j < width; j++) {
	    data[i][j] = other.data[i][j];
	}
    }

    return *this;
}




































































































































