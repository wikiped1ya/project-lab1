#include "worker_db.hpp"
#include <iostream>
#include <stdexcept>

WorkerDb::WorkerDb() : head(nullptr) {}

WorkerDb::~WorkerDb() {
    WorkerNode* current = head;
    while (current != nullptr) {
	WorkerNode* next = current->next;
	delete current;
	current = next;
    }
}

WorkerData& WorkerDb::operator[](const char* last_name) {
    WorkerNode* node = findNode(last_name);

    if (node != nullptr) {
	return node->data;
    } else {
	WorkerData defData;
	WorkerNode* newNode = new WorkerNode(last_name, defData);

	newNode->next = head;
	head = newNode;

	return newNode->data;
    }
}

bool WorkerDb::contains(const char* last_name) const {
    return findNode(last_name) != nullptr;
}
































