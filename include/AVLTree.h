#pragma once
#include <vector>
#include <algorithm>

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
		if (!otherCurr) return nullptr;
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
		if (!curr) return nullptr;
		int balance = getBalance(curr);
		if (balance == 2 || balance == -2) {
			if (balance == -2) {
				if (getBalance(curr->left) == 1) {
					curr->left = rotateLeft(curr->left);
					updateHeight(curr->left);
				}
				curr = rotateRight(curr);
				updateHeight(curr);
			}
			else if (balance == 2) {
				if (getBalance(curr->right) == -1) {
					curr->right = rotateRight(curr->right);
					updateHeight(curr->right);
				}
				curr = rotateLeft(curr);
				updateHeight(curr);
			}
		}
		return curr;

	}

	void print(Node* curr) {
		if (!curr) return;
		print(curr->left);
		std::cout << curr->key << " = ";
		curr->value.print();
		//std::cout << std::endl;
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

	Node* insert(Tkey key, Tvalue value, Node* curr) {
		if (!curr) return new Node(key, value);
		if (key == curr->key) {
			throw std::runtime_error("keys must be unique");
		}
		if (key < curr->key) {
			curr->left = insert(key, value, curr->left);
		}
		if (key > curr->key) {
			curr->right = insert(key, value, curr->right);
		}
		updateHeight(curr);
		curr = balance(curr);
		return curr;
	}

	Node* erase(Tkey key, Node* curr) {
		if (!curr) throw std::runtime_error("No node found with that key");
		else if (key < curr->key) {
			curr->left = erase(key, curr->left);
		}
		else if (key > curr->key) {
			curr->right = erase(key, curr->right);
		}
		else {
			if (!curr->left && !curr->right) {//лист
				delete curr;
				return nullptr;
			}
			else if (!curr->left) {//есть правый ребенок
				Node* temp = curr->right;
				delete curr;
				return temp;
			}
			else if (!curr->right) {//есть левый ребенок
				Node* temp = curr->left;
				delete curr;
				return temp;
			}
			else {
				Node* m = findMax(curr->left);//есть оба ребенка
				curr->key = m->key;
				curr->value = m->value;
				curr->left = erase(m->key, curr->left);
			}	
		}
		if (curr) {
			updateHeight(curr);
			curr = balance(curr);
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

	Node* testing(Node* curr) {
		if (!curr) return nullptr;

		if (!(getBalance(curr) == -1 || getBalance(curr) == 0 || getBalance(curr) == 1)) {
			throw std::runtime_error("AVLTree is not properly balanced");
		}

		if (curr->left) {
			if (curr->key <= curr->left->key) throw std::runtime_error("Is not a search tree");
		}

		if (curr->right) {
			if (curr->key >= curr->right->key) throw std::runtime_error("Is not a search tree");
		}

		curr->left = testing(curr->left);
		curr->right = testing(curr->right);
		return curr;
	}

public:

	void testAVLProperties() {
		root = testing(root);
	}

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
		std::cout << size() << " rows\n";
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

	int getHeight() {
		return root->height;
	}
};