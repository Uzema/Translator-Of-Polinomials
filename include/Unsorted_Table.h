#pragma once
#include <vector>
#include "Polynomial.h"

template <class Tkey, class Tvalue>
class UnsortedTable {
	std::vector<std::pair<Tkey, Tvalue>> table;
public:
	UnsortedTable() : table() { }

	class iterator {
	public:
		using value_type = std::pair<Tkey, Tvalue>;
		using pointer = value_type*;
		using reference = value_type&;

	private:
		pointer ptr;

	public:
		explicit iterator(pointer p) : ptr(p) { }

		iterator& operator++() {
			++ptr;
			return *this;
		}

		iterator operator++(int) {
			iterator temp = *this;
			++ptr;
			return temp;
		}

		iterator& operator--() {
			--ptr;
			return *this;
		}

		iterator operator--(int) {
			iterator temp = *this;
			--ptr;
			return temp;
		}

		bool operator==(const iterator& it) const {
			return ptr == it.ptr;
		}

		bool operator!=(const iterator& it) const {
			return ptr != it.ptr;
		}

		reference operator*() {
			return *ptr;
		}

		pointer operator->() {
			return ptr;
		}
	};

	iterator begin() {
		return iterator(table.empty() ? nullptr : &table[0]);
	}
	iterator end() {
		return iterator(table.empty() ? nullptr : &table[0] + table.size());
	}

	void insert(Tkey key, Tvalue val) {
		if (find(key) == end()) {
			table.push_back(std::make_pair(key, val));
		}
		else {
			throw "Element with this key exists already";
		}
	}

	iterator find(Tkey key) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->first == key) {
				return it;
			}
		}
		return end();
	}

	iterator erase(Tkey key) {
		auto it = find(key);
		if (it == end()) {
			throw "Element doesnt exist";
		}
		for (int i = 0; i < table.size() - 1; i++) {
			if (table[i].first == key) {
				table.erase(table.begin() + i);
				break;
			}
		}
		return it;

	}

	std::pair<Tkey, Tvalue> operator[](int ind) {
		return table[ind];
	}

	int size() {
		return table.size();
	}

};