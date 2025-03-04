#pragma once
#include<vector>
#include"Polynomial.h"

template <class Tkey, class Tvalue>
class SortedTable {
	std::vector<std::pair<Tkey, Tvalue>> table;
public:
	SortedTable() : table() { }

	class iterator {
	public:
		std::pair<Tkey, Tvalue> ptr;

		iterator(std::pair<Tkey, Tvalue>* p) {
			ptr = p;
		}

		iterator& operator++() {
			return ptr++;
		}
		iterator& operator--() {
			return ptr--;
		}
		bool operator==(iterator& it) {
			return ptr == it.ptr;
		}
		bool operator!=(iterator& it) {
			return ptr != it.ptr;
		}
		std::pair<Tkey, Tvalue>& operator*() {
			return *ptr;
		}
		std::pair<Tkey, Tvalue>* operator->() {
			return ptr;
		}
	};

	iterator begin() {
		return iterator(&table[0]);
	}
	iterator end() {
		return iterator(&table[table.size()]);
	}

};