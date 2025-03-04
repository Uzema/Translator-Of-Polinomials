#ifndef __TList_H__
#define __TList_H__

#include <string>

template <typename T>
class List{
	struct node {
		T value;
		node* next;
		node() {
			next = nullptr;
		}
		node(T val, node* adr) {
			value = val;
			next = adr;
		}
	};
	node* head;
public:
	class iterator {
	protected:
		node* curr;
	public:
		explicit iterator(node* node) : curr(node) {}
		iterator& operator++() {
			curr = curr->next;
			return *this;
		}
		iterator operator++(int) {
			iterator copy = *this;
			curr = curr->next;
			return copy;
		}
		T& operator*() {
			return curr->value;
		}
		T* operator->() {
			return &(curr->value);
		}
		node* get_node() {
			return curr;
		}
		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return it1.curr != it2.curr;
		}
		friend bool operator==(const iterator& it1, const iterator& it2) {
			return it1.curr == it2.curr;
		}
	};
	iterator begin() {
		return iterator(head->next);
	}
	iterator end() {
		return iterator(head);
	}

	List();
	List(int n, T deflt = T());
	~List();
	List(const List& l);
	List operator=(const List& l);
	T& operator[](int index);
	size_t size();
	void print();

	node* insert(T val, node* pr) {
		node* tmp = new node;
		tmp->next = pr->next;
		pr->next = tmp;
		tmp->value = val;
		return tmp;
	}
	
	node* erase(node* n) {
		if (n->next == head) throw std::exception("erase a non existing element");
		node* ne = n->next;
		n->next = ne->next;
		delete ne;
		return n->next;
	}

	node* find(T val) {
		node* cur = head->next;
		while (cur != head) {
			if (cur->value == val)
				return cur;
			cur = cur->next;
		}
		return nullptr;
	}

	node* get_head() {
		return head;
	}
};

template <class T>
inline List<T>::List() {
	head = new node;
	head->next = head;
}

template <class T>
inline List<T>::List(int n, T deflt = T()) {
	if (n < 0) throw std::exception("List size should be non negative");
	if (n == 0) {
		head = new node;
		head->next = head;
		return;
	}

	head = new node;
	head->next = new node(deflt, nullptr);
	node* cur = head->next;

	for (int i = 1; i < n; ++i) {
		node* tmp = new node(deflt, nullptr);
		cur->next = tmp;
		cur = cur->next;
	}

	cur->next = head;
}

template <class T>
inline List<T>::List(const List& l) {
	head = new node;
	head->next = new node(l.head->next->value, nullptr);
	node* cur = head->next;
	node* ocur = l.head->next;
	while (ocur->next != l.head) {
		cur->next = new node(ocur->next->value, nullptr);
		cur = cur->next;
		ocur = ocur->next;
	}
	cur->next = head;
}

template <class T>
inline List<T>::~List() {
	if (head == head->next) {
		delete head;
		return;
	}

	node* first = head->next;
	while(first != head) {
		node* second = first->next;
		delete first;
		first = second;
	}
	delete head;
}

template <class T>
inline void List<T>::print() {
	node* cur = head->next;
	while (cur != head) {
		std::cout << cur->value << ' ';
		cur = cur->next;
	}
	std::cout << std::endl;
}

template<class T>
inline size_t List<T>::size() {
	int s = 0;
	node* cur = head->next;
	while (cur != head) {
		s++;
		cur = cur->next;
	}
	return s;
}

template <class T>
inline List<T> List<T>::operator=(const List<T>& l) {
	if (this == &l) {
		return *this;
	}
	
	node* first = head->next;
	while (first != head) {
		node* second = first->next;
		delete first;
		first = second;
	}

	node* ocur = l.head->next;
	head->next = new node(ocur->value, nullptr);
	node* cur  = head->next;

	while (ocur->next != l.head) {
		cur->next = new node(ocur->next->value, nullptr);
		cur = cur->next;
		ocur = ocur->next;
	}

	cur->next = head;
	return *this;
}

template <class T>
inline T& List<T>::operator[](int ind) {
	if (ind < 0) throw std::exception("out_of_range");

	node* cur = head->next;
	for (int i = 0; cur != head; i++) {
		if (i == ind)
			return cur->value;

		cur = cur->next;
	}
	throw std::exception("out_of_range");
}

#endif
