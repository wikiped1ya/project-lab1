#ifndef NOTIFICATION_PRIORITY_QUEUE_HPP
#define NOTIFICATION_PRIORITY_QUEUE_HPP

#include <iostream>

//Вычисление приоритета структура
struct NotificationPriority {
    int priority;
    Notification* notif;
};

//Вычисление приоритера функция
int getPriority(Notification* notif) {
    switch (notif->type) {
	case SYSTEM:
	    if (notif->data.system.severity == URGENT) {
		return 4;
	    }
	    return 2;
	case INSTANT:
	    return 3;
	case APP:
	    return 1;
	default:
	    return 0;
    }
}

//Сравнение двух уведомлений
bool isMoreUrgent(Notification* a, Notification* b) {
    int priorityA = getPriority(a);
    int priorityB = getPriority(b);

    if (priorityA != priorityB) {
	return priorityA > priorityB;
    }

    if (a->time_stamp != b->time_stamp) {
	return a->time_stamp < b->time_stamp;
    }

    return false;
}

//Узел очереди
struct PQueueNode {
    Notification* data;
    PQueueNode* next;
    int order; //Порядок добавления

    PQueueNode(Notification* notif, int ord) : data(notif), next(nullptr), order(ord) {}
};

class NotificationPriorityQueue {
    private:
	PQueueNode* head;
	int nextOrder;
	int cou;

	//Поиск места для вставки по приоритету
	// TODO: узнать как сделать лучше: < O(N) для вставки и удаления
	PQueueNode* find_pos(Notification* notif) {
	    if (head == nullptr) return nullptr;

	    PQueueNode* current = head;
	    PQueueNode* prev = nullptr;

	    while (current != nullptr) {
		if (isMoreUrgent(notif, current->data)) {
		    return prev;
		}
		prev = current;
		current = current->next;
	    }
	    return prev;
	}

    public:
	NotificationPriorityQueue() : head(nullptr), nextOrder(0), cou(0) {}

	~NotificationPriorityQueue() {
	    while(!isEmpty()) {
		pop();
	    }
	}

	void push(Notification* notif) {
	    PQueueNode* newNode = new PQueueNode(notif, nextOrder++);

	    if (head == nullptr) {
		head = newNode;
	    } else {
		PQueueNode* pos = find_pos(notif);
		if (pos == nullptr) {
		    newNode->next = head;
		    head = newNode;
		} else if (pos->next == nullptr) {
		    pos->next = newNode;
		} else {
		    newNode->next = pos->next;
		    pos->next = newNode;
		}
	    }
	    cou++;
	}

	int size() const {
	    return cou;
	}

	bool isEmpty() const {
	    return cou == 0;
	}

	Notification* pop() {
	    if (isEmpty()) return nullptr;

	    PQueueNode* oldHead = head;
	    Notification* result = oldHead->data;
	    head = head->next;
	    delete oldHead;
	    cou--;
	    return result;
	}

	PQueueNode* begin() { return head; }
	PQueueNode* end() { return nullptr; }
};

#endif










































