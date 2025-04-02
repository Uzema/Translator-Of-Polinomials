#pragma once
#include <vector>
#include "Polynomial.h"

template <class Tkey, class Tvalue>
class SearchTree {

	Node* root;

	struct Node {
		std::pair<Tkey, Tvalue> data;
		Node* left;
		Node* right;
		Node* parent;
	};

public:
	Node* find(Tkey key) {
		return find(key, root);
	}

private:
	Node* find(Tkey key Node* cur);
};