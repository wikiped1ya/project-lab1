#include <iostream>
#include <cstdlib> //Для рандомайзера
#include <ctime>
#include <cstring>
#include "../basefile.hpp"

//Генерация случайных данных
unsigned char* generate(size_t size) {
    unsigned char* data = new unsigned char[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = rand() % 256;
    }
    return data;
}

//Сравнение двух массивов
bool compare_data(const unsigned char* data1, const unsigned char* data2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (data1[i] != data2[i]) {
            std::cout << "Ошибка: данные не совпали" << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));

    const size_t DATA_SIZE = 50000; //(примерно 50кб)
    const size_t BUFFER_SIZE = 256;

    unsigned char* orig_data = generate(DATA_SIZE);

    {
        RleFile file("test_rlefile.bin", "w");
        size_t written_total = 0; //Сколько байт записано

        while (written_total < DATA_SIZE) {
            size_t to_write = BUFFER_SIZE;

            if (to_write > DATA_SIZE - written_total) {
                to_write = DATA_SIZE - written_total;
            }

            size_t written = file.write(orig_data + written_total, to_write);

            written_total += written;
        }
        file.flush();
        std::cout << "Записано " << written_total << " байт" << std::endl;
    }

    //Чтнение данных
    unsigned char* read_data = new unsigned char[DATA_SIZE];

    {
        RleFile file("test_rlefile.bin", "r");

        size_t read_total = 0;

        while (read_total < DATA_SIZE) {
            size_t to_read = BUFFER_SIZE;

            if (to_read > DATA_SIZE - read_total) {
                to_read = DATA_SIZE - read_total;
            }

            size_t read = file.read(read_data + read_total, to_read);

            if (read == 0) {
                break;
            }

            read_total += read;
        }
        std::cout << "Прочитано " << read_total << " байт" << std::endl;
    }

    //Сравнение данных
    if (compare_data(orig_data, read_data, DATA_SIZE)) {
        std::cout << "Данные совпадают" << std::endl;
        delete[] orig_data;
        delete[] read_data;
        return 0;
    } else {
        std::cout << "Данные не совпадают" << std::endl;
        delete[] orig_data;
        delete[] read_data;
        return 1;
    }
}
