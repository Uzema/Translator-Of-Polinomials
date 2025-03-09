#pragma once
#include<vector>
#include"Polynomial.h"

//TODO: write throw 

template <class Tkey, class Tvalue>
class SortedTable {
	std::vector<std::pair<Tkey, Tvalue>> table;
public:
	SortedTable() : table() { }

	class iterator {
	public:
		std::pair<Tkey, Tvalue>* ptr;

		explicit iterator(std::pair<Tkey, Tvalue>* p) : ptr(p) { }

		iterator& operator++() {
			return ptr++;
		}
		iterator& operator--() {
			return ptr--;
		}
		bool operator==(const iterator& it) const{
			return ptr == it.ptr;
		}
		bool operator!=(const iterator& it) const {
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
		return iterator(nullptr);
	}
	
	void insert(Tkey key, Tvalue val) {
		table.push_back(std::make_pair(key, val));
		int i = table.size() - 1;
		if (i == 0)
			return;
		while (i > 0) {
			if (table[i - 1].first > table[i].first) {
				std::swap(table[i - 1], table[i]);
				i--;
			}
			else if (table[i - 1].first == table[i].first)
				throw " ";
			else
				break;
		}
	}

	iterator find(const Tkey& key) {
		int l = 0, r = table.size() - 1;
		while (l <= r) {
			int center = (l + r) / 2;
			if (table[center].first == key)
				return iterator(&table[center]);

			else if (table[center].first < key)
				l = center + 1;
			else
				r = center - 1;
		}
		return end();
	}

	iterator erase(const Tkey& key) {
		auto it = find(key);
		if (it == end())
			throw " ";
		for (int i = 0; i < table.size();i++) {
			if (table[i].first == key) {
				table.erase(table.begin() + i);
				break;
			}
		}
		return it;
	}

	std::pair<Tkey, Tvalue> operator[](int ind){
		return table[ind];
	}

	int size() {
		return table.size();
	}
};