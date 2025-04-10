#pragma once
#include<vector>

template <class Tkey, class Tvalue>
class SortedTable {
	std::vector<std::pair<Tkey, Tvalue>> table;
public:
	SortedTable() : table() { }

	class iterator {
	public:
		std::pair<Tkey, Tvalue>* ptr;

		iterator(std::pair<Tkey, Tvalue>* p) : ptr(p) {}

		iterator& operator++() {
			ptr++;
			return *ptr;
		}

		iterator& operator++(int) {
			iterator tmp = *this;
			ptr++;
			return tmp;
		}

		iterator& operator--() {
			ptr--
			return *ptr;
		}

		iterator& operator--(int) {
			iterator tmp = *ptr;
			ptr--;
			return *tmp;
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
		if (table.empty())
			return nullptr;
		return iterator(&table[0]);
	}
	iterator end() {
		if (table.empty())
			return nullptr;
		return iterator(&table[table.size() - 1])++;
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
				throw "This value already exists";
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
			throw "The value does not exist";
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