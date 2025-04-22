#pragma once

#include "translator.h"

class UserInterface {
	enum Status { ST, UT, BR, AV, HC, HO };

	SortedTable<std::string, polynom> st;
	UnsortedTable<std::string, polynom> ut;
	BRtree<std::string, polynom> br;
	HashTable<std::string, polynom> ht;
	Status status;

public:

	void process(std::string inp) {
		inp.erase(std::remove_if(inp.begin(), inp.end(), ::isspace), inp.end());

		if (inp.size() >= 4 && inp.substr(0, 4) == "show") {
			print(inp.substr(4, inp.size() - 1));
		}
		else if (inp.size() >= 6 && inp.substr(0, 6) == "switch") {
			sw(inp.substr(6, inp.size() - 1));
		}
		else if (inp.size() >= 3 && inp.substr(0, 3) == "del") {
			erase(inp.substr(3, inp.size() - 1));
		}
		else {
			int eq = -1;
			for (int i = 0; i < inp.size(); i++) {
				if (inp[i] == '=') {
					eq = i;
					break;
				}
			}
			if (eq != -1)
				insert(inp, eq);
			else
				calc(inp);
		}
	}

	UserInterface() {
		SortedTable<std::string, polynom> st;
		UnsortedTable<std::string, polynom> ut;
		BRtree<std::string, polynom> br;
		HashTable<std::string, polynom> ht;
		status = ST;
	}
	polynom get(std::string key) {
		if (status == ST) {
			if (st.find(key) != st.end())
				st.find(key)->second.print();
			else std::cout << "Element is not exist\n";
		}
		if (status == BR) {
			if (br.find(key) != br.end())
				br.find(key)->value.print();
			else std::cout << "Element is not exist\n";
		}
		if (status == HO) ht.find(key);
		if (status == UT) {
			if (ut.find(key) != ut.end())
				ut.find(key)->second.print();
			else std::cout << "Element is not exist\n";
		}
	}
private:


	void print(std::string inp) {

	}

	void sw(std::string inp) {
		if (inp == "SortedTable") status = ST;
		else if (inp == "UnsortedTable") status = UT;
		else if (inp == "BRtree") status = BR;
		else if (inp == "AVLtree") status = AV;
		else if (inp == "ChainedHashTable") status = HC;
		else if (inp == "ProbingHashTable") status = HO;
		else std::cout << "Incorrect switch\n";
	}

	void erase(std::string inp) {
		if (status == ST) st.erase(inp);
		if (status == BR) br.erase(inp);
		if (status == HO) ht.erase(inp);
		if (status == UT) ut.erase(inp);
	}

	void insert(std::string inp, int eq) {
		std::string name = inp.substr(0, eq);
		polynom p;
		try {
			p.parser(inp.substr(eq + 1, inp.size() - 1));
		}
		catch (const std::exception& e) {
			try {
				p = Translator(inp.substr(eq + 1, inp.size() - 1));
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
		
		vars[name] = p;
		if (status == ST) st.insert(name, p);
		if (status == BR) br.insert(name, p);
		if (status == HO) ht.insert(name, p);
		if (status == UT) ut.insert(name, p);
	}

	void calc(std::string inp) {
		polynom res = Translator(inp);
		res.print();
	}
};