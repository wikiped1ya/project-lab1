#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <iostream>
#include <ctime>
#include <cstring>
#include "/home/ser17/lab1/src/my_string.hpp"

enum NotificationType {
    SYSTEM,
    INSTANT,
    APP
};

enum Severity {
    NORMAL,
    URGENT
};

struct Notification {
    time_t time_stamp;
    NotificationType type;

    union {
	//Системное
	struct {
	    MyString* message;
	    Severity severity;
	} system;

	//Мгновенное
	struct {
	    MyString* name;
	    MyString* text;
	} instant;

	//Приложение
	struct {
	    MyString* app_name;
	    MyString* title;
	    MyString* text;
	} app;
    } data;

    //Конструкторы
    //По умолчанию
    Notification() : time_stamp(0), type(SYSTEM), data() {
	data.system.message = nullptr;
	data.system.severity = NORMAL;
    }

    //Системное
    static Notification createSystem(const char* msg, Severity sev) {
	Notification n;
	n.time_stamp = ::time(nullptr);
	n.type = SYSTEM;
	n.data.system.message = new MyString(msg);
	n.data.system.severity = sev;
	return n;
    }

    //Мгновенное
    static Notification createInstant(const char* contact, const char* msg) {
	Notification n;
	n.time_stamp = ::time(nullptr);
	n.type = INSTANT;
	n.data.instant.name = new MyString(contact);
	n.data.instant.text = new MyString(msg);
	return n;
    }

    //Приложение
    static Notification createApp(const char* name, const char* title, const char* msg) {
	Notification n;
	n.time_stamp = ::time(nullptr);
	n.type = APP;
	n.data.app.app_name = new MyString(name);
	n.data.app.title = new MyString(title);
	n.data.app.text = new MyString(msg);
	return n;
    }

    //Деструктор
    ~Notification() {
	switch (type) {
	    case SYSTEM:
		delete data.system.message;
		break;
	    case INSTANT:
		delete data.instant.name;
		delete data.instant.text;
		break;
	    case APP:
		delete data.app.app_name;
		delete data.app.title;
		delete data.app.text;
		break;
	}
    }

    //Запрет копирования
    Notification(const Notification&) = delete;
    Notification& operator=(const Notification&) = delete;

    //Перемещение
    Notification(Notification&& other) : time_stamp(other.time_stamp), type(other.type), data(other.data) {
	other.type = SYSTEM;
	other.data.system.message = nullptr;
    }

    //Вывод уведомлений
    void print() const {
	char* time_str = ctime(&time_stamp);

	time_str[strlen(time_str)-1] = '\0'; //Убирает \n
	std::cout << "[" << time_str << "]" << std::endl;

	switch (type) {
	    case SYSTEM:
		std::cout << "СИСТЕМА: ";	
		if (data.system.severity == URGENT) {
		    std::cout << "Срочное!" << std::endl;
		}
		std::cout << *data.system.message << std::endl;
		break;
	    case INSTANT:
		std::cout << "СООБЩЕНИЕ: От ";
		std::cout << *data.instant.name << std::endl;
		std::cout << *data.instant.text << std::endl;
		break;
	    case APP:
		std::cout << "ПРИЛОЖЕНИЕ: ";
		std::cout << *data.app.app_name << std::endl;
		std::cout << *data.app.title << std::endl;
		std::cout << *data.app.text << std::endl;
		break;
	}
    }
};

//Подсчет уведомлений заданного типа
int cou(Notification** notification, int size, NotificationType type) {
    int count = 0;
    for (int i = 0; i < size; i++) {
	if (notification[i]->type == type) {
	    count++;
	}
    }
    return count;
}

#endif




































