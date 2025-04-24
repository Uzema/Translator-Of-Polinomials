#pragma once

#include "translator.h"

class UserInterface {
	enum Status { ST, UT, BR, AV, HT, HO };

	SortedTable<std::string, polynom> st;
	UnsortedTable<std::string, polynom> ut;
	BRtree<std::string, polynom> br;
	AVLTree<std::string, polynom> av;
	HashTable<std::string, polynom> ht;
	HashO<std::string, polynom> ho;
	Status status;

public:

	void process(std::string inp) {
		inp.erase(std::remove_if(inp.begin(), inp.end(), ::isspace), inp.end());

		if (inp.size() > 4 && inp.substr(0, 4) == "show") {
			print(inp.substr(4, inp.size() - 1));
		}
		else if (inp == "show") {
			print();
		}
		else if (inp == "status") {
			stat();
		}
		else if (inp.size() > 6 && inp.substr(0, 6) == "switch") {
			sw(inp.substr(6, inp.size() - 1));
		}
		else if (inp.size() > 3 && inp.substr(0, 3) == "del") {
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
		AVLTree<std::string, polynom> av;
		HashTable<std::string, polynom> ht;
		HashO<std::string, polynom> ho;
		status = ST;
	}

private:

	void print(std::string inp = "-1") {
		int s = std::stoi(inp);
		if (status == ST) st.print(s);
		if (status == UT) ut.print();
		if (status == BR) br.print();
		if (status == AV) av.print();
		if (status == HT) ht.print();
		if (status == HO) ho.print();
	}

	void stat() {
		if (status == ST) std::cout << "Sorted Table\n";
		if (status == UT) std::cout << "Unsorted Table\n";
		if (status == BR) std::cout << "Red Black tree\n";
		if (status == AV) std::cout << "AVL tree\n";
		if (status == HT) std::cout << "Chained Hash Table\n";
		if (status == HO) std::cout << "Probing Hash Table\n";
	}

	void sw(std::string inp) {
		if (inp == "SortedTable" || inp == "st") status = ST;
		else if (inp == "UnsortedTable" || inp == "ut") status = UT;
		else if (inp == "BRtree" || inp == "br") status = BR;
		else if (inp == "AVLtree" || inp == "av") status = AV;
		else if (inp == "ChainedHashTable" || inp == "ht" || inp == "h1") status = HT;
		else if (inp == "ProbingHashTable" || inp == "ho" || inp == "h2") status = HO;
		else std::cout << "Incorrect switch\n";
	}

	void erase(std::string inp) {
		if (status == ST) st.erase(inp);
		if (status == UT) ut.erase(inp);
		if (status == BR) br.erase(inp);
		if (status == AV) av.erase(inp);
		if (status == HT) ht.erase(inp);
		if (status == HO) ho.erase(inp);
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
		if (status == UT) ut.insert(name, p);
		if (status == BR) br.insert(name, p);
		if (status == AV) av.insert(name, p);
		if (status == HT) ht.insert(name, p);
		if (status == HO) ho.insert(name, p);
	}

	void calc(std::string inp) {
		polynom res = Translator(inp);
		res.print();
	}
};