#include "text_wrapper.hpp"
#include <iostream>

//Конструктор
TextWrapper::TextWrapper(const MyString& input_text, int width) : text(input_text), line_width(width), position(0), line_start(0),
line_end(0), text_length(text.get_length()) {}

//Закончился ли текст
bool TextWrapper::is_end_of_text() {
    return position >= text_length;
}

//Является ли символ пробелом
bool TextWrapper::is_space(char c) {
    return c == ' ';
}

//Поиск пробела
int TextWrapper::find_space_before(int pos) {
    while(pos > line_start and !is_space(text.get(pos))) {
	pos--;
    }
    if (pos == line_start) {
        return line_start + line_width;
    }
    return pos;
}

//Вывод строки
void TextWrapper::print_line(int start, int end) {
    std::cout << " |";
    int line_len = end - start;

    for (int i = start; i < end; i++) {
	std::cout << text.get(i);
    }

    print_spaces(line_width - line_len);
    std::cout << "|" << std::endl;
}

//Вывод пробелов
void TextWrapper::print_spaces(int count) {
    for (int i = 0; i < count; i++) {
	std::cout << ' ';
    }
}

//Вывод верхней границы
void TextWrapper::print_top_border() {
    std::cout << "  ";
    for (int i = 0; i < line_width; i++) {
	std::cout << "_";
    }
    std::cout << std::endl;
}

//Вывод нижней границы
void TextWrapper::print_bottom_border() {
    std::cout << "  ";
    for (int i = 0; i < line_width; i++) {
	std::cout << "-";
    }
    std::cout << std::endl;
}

//Вывод последней строки
void TextWrapper::print_last_line() {
    int lenn = text_length - line_start;
    std::cout << " |";
    for (int i = 0; i < lenn; i++) {
	std::cout << text.get(line_start+i);
    }
    print_spaces(line_width-lenn);
    std::cout << "| " << std::endl;
}

//Основной метод
void TextWrapper::print_wrapped() {
    print_top_border();

    line_start = 0;

    while (line_start < text_length) {
        //Если остаток текста помещается в строку
        if (text_length - line_start <= line_width) {
            print_line(line_start, text_length);
            break;
        }

        //Место для переноса
        line_end = line_start + line_width;

        //Если на границе не пробел, ищем пробел левее
        if (!is_space(text.get(line_end))) {
            int new_end = find_space_before(line_end);
            if (new_end > line_start) {
                line_end = new_end;
            }
        }

        print_line(line_start, line_end);
        //Пропускает пробел в начале следующей строки
        line_start = line_end;
        while (line_start < text_length and is_space(text.get(line_start))) {
            line_start++;
        }
    }

    print_bottom_border();
}





















































































