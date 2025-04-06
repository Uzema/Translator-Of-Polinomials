#pragma once
#include <vector>
#include "Polynomial.h"

template <class Tkey, class Tvalue>
class SearchTree {

	Node* root;

	struct Node {
		Tkey key;
		Tvalue value;
		Node* left;
		Node* right;
		Node* parent;
	};

private:
	void print(Node* curr) {
		if (!curr) return;
		print(curr->left);
		std::cout << curr->key << "_" << curr->value;
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
			if (!curr->left && !curr->right) {
				delete curr;
				return nullptr;
			}
			if (!curr->left) {
				Node* temp = curr->right;
				delete curr;
				return temp;
			}
			if (!curr->right) {
				Node* temp = curr->left;
				delete curr;
				return temp;
			}
		}
		Node* m = findMax(curr->left);
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

	}

	Node* findMax(Node* curr) {
		if (!curr) return nullptr;
		if (curr->right)
			return findMax(curr->right);
		return curr;
	}
};