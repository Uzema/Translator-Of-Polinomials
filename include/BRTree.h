#pragma once

template <class Tkey, class Tvalue>
class BRtree {
	enum Color { RED, BLACK };
	struct node {
		Tkey key;
		Tvalue value;
		node* left, * right, * parent;
		Color color;
		bool fict;

		node() {
			left   = nullptr;
			fict   = true;
			right  = nullptr;
			color  = BLACK;
			parent = nullptr;
		}
		node(Tkey k, Tvalue val, Color c = BLACK, bool fict = false, node* parent = nullptr) :
			key(k), value(val), color(c), parent(parent) {
			this->fict = fict;
			left = right = nullptr;
		}
		
	};
	node* root;
	size_t sz;

	void createFict(node* x) {
		x->left = new node();
		x->left->parent = x;
		x->right = new node();
		x->right->parent = x;
	}

	void Destr(node* x) {
		if (x->left) return Destr(x->left);
		if (x->right) return Destr(x->right);
		delete x;
	}

	void copy(node* first, node* second) {
		createFict(first);
		first->color  =  second->color;
		first->key    =  second->key;
		first->value  =  second->value;
		first->fict   =  second->fict;

		if (second->left && !second->left->fict)
			copy(first->left, second->left);
		if (second->right && !second->right->fict)
			copy(first->right, second->right);
	}

public:
	class iterator {
	public:
		node* ptr;

		iterator(node* p) : ptr(p) {}

		iterator operator++() {
			if (!ptr->right && !ptr->left && ptr->parent->right == ptr)
				return iterator(nullptr);
			if (ptr->right && !ptr->right->fict) {
				ptr = ptr->right;
				while (!ptr->left->fict)
					ptr = ptr->left;
				return iterator(ptr);
			}
			else {
				node* par = ptr->parent;
				while (par && ptr == par->right) {
					ptr = par;
					par = par->parent;
				}
				ptr = par;
			}
			return iterator(ptr);
		}
		
		bool operator==(const iterator& it) const {
			return ptr == it.ptr;
		}
		bool operator!=(const iterator& it) const {
			return ptr != it.ptr;
		}
		node& operator*() {
			return *ptr;
		}
		node* operator->() {
			return ptr;
		}
		Tkey GetKey() {
			return ptr->key;
		}
	};

	iterator begin() {
		node* cur = root;
		while (cur->left && !cur->left->fict) {
			cur = cur->left;
		}
		return iterator(cur);
	}

	iterator end() {
		return iterator(nullptr);
	}

	BRtree() {
		root = new node();
		sz = 0;
	}

	~BRtree() {
		Destr(root);
	}

	BRtree(const BRtree<Tkey,Tvalue>& t) {
		root = new node();
		root->parent = nullptr;
		sz = t.sz;
		copy(root, t.root);
	}

	BRtree operator=(const BRtree& t) {
		if (this == &t)
			return *this;

		Destr(root);

		root = new node();
		root->parent = nullptr;
		sz = t.sz;
		copy(root, t.root);
		return *this;
	}

private:
	void rotateLeft(node* x) {
		node* y = x->right;

		x->right = y->left;
		if (y->left) y->left->parent = x;

		y->parent = x->parent;
		if (!y->parent) root = y;
		if (x->parent)
			if (x->parent->left == x) x->parent->left = y;
			else x->parent->right = y;

		y->left = x;
		x->parent = y;
	}
	
	void rotateRight(node* x) {
		node* y = x->left;
		
		x->left = y->right;
		if (y->right) y->right->parent = x;

		y->parent = x->parent;
		if (!y->parent) root = y;
		if (x->parent)
			if (x->parent->right == x) x->parent->right = y;
			else x->parent->left = y;

		y->right = x;
		x->parent = y;
	}
	

	void balanceInsert(node* x) {
		if (x->parent == nullptr) {
			x->color = BLACK;
			return;
		}

		if (x->parent->color == BLACK) return;

		if (uncle(x) && uncle(x)->color == RED) {
			x->parent->color         = BLACK;
			uncle(x)->color			 = BLACK;
			x->parent->parent->color = RED;
			balanceInsert(x->parent->parent);
			return;
		}

		if (x->parent->parent && x->parent->parent->left && x->parent == x->parent->parent->left) {
			node* g = x->parent->parent;
			node* p = x->parent;
			if (x == x->parent->right)
				rotateLeft(p);
			x->parent->color = BLACK;
			if(x->parent->parent)
				x->parent->parent->color = RED;
			rotateRight(g);
		}
		else if (x->parent->parent && x->parent->parent->right && x->parent == x->parent->parent->right) {
			node* g = x->parent->parent;
			node* p = x->parent;
			if (x == x->parent->left)
				rotateRight(p);
			x->parent->color = BLACK;
			if(x->parent->parent)
				x->parent->parent->color = RED;
			rotateLeft(g);
		}
	}
	
