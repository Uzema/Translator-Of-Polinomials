#pragma once
#include <vector>

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

		pointer get_ptr() {
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
			throw std::runtime_error("Element with this key exists already");
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
			throw std::runtime_error("Element doesnt exist");
		}
		return erase(it);
	}

	iterator erase(iterator it) {
		if (it == end()) {
			throw std::runtime_error("");
		}
		int index = it.get_ptr() - &table[0];
		table.erase(table.begin() + index);
		return iterator(index < table.size() ? &table[index] : nullptr);
		//can use swap and pop back to make erase(it) O(1)
	}

	std::pair<Tkey, Tvalue> operator[](int ind) {
		return table[ind];
	}

	int size() {
		return table.size();
	}

	void print(int n = -1) {
		int x = n;
		if (n == -1) {
			x = size();
			n = x;
		}
		if (n > size() || n < 0) {
			std::cout << "Out of range\n";
			return;
		}
		for (auto it = begin(); it != end(); ++it, n--) {
			if (n <= 0) break;
			std::cout << it->first << " = ";
			it->second.print();
		}
		std::cout << x << " rows\n";
	}

};