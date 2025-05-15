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
	size_t size = 0;
	int capacity;
	int a, b;
	int simpleNum = 1'000'000'007;
	std::vector<int> simpleNums = { 157, 262127, 524287, 786433, 1048609, 1310719, 1572869 };

public:

	HashO() {
		table.resize(157);
		capacity = 157;
		std::srand(std::time({}));
		a = abs(std::rand() % (simpleNum) - 1) + 1;
		b = abs(std::rand()) % simpleNum;
	}

	void repack() {
		if (capacity == simpleNums[simpleNums.size() - 1]) {
			return;
		}
		int newCapacity;
		for (int i = 0; i < simpleNums.size(); i++) {
			if (capacity == simpleNums[i]) {
				newCapacity = simpleNums[i + 1];
				break;
			}
		}
		
		std::vector<tuple> newTable(newCapacity);
		for (int i = 0; i < table.capacity(); i++) {
			if (!table[i].getEmpty()) {
				int newIndex = Hash(table[i].getKey(), newCapacity);

				while (!newTable[newIndex].getEmpty()) {
					newIndex = (newIndex + 1) % newCapacity;
				}

				newTable[newIndex] = table[i];
			}
		}
		table = std::move(newTable);
		capacity = newCapacity;
		
	}

	int Hash(std::string s) {
		unsigned long long int x = 0;
		for (int i = 0; i < s.size(); i++) {
			x += (s[i] * (int)pow(31, i)) % simpleNum;
		}
		return ((a * x + b) % simpleNum) % capacity;
	}

	int Hash(std::string s, int newCapacity) {
		unsigned long long int x = 0;
		for (int i = 0; i < s.size(); i++) {
			x += (s[i] * (int)pow(31, i)) % simpleNum;
		}
		return ((a * x + b) % simpleNum) % newCapacity;
	}

	void print() {
		for (int i = 0; i < capacity; i++) {
			if (table[i].getEmpty() == false) {
				std::cout << table[i].getKey() << " = ";
				table[i].getValue().print();
			}
		}
		std::cout << size << " rows\n";
	}

	void insert(Tkey key, Tvalue value) {

		tuple t(key, value);
		int index = Hash(key);

		while (!table[index].getEmpty()) {
			if (table[index].getKey() == key) {
				table[index] = t;
				break;
			}
			index = (index + 1) % capacity;
			continue;
		}
		if (table[index].getEmpty()) {
			table[index] = t;
			size++;
		}

		if ((double)size / (double)capacity > 0.6f) {
			repack();
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
					throw std::runtime_error("didnt find");
				}
			}
		} while (true);
	}

	void erase(Tkey key) {
		int index = Hash(key);
		do {
			if (table[index].getEmpty() == false) {
				if (table[index].getKey() == key) {
					table[index].flag = true;
					table[index].empty = true;
					size--;
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
					throw std::runtime_error("didnt find");
				}
			}
		} while (true);
	}

	size_t getSize() {
		return size;
	}

	Tvalue operator[](Tkey key) {
		return find(key).getValue();
	}
};