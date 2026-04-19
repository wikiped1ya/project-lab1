#include <utility>
#include <cassert>
#include <iostream>
#include "/home/ser17/lab1/src/my_string.hpp"
#include "/home/ser17/lab1/src/matrix.hpp"
#include "worker_db.hpp"
#include "notification.hpp"
#include "notification_queue.hpp"
#include "notification_priority_queue.hpp"

MyString addTxtExtension(const MyString &path) { return path + ".txt"; }

//Функции для задания 3.3
//Печать всей базы данных
void print_db(WorkerDb& db) {
    std::cout << "База данных работников:" << std::endl;

    int cou = 1;
    for (auto it = db.begin(); it != db.end(); ++it) {
	std::cout << "Фамилия: " << it.key() << ", Имя: " << it->name << ", Возраст: " << it->age << ", Зарплата: " << it->salary << std::endl;
	cou++;
    }

    if (cou = 1) {
	std::cout << "База данных пуста" << std::endl;
    }
}

//Вычисление среднего возраста
double get_age(WorkerDb& db) {
    int sum = 0;
    int cou = 0;

    for (auto it = db.begin(); it != db.end(); ++it) {
	sum += it->age;
	cou++;
    }

    if (cou == 0) {
	return 0.0;
    }

    return static_cast<double>(sum)/cou;
}


int main() {
    //Задание 1.1
    {
	MyString s1("AAA"), s2;
        s2 = s1;
        s1 = "CCC";
        s2 = MyString("tmp");
        s1 = s1;
    }
    {
        Matrix m1(10), m2(10, 2);
        m1 = m2;
        m2 = Matrix(3, 4, 1.0);
        m1 = m1;
    }

    //Задание 1.2.1
    {
        Matrix m1(4), m2(4, 4, 1);
        m2 += m1;
        m2 -= m1 += m1;
        m1 *= 2;
        m2 /= 3;
    }

    //Задание 1.2.2
    {
        Matrix m1(4), m2(4, 4, 1);
        Matrix m3 = (m1 + m2) * m1 * 4 / 2 - m2;
    }

    //Задание 1.2.3
    {
	//Нельзя перегрузить методом класса функцию double*Matrix, тк в методе класса левый операнд обязательно должен быть объектом класса
    }

    //Задание 1.2.4
    {
	MyString s1("abc"), s2("def"), s3;
        s1 += s2 += "111";
        s2 += "222" + s1 + "333";
        s3 += s3;
    }

    //Задание 1.3
    {
        MyString s1("abc");
        MyString s2 = s1 + "ccc";
        s1 = "abc" + s2;
        s2 = std::move(s1);

        Matrix m1(4), m2 = m1 + m1;
        m1 = m2 * m1;
        m2 = std::move(m1);
    }

    //Задание 1.4
    {
	MyString s1("abc"), s2("ab"), s3 = s1;
        assert(s2 < s1);
        assert(s1 == s3);
        assert(s1 != s2);
        assert(s1 <= s3);
        assert("ab" == s2);
        assert("aba" < s1);
        assert("aba" <= s3);
    }

    //Задание 1.5
    {
	MyString s1("abc");
        s1[0] = s1[1] = 'd';
	s1.print();
	std::cout << std::endl;
    }

    //Задание 1.6
    {
	MyString s("123");
        std::cout << "This is my string: '" << s << "'\n";
        std::cout << "Enter your string: ";
        std::cin >> s;
        std::cout << "Your string: '" << s << "'\n";
    }

    //Задание 3.1
    {
	WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 100.0);
        db["Petrov"] = WorkerData("Petr", 43, 250.0);
        db["Sidorov"] = WorkerData("Misha", 28, 180.0);
	std::cout << "Ivanov's name = " << db["Ivanov"].name << "\n";
        std::cout << "Petrov's age = " << db["Petrov"].age << "\n";
	std::cout << "Sidorov's salary = " << db["Sidorov"].salary << "\n";
    }

    //Задание 3.2
    {
	WorkerDb db;
        db["Ivanov"] = WorkerData("Ivan", 34, 100.0);
        db["Petrov"] = WorkerData("Petr", 43, 250.0);
        for (auto it = db.begin(); it != db.end(); ++it)
        {
            std::cout << it.key() << " -> " << it->name << '\n';
        }
    }
     	
    //Задание 3.3
    {
	WorkerDb db;

        db["Ivanov"] = WorkerData("Ivan", 34, 100.0);
        db["Petrov"] = WorkerData("Petr", 43, 250.0);
        db["Sidorov"] = WorkerData("Misha", 28, 180.0);

	print_db(db);

	double sr_age = get_age(db);
	std::cout << "Средний возраст: " << sr_age << std::endl;
    }

    //Задание 4.1
    {
	Notification* notifications[3];

	notifications[0] = new Notification(Notification::createSystem("Обновление системы.", NORMAL));
        notifications[1] = new Notification(Notification::createInstant("Мама", "Привет, как дела?"));
        notifications[2] = new Notification(Notification::createApp("Telegram", "Новое сообщение", "У вас 3 новых сообщения"));	

	std::cout << "Уведомления: " << std::endl;

	for (int i = 0; i < 3; i++) {
	    std::cout << i+1 << ". ";
	    notifications[i]->print();
	}

	std::cout << "Системных уведомлений: " << cou(notifications, 3, SYSTEM) << std::endl;

	for (int i = 0; i < 3; i++) {
	    delete notifications[i];
	}
    }

    //Задание 4.2
    {
	//Вместо union и enum можно было бы создать иерархию классов, где каждый тип уведомления будет отдельным классом-наследником.

	//Union: экономия памяти, простота, все данные рядом, но ручное управление памятью из за указателей, сложность с объектами с конструкторами

	//Наследование: легко добавлять новые типы, нет switch, код более чистый, можно хранить любые объекты, но тратится больше памяти, это медленнее и сложнее
    }

    //Задание 4.3
    {
	NotificationQueue queue;

	Notification* n1 = new Notification(Notification::createSystem("Обновление системы.", NORMAL));
	Notification* n2 = new Notification(Notification::createInstant("Мама", "Привет, как дела?"));
	Notification* n3 = new Notification(Notification::createApp("Telegram", "Новое сообщение", "У вас 3 новых сообщения"));  

	queue.push(n1);
	queue.push(n2);
	queue.push(n3);

	std::cout << "Размер: " << queue.size() << std::endl;  

	while (!queue.isEmpty()) {
	    Notification* n = queue.pop();
	    n->print();
	    delete n;
	}                 	
    }

    //Задание 4.4
    {
	NotificationPriorityQueue pq;

        Notification* n1 = new Notification(Notification::createSystem("Обновление системы.", NORMAL));
        Notification* n2 = new Notification(Notification::createInstant("Мама", "Привет, как дела?"));
        Notification* n3 = new Notification(Notification::createApp("Telegram", "Новое сообщение", "У вас 3 новых сообщения"));

        pq.push(n1);
        pq.push(n2);
        pq.push(n3);

        std::cout << "Размер: " << pq.size() << std::endl;	

	std::cout << "По приоритету:" << std::endl;
	while(!pq.isEmpty()) {
	    Notification* n = pq.pop();
	    n->print();
	    delete n;
	}
    }

    //Задание 5
    {
	//В классе BaseFile оператор присваивания запрещен, так как этот класс обладает открытым ресурсом. То есть он может открыть файл, но должен его и закрыть, а при копировании с этим могут возникнуть проблемы
    }



    return 0;
}









































