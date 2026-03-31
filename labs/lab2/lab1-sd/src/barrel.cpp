#include "barrel.hpp"
#include <iostream>

//Конструктор
Barrel::Barrel(double total, double volume, double alch_conc) {
    if (volume > total) { //Если воды больше, чем бочка
	std::cout << "Жидкости в бочке больше, чем ее объем, так что объем жидкости уменьшен до объема бочки" << std::endl;
	volume = total;
    }

    total_volume = total;
    alch_volume = volume*alch_conc;
    water_volume = volume*(1.0-alch_conc);

    std::cout << "Создана бочка объемом: " << total_volume << "л, с концентрацией спирта - " << alch_conc*100 << "%" << std::endl;
}

//Получить концентрацию
double Barrel::get_alch_conc() const {
    double total = alch_volume + water_volume;
        if (total < 1e-10) {
	    return 0.0;
        }
    return alch_volume / total;
}

//Перелить воду
void Barrel::pour(Barrel& other) {
    double volume = alch_volume + water_volume;
    if (volume < 1e-10) {
	std::cout << "Бочка путса" << std::endl;
	return;
    }

    double amount;
    if (volume < 1.0) {
	amount = volume;
    } else {
	amount = 1.0;
    }

    double alch_part = alch_volume/volume;
    double water_part = water_volume/volume;

    double alch_to_pour = amount*alch_part;
    double water_to_pour = amount*water_part;

    alch_volume -= alch_to_pour;
    water_volume -= water_to_pour;

    other.alch_volume += alch_to_pour;
    other.water_volume += water_to_pour;

    if (other.alch_volume + other.water_volume > other.total_volume) {
	other.alch_volume -= (other.water_volume+other.alch_volume-other.total_volume)*(other.alch_volume/(other.alch_volume + other.water_volume));
	other.water_volume -= (other.water_volume+other.alch_volume-other.total_volume)*(other.water_volume/(other.alch_volume + other.water_volume));
    }
}
