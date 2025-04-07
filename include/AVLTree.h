#pragma once
#include <vector>
#include <algorithm>
#include "Polynomial.h"


template <class Tkey, class Tvalue>
class SearchTree {

	struct Node {
		Tkey key;
		Tvalue value;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;

		Node(Tkey key) {
			this->key = key;
			this->value = Tvalue();
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	Node* root = nullptr;

private:
	void print(Node* curr) {
		if (!curr) return;
		print(curr->left);
		std::cout << curr->key << "_" << curr->value << " ";
		print(curr->right);
	}

	Node* find(Tkey key, Node* curr) {
		if (!curr) return nullptr;
		if (key == curr->key)
			return curr;
		if (key < curr->key)
			return find(key, curr->left);
		return find(key, curr->right);
	}

	Node* insert(Tkey key, Node* curr) {
		if (!curr) return new Node(key);//delete
		if (key == curr->key)
			throw "keys must be unique";
		if (key < curr->key)
			curr->left = insert(key, curr->left);
		else if (key > curr->key)
			curr->right = insert(key, curr->right);
		return curr;
	}

	Node* erase(Tkey key, Node* curr) {
		if (!curr) throw 1;
		if (key < curr->key) {
			curr->left = erase(key, curr->left);
			return curr;
		}
		if (key > curr->key) {
			curr->right = erase(key, curr->right);
			return curr;
		}
		if (key == curr->key) {
			if (!curr->left && !curr->right) {//лист
				delete curr;
				return nullptr;
			}
			if (!curr->left) {//есть правый ребенок
				Node* temp = curr->right;
				delete curr;
				return temp;
			}
			if (!curr->right) {//есть левый ребенок
				Node* temp = curr->left;
				delete curr;
				return temp;
			}
		}
		Node* m = findMax(curr->left);//есть оба ребенка
		curr->key = m->key;
		curr->left = erase(m->key, curr->left);
		return curr;
	}

public:
	void print() {
		print(root);
	}

	Node* find(Tkey key) {
		return find(key, root);
	}

	Node* insert(Tkey key) {
		root = insert(key, root);
		return find(key);
	}

	Node* erase(Tkey key) {
		return erase(key, root);
	}

	Node* findMax(Node* curr) {
		if (!curr) return nullptr;
		if (curr->right)
			return findMax(curr->right);
		return curr;
	}
};

template <class Tkey, class Tvalue>
class AVLTree {

	struct Node {
		Tkey key;
		Tvalue value;
		int height = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(Tkey key) {
			this->key = key;
			this->value = Tvalue();
			this->left = nullptr;
			this->right = nullptr;
		}

