#ifndef NOTIFICATION_QUEUE_HPP
#define NOTIFICATION_QUEUE_HPP

#include <iostream>

struct QueueNode {
    Notification* data; //Указатель на уведомление
    QueueNode* next; //Указатель на следующий элемент

    QueueNode(Notification* notif) : data(notif), next(nullptr) {}
};

class NotificationQueue {
    private:
	QueueNode* head;
	QueueNode* tail;
	int cou;

    public:
	NotificationQueue() : head(nullptr), tail(nullptr), cou(0) {}

	~NotificationQueue() {
	    while (!isEmpty()) {
		pop();
	    }
	}

	void push(Notification* notif) {
	    QueueNode* newNode = new QueueNode(notif);

	    if (isEmpty()) {
		head = newNode;
		tail = newNode;
	    } else {
		tail->next = newNode;
		tail = newNode;
	    }

	    cou++;
	}

	int size() const {
	    return cou;
	}

	Notification* pop() {
	    if (isEmpty()) return nullptr;
	    QueueNode* oldHead = head;
	    Notification* result = oldHead->data;
	    head = head->next;

	    if (head == nullptr) tail = nullptr;
	    delete oldHead;
	    cou--;
	    
	    return result;
	}

	bool isEmpty() const {
	    return cou == 0;
	}

	//Итераторы
	QueueNode* begin() {return head; }
	QueueNode* end() {return nullptr; }
};

#endif







































