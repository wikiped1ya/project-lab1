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
// TODO: сделать O(N * log N), которая бы работала быстрее для отсортированного массива
//Разделение списка
Node* split_list(Node* head) {
    if (head == nullptr or head->pNext == nullptr) {
	return nullptr;
    }

    //Медленный указатель
    Node* slow = head;

    //Быстрый указатель
    Node* fast = head->pNext;

    while (fast != nullptr and fast->pNext != nullptr) {
	slow = slow->pNext;
	fast = fast->pNext->pNext;
    }

    Node* second_half = slow->pNext;
    slow->pNext = nullptr;

    return second_half;
}

//Слияние двух списков
Node* merge_list(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node* result = nullptr;

    if (left->m_Data.get_area() <= right->m_Data.get_area()) {
	result = left;
	result->pNext = merge_list(left->pNext, right);
	if (result->pNext != nullptr) {
	    result->pNext->pPrev = result;
	}
    } else {
	result = right;
	result->pNext = merge_list(left, right->pNext);
	if (result->pNext != nullptr) {
	    result->pNext->pPrev = result;
	}
    }

    return result;
}

//Сортировка слиянием
Node* merge_sort(Node* head) {
    if (head == nullptr or head->pNext == nullptr) {
	return head;
    }

    Node* second_half = split_list(head);

    Node* left = merge_sort(head);
    Node* right = merge_sort(second_half);

    return merge_list(left, right);
}

void List::sort_by_area() {
    if (m_size < 2) return;

    //Отсортирован ли список
    bool is_sorted = true;
    Node* check = Head.pNext;
    while (check->pNext != &Tail) {
	if (check->m_Data.get_area() > check->pNext->m_Data.get_area()) {
	    is_sorted = false;
	    break;
	}
	check = check->pNext;
    }

    if (is_sorted) {
	return;
    }

    //Поиск блоков
    Node* runs[1000];
    int run_cou = 0;

    Node* current = Head.pNext;
    while(current != &Tail and run_cou < 1000) {
	runs[run_cou] = current;
	current = extract_next(current);
	run_cou++;
    }

    //Если блок один
    if (run_cou == 1) {
	Node* last = runs[0];
	while (last->pNext != nullptr) {
	    last = last->pNext;
	}
	last->pNext = &Tail;
	Tail.pPrev = last;
	return;
    }

    //Сортировка блоков слиянием
    while (run_cou > 1) {
	int new_cou = 0;

	for (int i = 0; i < run_cou; i +=2) {
	    if (i + 1 < run_cou) {
		runs[new_cou] = merge_list(runs[i], runs[i+1]);
	    } else {
		runs[new_cou] = runs[i];
	    }

	    new_cou++;
	}

	run_cou = new_cou;
    }

    //Подключение отсортированного блока с head и tail
    Node* sorted_head = runs[0];

    Node* last = sorted_head;
    while (last->pNext != nullptr) {
	last = last->pNext;
    }

    Head.pNext = sorted_head;
    sorted_head->pPrev = &Head;

    last->pNext = &Tail;
    Tail.pPrev = last;
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
    // TODO: сделать отдельный метод, который бы получал уже готовый std::istream&
    if (!fin.is_open()) {
	std::cout << "Не удалось открыть файл " << filename << std::endl;
	return;
    }

//    clear();
//
//    Circle c;
//    while (fin >> c) {
//	push_back(c);
//    }

    read(fin);

    fin.close();
}

void List::write_file(const char* filename) const {
    std::ofstream fout(filename);
    // TODO: сделать отдельный метод, который бы получал уже готовый std::ostream&
    if (!fout.is_open()) {
	std::cout << "Не удалось открыть файл " << filename << std::endl;
	return;
    }

//    Node* current = Head.pNext;
//    while (current != &Tail) {
//	fout << current->m_Data.get_center().get_x() << " " << current->m_Data.get_center().get_y() << " " << current->m_Data.get_radius() << std::endl;
//	current = current->pNext;
//    }

    write(fout);

    fout.close();
}

//Новые методы
void List::read(std::istream& is) {
    clear();

    Circle c;
    while (is >> c) {
	push_back(c);
    }
}

void List::write(std::ostream& os) const {
    Node* current = Head.pNext;
    while (current != &Tail) {
	os << current->m_Data.get_center().get_x() << " " << current->m_Data.get_center().get_y() << " " << current->m_Data.get_radius() << std::endl;
	current = current->pNext;
    }
}

//Конструктор копирвоания
List::List(const List& other) : List() {
    Node* current = other.Head.pNext;
    while (current != &other.Tail) {
	push_back(current->m_Data);
	current = current->pNext;
    }
}

//Оператор присваивания
List& List::operator=(const List& other) {
    if (this != &other) {
	clear();

	Node* current = other.Head.pNext;
	while (current != &other.Tail) {
	    push_back(current->m_Data);
	    current = current->pNext;
	}
    }

    return *this;
}

//Конструктор перемещения
List::List(List&& other) : Head(), Tail(), m_size(0) {
    Head.pNext = other.Head.pNext;
    Tail.pPrev = other.Tail.pPrev;
    m_size = other.m_size;

    if (Head.pNext) Head.pNext->pPrev = &Head;
    else Head.pNext = &Tail;

    if (Tail.pPrev) Tail.pPrev->pNext = &Tail;
    else Tail.pPrev = &Head;

    other.Head.pNext = &other.Tail;
    other.Tail.pPrev = &other.Head;
    other.m_size = 0;
}

//Оператор присваивания (перемещение)
List& List::operator=(List&& other) {
    if (this != &other) {
	clear();

	Head.pNext = other.Head.pNext;
        Tail.pPrev = other.Tail.pPrev;
        m_size = other.m_size;

	if (Head.pNext) Head.pNext->pPrev = &Head;
        else Head.pNext = &Tail;

	if (Tail.pPrev) Tail.pPrev->pNext = &Tail;
        else Tail.pPrev = &Head;

	other.Head.pNext = &other.Tail;
        other.Tail.pPrev = &other.Head;
        other.m_size = 0;
    }

    return *this;
}

//Применяет ф-цию к каждому элементу
void List::for_each(std::function<void(Circle&)> func) {
    Node* current = Head.pNext;
    while (current != &Tail) {
	func(current->m_Data);
	current = current->pNext;
    }
}

//Длина возрастабщего блока
int List::get_run_len(Node* start) const {
    if (start == nullptr or start == &Tail) return 0;

    int len = 1;
    Node* current = start;

    while (current->pNext != &Tail and current->m_Data.get_area() <= current->pNext->m_Data.get_area()) {
	len++;
	current = current->pNext;
    }

    return len;
}

//Отделяет первый блок от списка и возвращает указатель на следующий блок
Node* List::extract_next(Node*& current) {
    if (current == nullptr or current == &Tail) return nullptr;

    Node* run_start = current;
    Node* run_end = current;

    while (run_end->pNext != &Tail and run_end->m_Data.get_area() <= run_end->pNext->m_Data.get_area()) {
	run_end = run_end->pNext;
    }

    Node* next_run = run_end->pNext;

    run_end->pNext = nullptr;
    if (next_run != nullptr) {
	next_run->pPrev = nullptr;
    }

    current = next_run;

    return run_start;
}