		Node(Tkey key, Tvalue value) {
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	Node* root = nullptr;

private:

	void deleteTree(Node* curr) {
		if (!curr) return;
		deleteTree(curr->left);
		deleteTree(curr->right);
		delete curr;
	}

	Node* copyTree(Node* otherCurr) {
		Node* newCurr = new Node(otherCurr->key, otherCurr->value);
		newCurr->left = copyTree(otherCurr->left);
		newCurr->right = copyTree(otherCurr->right);
		newCurr->height = otherCurr->height;
		return newCurr;
	}

	int getHeight(Node* curr) {
		return (curr == nullptr ? -1 : curr->height);
	}

	void updateHeight(Node* curr) {
		curr->height = std::max(getHeight(curr->left), getHeight(curr->right)) + 1;
	}

	int getBalance(Node* curr) {
		return (curr == nullptr ? 0 : getHeight(curr->right) - getHeight(curr->left));
	}

	/*void swap(Node* a, Node* b) {
		Tkey a_key = a->key;
		a->key = b->key;
		b->key = a_key;
		Tvalue a_value = a->value;
		a->value = b->value;
		b->value = a_value;
	}*/

	Node* rotateRight(Node* a) {
		Node* b = a->left;
		a->left = b->right;
		b->right = a;
		updateHeight(a);
		updateHeight(b);
		return b;
	}

	Node* rotateLeft(Node* a) {
		Node* b = a->right;
		a->right= b->left;
		b->left = a;
		updateHeight(a);
		updateHeight(b);
		return b;
	}
	
	Node* balance(Node* curr) {
		int balance = getBalance(curr);
		if (balance == 2 || balance == -2) {

			if (balance == -2) {
				if (getBalance(curr->left) == 1) {
					curr->left = rotateLeft(curr->left);
				}
				curr = rotateRight(curr);
				return curr;
			}
			if (balance == 2) {
				if (getBalance(curr->right) == -1) {
					curr->right = rotateRight(curr->left);
				}
				curr = rotateLeft(curr);
				return curr;
			}
		}
		return curr;

	}

	void print(Node* curr) {
		if (!curr) return;
		print(curr->left);
		std::cout << curr->key << "_" << curr->value << " ";
		print(curr->right);
	}

	Node* find(Tkey key, Node* curr) {
		if (!curr) return nullptr;
		if (key == curr->key)
			return curr;
		if (key < curr->key)
			return find(key, curr->left);
		return find(key, curr->right);
	}

	//Node* insert(Tkey key, Node* curr) {
	//	if (!curr) return new Node(key);//delete
	//	if (key == curr->key)
	//		throw "keys must be unique";
	//	if (key < curr->key)
	//		curr->left = insert(key, curr->left);
	//	else if (key > curr->key)
	//		curr->right = insert(key, curr->right);
	//	return curr;
	//}

	Node* insert(Tkey key, Tvalue value, Node* curr) {
		if (!curr) return new Node(key, value);
		if (key == curr->key) {
			throw "keys must be unique";
		}
		if (key < curr->key) {
			curr->left = insert(key, value, curr->left);
			curr->left = balance(curr->left);
		}
		if (key > curr->key) {
			curr->right = insert(key, value, curr->right);
			curr->right = balance(curr->right);
		}
		updateHeight(curr);
		curr = balance(curr);
		return curr;
	}

	Node* erase(Tkey key, Node* curr) {
		if (!curr) throw "No node found with that key";
		if (key < curr->key) {
			curr->left = erase(key, curr->left);
			return curr;
		}
		if (key > curr->key) {
			curr->right = erase(key, curr->right);
			return curr;
		}
		if (key == curr->key) {
			if (!curr->left && !curr->right) {//лист
				delete curr;
				return nullptr;
			}
			if (curr->left && curr->right) {
				Node* m = findMax(curr->left);//есть оба ребенка
				curr->key = m->key;
				curr->left = erase(m->key, curr->left);
				return curr;
			}
			if (!curr->left) {//есть правый ребенок
				Node* temp = curr->right;
				delete curr;
				return temp;
			}
			if (!curr->right) {//есть левый ребенок
				Node* temp = curr->left;
				delete curr;
				return temp;
			}
			
		}
		if (!curr) {
			updateHeight(curr);
			balance(curr);
		}
		return curr;
	}

	Node* findMax(Node* curr) {
		if (!curr) return nullptr;
		if (curr->right)
			return findMax(curr->right);
		return curr;
	}

	int countSize(Node* curr) {
		if (curr == nullptr) return 0;
		return (1 + countSize(curr->left) + countSize(curr->right));
	}

public:

	AVLTree() {

	}

	~AVLTree() {
		deleteTree(root);
	}

	AVLTree(const AVLTree& other) {
		root = copyTree(other.root);
	}

	AVLTree& operator=(const AVLTree& other) {
		if (this != &other) {
			deleteTree(root);
			root = copyTree(other.root);
		}
		return *this;
	}

	void print() {
		print(root);
	}

	Node* find(Tkey key) {
		return find(key, root);
	}

	Node* insert(Tkey key, Tvalue value) {
		root = insert(key, value, root);
		return find(key);
	}

	Node* erase(Tkey key) {
		return erase(key, root);
	}

	int size() {
		return countSize(root);
	}

	bool empty() {
		if (root == nullptr) return true;
		return false;
	}

	Tvalue getValue(Tkey key) {
		return find(key)->value;
	}

	int getTreeHeight() {
		return root->height;
	}
};