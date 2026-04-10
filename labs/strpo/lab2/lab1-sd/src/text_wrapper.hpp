#ifndef TEXT_WRAPPER
#define TEXT_WRAPPER
#include "my_string.hpp"

class TextWrapper {
    private:
	MyString text; //Исходный текст
	int line_width; //Ширина строки
	int position; //Позиция в тексте
	int line_start; //Начало текущей строки
	int line_end; //Конец текущей строки
	int text_length; //Длина всего текста

    public:
	//Конструктор
	TextWrapper(const MyString& input_text, int width);

	//Основной метод
	void print_wrapped();

    private:
	//Вспомогательные методы
	bool is_end_of_text(); //Закончилась ли строка
	bool is_space(char c); //Является ли символ пробелом
	int find_space_before(int pos); //Поиск ближайшего пробела к позиции
	void print_line(int start, int end); //Вывод строки
	void print_top_border(); //Вывод верхней границы
	void print_bottom_border(); //Вывод нижней границы
	void print_last_line(); //Вывод последней строки
	void print_spaces(int count); //Вывод пробелов
};

#endif

