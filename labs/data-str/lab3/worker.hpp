#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include "/home/ser17/lab1/src/my_string.hpp"

struct WorkerData {
    MyString name;
    int age;
    double salary; //Зарплата

    WorkerData() : name(""), age(0), salary(0.0) {}
    WorkerData(const char* n, int a, double s) : name (n), age(a), salary(s) {}

    void print() const {
	std::cout << "Имя: " << name << std::endl;
	std::cout << "Возраст: " << age << std::endl;
	std::cout << "Зарплата: " << salary << std::endl;
    }
};

#endif






































