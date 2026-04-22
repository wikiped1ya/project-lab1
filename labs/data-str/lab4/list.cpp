#include "list.hpp"
#include <iostream>

Node::Node() : pPrev(nullptr), pNext(nullptr), m_Data() {}

Node::Node(const Circle& data, Node* prev, Node* next) : pPrev(prev), pNext(next), m_Data(data) {}

Node::~Node() {
    if (pPrev != nullptr) {
	pPrev->pNext = pNext;
    }
    if (pNext != nullptr) {
	pNext->pPrev = pPrev;
    }
}

List::List() : Head(), Tail(), m_size(0) {
    Head.pNext = &Tail; 
    Tail.pPrev = &Head;
}

List::~List() {
    clear();
}

void List::push_front(const Circle& data) {
    Node* newNode = new Node(data, &Head, Head.pNext);
    Head.pNext->pPrev = newNode;
    Head.pNext = newNode;

    m_size++;
}

void List::push_back(const Circle& data) {
    Node* newNode = new Node(data, Tail.pPrev, &Tail);
    Tail.pPrev->pNext = newNode;
    Tail.pPrev = newNode;

    m_size++;
}

Node* List::find_node(const Circle& data) const {
    Node* current = Head.pNext;

    while (current != &Tail) {
	if (current->m_Data == data) {
	    return current;
	}
	current = current->pNext;
    }

    return nullptr;
}

bool List::remove_first(const Circle& data) {
    Node* node = find_node(data);

    if (node == nullptr) {
	return false;
    }

    delete node;
    m_size--;

    return true;
}

size_t List::remove_all(const Circle& data) {
    size_t remove_cou = 0;

    Node* current = Head.pNext;
    while (current != &Tail) {
	Node* next = current->pNext; //Если текущий удалится, запомнится следующий

	if (current->m_Data == data) {
	    delete current;
	    remove_cou++;
	    m_size--;
	}

	current = next;
    }

    return remove_cou;
}

void List::clear() {
    Node* current = Head.pNext;
    while (current != &Tail) {
	Node* next = current->pNext;
	delete current;
	current = next;
    }

    Head.pNext = &Tail;
    Tail.pPrev = &Head;
    m_size = 0;
}

size_t List::size() const {
    return m_size;
}

bool List::empty() const {
    return m_size == 0;
}

//Сортировка пузырьком
void List::sort_by_area() {
    if (m_size < 2) return;

    bool sw;
    do {
	sw = false;
	Node* current = Head.pNext;

	while (current->pNext != &Tail) {
	    if (current->m_Data.get_area() > current->pNext->m_Data.get_area()) {
		//Данные меняются местами
		Circle temp = current->m_Data;
		current->m_Data = current->pNext->m_Data;
		current->pNext->m_Data = temp;
		sw = true;
	    }
	    current = current->pNext;
	}
    } while (sw);
}

void List::print(std::ostream& os) const {
    Node* current = Head.pNext;
    int ind = 0;

    while (current != &Tail) {
	os << ind << ": " << current->m_Data << std::endl;
	current = current->pNext;
	ind++;
    }
}

std::ostream& operator<<(std::ostream& os, const List& l) {
    l.print(os);
    return os;

}

void List::read_file(const char* filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
	std::cout << "Не удалось открыть файл " << filename << std::endl;
	return;
    }

    clear();

    Circle c;
    while (fin >> c) {
	push_back(c);
    }

    fin.close();
}

void List::write_file(const char* filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
	std::cout << "Не удалось открыть файл " << filename << std::endl;
	return;
    }

    Node* current = Head.pNext;
    while (current != &Tail) {
	fout << current->m_Data.get_center().get_x() << " " << current->m_Data.get_center().get_y() << " " << current->m_Data.get_radius() << std::endl;
	current = current->pNext;
    }

    fout.close();
}
































