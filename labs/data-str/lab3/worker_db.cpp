#include "worker_db.hpp"
#include <iostream>
#include <stdexcept>

WorkerDb::WorkerDb() : count(0) {
    for (int i = 0; i < TABLE_SIZE; i++) {
	buckets[i] = nullptr;
    }
}

WorkerDb::~WorkerDb() {
    for (int i = 0; i < TABLE_SIZE; i++) {
    	WorkerNode* current = buckets[i];
    	while (current != nullptr) {
	    WorkerNode* next = current->next;
	    delete current;
	    current = next;
        }
    }
}

WorkerData& WorkerDb::operator[](const char* last_name) {
    int index = hash(last_name);

    WorkerNode* node = findInBucket(index, last_name);

    if (node != nullptr) {
	return node->data;
    } else {
	WorkerData defData;
	WorkerNode* newNode = new WorkerNode(last_name, defData);

	newNode->next = buckets[index];
	buckets[index] = newNode;

	return newNode->data;
    }
}

bool WorkerDb::contains(const char* last_name) const {
    int index = hash(last_name);
    return findInBucket(index, last_name) != nullptr;
}
































