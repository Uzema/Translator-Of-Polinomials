#pragma once
#include <vector>
#include <random>
#include <list>

template<class Tkey, class Tvalue>
class HashTable {
	std::vector<std::list<std::pair<Tkey, Tvalue>>> table;
	size_t sz;
	long long a, b;
	int SimpleNum = 1000000007;
	int capacity;
	std::vector<int> sn = { 157, 262127, 524287, 786433, 1048609, 1310719, 1572869 };

	int hash(std::string s) {
		long long x = 0;
		for (int i = 0; i < s.size(); i++)
			x += (s[i] * (int)pow(31,i)) % SimpleNum;
		return ((a*x+b)%SimpleNum)%capacity;
	}
	
	int hash(std::string s, int c) {
		long long x = 0;
		for (int i = 0; i < s.size(); i++)
			x += (s[i] * (int)pow(31,i)) % SimpleNum;
		return ((a*x+b)%SimpleNum)%c;
	}

	void repack() {
		if (capacity == sn[sn.size()-1])
			return;
		int newcapacity = sn[0];
		for (int i = 0; i < sn.size(); i++) {
			if (sn[i] == capacity) {
				newcapacity = sn[i + 1];
				break;
			}
		}
		std::vector<std::list<std::pair<Tkey, Tvalue>>> newtable(newcapacity);
		for (iterator it = begin(); it != end(); ++it) {
			int t = hash(it->first, newcapacity);
			newtable[t].push_front(std::make_pair(it->first, it->second));
		}
		capacity = newcapacity;
		table = std::move(newtable);
	}

public:
	HashTable(int s = 157) {
		srand(time(0));
		a = (abs(rand()) % (SimpleNum-1)) + 1;
		b = abs(rand()) % SimpleNum;
		sz = 0;
		capacity = s;
		table.resize(s);
	}
	
	class iterator{
		friend class HashTable;
		int index;
		int capacity;
		typename std::list<std::pair<Tkey, Tvalue>>::iterator it;
		std::vector<std::list<std::pair<Tkey, Tvalue>>>* table;

		iterator() = delete;
		iterator(int index,
			typename std::list<std::pair<Tkey, Tvalue>>::iterator it,
			std::vector<std::list<std::pair<Tkey, Tvalue>>>* table) {
			this->index = index;
			this->table = table;
			this->it = it;
			this->capacity = table->size();
		}
	public:
		iterator& operator++() {
			if (index >= capacity-1 && it == (*table)[index].end())
				return *this;
			it++;
			if (it != (*table)[index].end())
				return *this;
			
			index++;
			while (index < capacity && (*table)[index].empty()) {
				index++;
			}
			if (index >= capacity - 1 && (*table)[capacity - 1].empty()) {
				index = capacity - 1;
				it = (*table)[capacity - 1].end();
			}
			else				
				it = (*table)[index].begin();
			
			return *this;
		}

		bool operator==(const iterator& itr) const {
			return itr.index == index && it == itr.it;
		}
		bool operator!=(const iterator& itr) const {
			return !operator==(itr);
		}

		std::pair<Tkey, Tvalue>& operator*() {
			return *it;
		}
		std::pair<Tkey, Tvalue>* operator->() {
			return &(*it);
		}
	};

	iterator begin() {
		if (sz == 0)
			return end();
		int index = 0;
		while (table[index].empty()) {
			index++;
		}
		if (index >= table.size()) return end();
		return iterator(index,table[index].begin(),&table);
	}

	iterator end() {
		return iterator(table.size()-1, table[table.size() - 1].end(), &table);
	}

	void insert(Tkey k, Tvalue v) {
		int index = hash(k);
		if (find(k) != end())
			throw "This value already exists";
		table[index].push_front(std::make_pair(k, v));
		sz++;
		if ((double)sz / (double)capacity > 0.6f)
			repack();
	}

	iterator find(Tkey k) {
		int i = hash(k);
		typename std::list<std::pair<Tkey,Tvalue>>::iterator it = table[i].begin();
		while (it != table[i].end()) {
			if (it->first == k)
				return iterator(i, it, &table);
			it++;
		}
		return end();
	}

	void erase(Tkey k) {
		int index = hash(k);
		typename std::list<std::pair<Tkey, Tvalue>>::iterator it = table[index].begin();
		for (; it != table[index].end(); it++) {
			if (it->first == k) {
				table[index].erase(it);
				sz--;
				return;
			}
		}
		throw "The value does not exist";
	}

	size_t size() {
		return sz;
	}

	void print() {
		for (auto it = begin(); it != end(); ++it) {
			std::cout << it->first << " = ";
			it->second.print();
		}
		std::cout << sz << " rows\n";
	}
};