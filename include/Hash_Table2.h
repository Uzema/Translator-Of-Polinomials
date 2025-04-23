#pragma once
#include <vector>
//#include <algorithm>
#include <cmath>

template <class Tkey, class Tvalue>
class HashO {
	struct tuple {
		Tkey key;
		Tvalue value;
		bool flag;
		bool empty;

		Tkey getKey() {
			return key;
		}

		Tvalue getValue() {
			return value;
		}

		bool getFlag() {
			return flag;
		}

		bool getEmpty() {
			return empty;
		}

		tuple() {
			flag = false;
			empty = true;
		}

		tuple(Tkey key) {
			this->key = key;
			this->value = Tvalue();
			flag = false;
			empty = true;
		}

		tuple(Tkey key, Tvalue value) {
			this->key = key;
			this->value = value;
			flag = false;
			empty = false;
		}
	};

	std::vector<tuple> table;
	int size;
	int capacity;
	int a, b;
	int simpleNum = 1'000'000'007;

public:

	HashO() {
		table.resize(157);
		capacity = 157;
		std::srand(std::time({}));
		a = abs(std::rand() % (simpleNum) - 1) + 1;
		b = abs(std::rand()) % simpleNum;
	}

	int Hash(std::string s) {
		unsigned long long int x = 0;
		for (int i = 0; i < s.size(); i++) {
			x += (s[i] * (int)pow(31, i)) % simpleNum;
		}
		return ((a * x + b) % simpleNum) % capacity;
	}

	void insert(Tkey key, Tvalue value) {
		if (size == capacity) {
			//repack
		}

		tuple t(key, value);
		int index = Hash(key);

		while (!table[index].getEmpty()) {
			index = (index + 1) % capacity;
			continue;
		}
		if (table[index].getEmpty()) {
			table[index] = t;
			size++;
			return;
		}
	}
	
	tuple find(Tkey key) {
		int index = Hash(key);
		int start_index = index;
		do {
			if (table[index].getEmpty() == false) {
				if (table[index].getKey() == key) {
					return table[index];
				}
				else {
					index = (index + 1) % capacity;
					continue;
				}
			}
			else {
				if (table[index].getFlag() == true) {
					index = (index + 1) % capacity;
					continue;
				}
				else {
					throw "didnt find";
				}
			}
		} while (true);
	}

	void erase(Tkey key) {
		int index = Hash(key);
		do {
			if (tabble[index].getEmpty() == false) {
				if (table[index].getKey() == key) {
					tuple.flag = true;
					tuple.empty = true;
					return;
				}
				else {
					index = (index + 1) % capacity;
					continue;
				}
			}
			else {
				if (table[index].getFlag() == true) {
					index = (index + 1) % capacity;
					continue;
				}
				else {
					throw "didnt find";
				}
			}
		} while (true);
	}


	Tvalue operator[](Tkey key) {
		return find(key).getValue();
	}

};