	node* sibling(node* x) {
		if(x->fict || x->parent->fict) return nullptr;
		if (x->parent->left == x) return x->parent->right;
		else return x->parent->left;
		return nullptr;
	}

	node* uncle(node* x) {
		if (x->parent == nullptr || x->parent->parent == nullptr) return nullptr;
		if (x->parent == x->parent->parent->left)
			return x->parent->parent->right;
		return x->parent->parent->left;
	}

	void balanceErase(node* x) {
		if (!x->fict) return;
		if (x->parent == nullptr) return;

		if (sibling(x) && sibling(x)->color == RED) {
			x->parent->color  = RED;
			sibling(x)->color = BLACK;
			x == x->parent->left ? rotateLeft(x) : rotateRight(x);
		}
		
		node* s = sibling(x);
		if (s && !s->fict && s->color == BLACK && x->parent->color == BLACK && 
			s->left->color == BLACK && s->right->color == BLACK) {
			s->color = RED;
			balanceErase(x->parent);
			return;
		}
		else if (!x->fict && x->parent->left == x) {
			node* s = sibling(x);
			if (!s->fict && s->left && s->right && s->right->color == BLACK && s->left->color == RED) {
				s->color	   = RED;
				s->left->color = BLACK;
				rotateRight(s);
			}
			sibling(x)->color = x->parent->color;
			x->parent->color = BLACK;
			if(!sibling(x)->fict)
				sibling(x)->right->color = BLACK;
			rotateLeft(x->parent);
		}
		else if (!x->fict && x->parent->right == x) {
			node* s = sibling(x);
			if (s && !s->fict && s->right->color == RED && s->left->color == BLACK) {
				s->color		= RED;
				s->right->color = BLACK;
				rotateLeft(s);
			}
			if(sibling(x))
				sibling(x)->color = x->parent->color;
			x->parent->color = BLACK;
			if(sibling(x)->left)
				sibling(x)->left->color = BLACK;
			rotateRight(x->parent);
		}
	}

	node* prInsert(Tkey key, Tvalue val) {
		node* cur = root;
		while (!cur->fict && cur->key != key) {
			if (key < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}

		if (cur->fict == true) {
			cur->key   = key;
			cur->value = val;
			cur->fict  = false;
			cur == root ? cur->color = BLACK : cur->color = RED;
	
			createFict(cur);
			sz++;

			balanceInsert(cur);
		}
		return cur;
	}

	void prErase(Tkey k) {
		node* cur = root;
		while ((cur) && cur->key != k) {
			if (k < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		if (!cur)
			throw "Not existing element";
		node* d = cur;
		if(cur->right && !cur->right->fict)
			cur = cur->right;
		
		while (cur->left && !cur->left->fict)
			cur = cur->left;

		d->value = cur->value;
		d->key   = cur->key;

		
		if (cur->right && !cur->right->fict) {
			cur->right->parent = cur->parent;
			if (cur == cur->parent->right)
				cur->parent->right = cur->right;
			if(cur == cur->parent->left)
				cur->parent->left = cur->right;
		}
		else {
			if (cur == cur->parent->left)
				cur->parent->left = nullptr;
			if (cur == cur->parent->right)
				cur->parent->right = nullptr;
		}

		if (cur->left && cur->left->fict) delete cur->left;
		if (cur->right && cur->right->fict) delete cur->right;
		delete cur;
		sz--;

		balanceErase(d);
	}

public:
	iterator find(Tkey k) {
		node* cur = root;
		while (cur) {
			if (cur->key == k) 
				return iterator(cur);
			else if (cur->key > k)
				cur = cur->left;
			else
				cur = cur->right;
		}
		return iterator(nullptr);
	}

	void insert(Tkey k, Tvalue val) {
		if (find(k) != iterator(nullptr))
			throw "This value is alredy exist";
		node* x = prInsert(k, val);
		if (x == root)
			root->color = BLACK;
	}

	void erase(Tkey key) {
		prErase(key);
	}
	
	size_t size() {
		return sz;
	}

	bool empty() {
		return sz == 0;
	}

	void print() {
		for (auto it = begin(); it != end(); ++it) {
			std::cout << it->key << " = ";
			it->value.print();
		}
		std::cout << size() << " rows\n";
	}
};