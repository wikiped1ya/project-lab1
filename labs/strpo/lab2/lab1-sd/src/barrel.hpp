#ifndef BARREL_HPP
#define BARREL_HPP
#include <iostream>

class Barrel {
	// TODO: добавить обработку логики переполнения бочки
    private:
	double total_volume;
	double alch_volume;
	double water_volume;

    public:
	Barrel(double total, double volume, double alch_conc); //Конструктор
	double get_alch_conc() const; //Получить концентрацию
	void pour(Barrel& other); //Перелить воду
};

#endif
