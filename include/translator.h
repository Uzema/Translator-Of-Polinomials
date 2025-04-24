#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include "stack.h"
#include "Polynomial.h"
#include "Sorted_Table.h"
#include "Unsorted_Table.h"
#include "Hash_Table1.h"
#include "Hash_Table2.h"
#include "BRTree.h"
#include "AVLTree.h"

class term {
	term *obj;
public:
	virtual ~term(){
		delete obj;
	}
	virtual std::string GetType() {
		return "term";
	}
};

class operation : public term {
	int pr = 0;
public:
	std::string GetType() {
		return "operation";
	}
	virtual int priority() {
		return this->pr;
	}
	virtual polynom calc(polynom x, polynom y) = 0;
};

class operand : public term{
	double val = 0;
public:
	virtual std::string GetType() {
		return "operand";
	}
	virtual double value() {
		return val;
	}
};

class openbracket : public term {
public:
	std::string GetType() override{
		return "openbracket";
	}
};

class closebracket : public term {
public:
	std::string GetType() override{
		return "closebracket";
	}
};

static std::map<std::string, polynom> vars;

class var : public operand {
	polynom val;
	std::string name;
public:
	var(std::string n, polynom p) {
		name = n;
		val = p;
	}
	var(polynom p) {
		val = p;
	}
	var() {	}
	polynom getvalue(){
		return val;
	}
	std::string GetName(){
		return name;
	}
	std::string GetType() override{
		return "var";
	}
};

class add : public operation {
	int pr = 1;
public:
	int priority() {
		return this->pr;
	}
	polynom calc(polynom x, polynom y) override{
		return x + y;
	}
};

class divn : public operation {
	int pr = 2;
public:
	int priority() {
		return this->pr;
	}
	polynom calc(polynom x, polynom y) override {
		return x / y[0].GetCoefficient();
	}
};

class sub : public operation {
	int pr = 1;
public:
	int priority() {
		return this->pr;
	}
	std::string GetType() override {
		return "sub";
	}
	polynom calc(polynom x, polynom y) override{
		return x - y;
	}
};

class mul : public operation {
	int pr = 2;
public:
	int priority() {
		return this->pr;
	}
	polynom calc(polynom x, polynom y) override {
		return x * y;
	}
};

class eq : public term {
	int pr = 0;
public:
	int priority() {
		return this->pr;
	}

	std::string GetType() {
		return "eq";
	}
};

static std::vector<term*> LexicalAnalyser(std::string str) {
	std::vector<term*> res;

	for (int i = 0; i < str.size(); i++) {

		if (str[i] >= '0' && str[i] <= '9') {
			std::string numstr;
			int f = 1; 

			while (str[i] >= '0' && str[i] <= '9' || str[i]== ',' || str[i] == '.') {
				numstr.push_back(str[i]);
				if (str[i] == '.' || str[i] == ',') f--;
				i++;
			}

			if (f >= 0){
				res.push_back(new var(polynom(monom(stod(numstr),0))));
			}

			else throw "Error";
		}

		if (str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z') {
			std::string name;

			while (str.size() > i && str[i] != '+' && str[i] != '-' && 
					str[i] != '*' && str[i] != ')' && str[i] != '/' &&
					str[i] != '=' && str[i] != ' ' && str[i] != '(') {
				name.push_back(str[i]);
				i++;
			}
			
			res.push_back(new var(name, vars[name]));
		}

		if (str[i] == '+')
			res.push_back(new add);

		if (str[i] == '-')
			res.push_back(new sub);

		if (str[i] == '/')
			res.push_back(new divn);

		if (str[i] == '*')
			res.push_back(new mul);

		if (str[i] == '(')
			res.push_back(new openbracket);

		if (str[i] == ')')
			res.push_back(new closebracket);
		
		if (str[i] == '=')
			res.push_back(new eq);
	}

	return res;
}

static bool Parser(std::vector<term*> vcr) {
	enum class State{ S0, Q1, Q2, Q3, Q4, V, U, Eq, Error };
	State ka = State::S0;

	for (int i = 0; i < vcr.size(); i++) {
		switch (ka) {

		case State::S0:
			if (vcr[i]->GetType() == "operand")
				ka = State::Q1;
			else if (vcr[i]->GetType() == "var")
				ka = State::V;
			else if (vcr[i]->GetType() == "openbracket")
				ka = State::Q2;
			else if (vcr[i]->GetType() == "sub")
				ka = State::U;
			else
				ka = State::Error;
			continue;

		case State::Q1:
			if (vcr[i]->GetType() == "operation" || vcr[i]->GetType() == "sub")
				ka = State::Q3;
			else if (vcr[i]->GetType() == "closebracket")
				ka = State::Q4;
			else
				ka = State::Error;
			continue;

		case State::V:
			if (vcr[i]->GetType() == "operation" || vcr[i]->GetType() == "sub")
				ka = State::Q3;
			else if (vcr[i]->GetType() == "closebracket")
				ka = State::Q4;
			else if (vcr[i]->GetType() == "eq")
				ka = State::Eq;
			else
				ka = State::Error;
			continue;

		case State::Q2:
			if (vcr[i]->GetType() == "openbracket")
				ka = State::Q2;
			else if (vcr[i]->GetType() == "closebracket")
				ka = State::Q4;
			else if (vcr[i]->GetType() == "operand")
				ka = State::Q1;
			else if (vcr[i]->GetType() == "var")
				ka = State::V;
			else if (vcr[i]->GetType() == "sub")
				ka = State::U;
			else
				ka = State::Error;
			continue;

		case State::Q3:
			if (vcr[i]->GetType() == "openbracket")
				ka = State::Q2;
			else if (vcr[i]->GetType() == "operand")
				ka = State::Q1;
			else if (vcr[i]->GetType() == "var")
				ka = State::V;
			else
				ka = State::Error;
			continue;

		case State::Q4:
			if (vcr[i]->GetType() == "operation" || vcr[i]->GetType() == "sub")
				ka = State::Q3;
			else if (vcr[i]->GetType() == "closebracket")
				ka = State::Q4;
			else
				ka = State::Error;
			continue;

		case State::Eq:
			if (vcr[i]->GetType() == "operand")
				ka = State::Q1;
			else if (vcr[i]->GetType() == "openbracket")
				ka = State::Q2;
			else if (vcr[i]->GetType() == "var")
				ka = State::V;
			else if (vcr[i]->GetType() == "sub")
				ka = State::U;
			else
				ka = State::Error;
			continue;

		case State::U:
			if (vcr[i]->GetType() == "operand")
				ka = State::Q1;
			else if (vcr[i]->GetType() == "var")
				ka = State::V;
			else if (vcr[i]->GetType() == "openbracket")
				ka = State::Q2;
			else
				ka = State::Error;
			continue;

		case State::Error:
			break;

		default: ka = State::Error;
		}
	}

	int k = 0;

	for (int i = 0; i < vcr.size(); i++) {
		if (vcr[i]->GetType() == "openbracket")
			k++;
		if (vcr[i]->GetType() == "closebracket")
			k--;
		if (k < 0)
			ka = State::Error;
	}

	if ((ka == State::S0 || ka == State::Q1 || ka == State::Q4 || ka == State::V) && k == 0)
		return true;
	else
		return false;
}


static polynom Calculate(std::vector<term*> t) {
	MyStack<term*, std::vector> st;

	for (int i = 0; i < t.size(); i++) {

		if (t[i]->GetType() == "operand" || t[i]->GetType() == "var") {
			st.push(t[i]);
		}

		if (t[i]->GetType() == "operation" || t[i]->GetType() == "sub") {
			operation* op  =  dynamic_cast<operation*>(t[i]);
			var*       y   =  dynamic_cast<var*>(st.top());
			st.pop();
			var* x = dynamic_cast<var*>(st.top());
			st.pop();

			polynom nval = op->calc(x->getvalue(), y->getvalue());
			st.push(new var(nval));
		}
	}
	if (t.size() > 0) {
		var* res = dynamic_cast<var*>(st.top());
		return res->getvalue();
	}
}

static std::vector<term*> ToPostfix(std::vector<term*> vr) {

	MyStack<term*, std::vector> st;
	std::vector<term*> PstForm;

	if (vr.size() == 0)
		return PstForm;

	if (vr[0]->GetType() == "sub")
		PstForm.push_back(new var());
	
	if (vr.size() > 1 && vr[0]->GetType() == "var" && vr[1]->GetType() == "eq") {
		std::vector<term*> tmp(vr.size() - 2);

		for (int i = 2; i < vr.size(); i++) 
			tmp[i - 2] = vr[i];

		var* v = dynamic_cast<var*>(vr[0]);
		vars[v->GetName()] = Calculate(ToPostfix(tmp));
	}

	for (int i = 0; i < vr.size(); i++) {

		if (vr[i]->GetType() == "openbracket") {
			st.push(vr[i]);
		}

		if (i + 1 < vr.size() && vr[i]->GetType() == "openbracket" && vr[i + 1]->GetType() == "sub") {
			PstForm.push_back(new var());
		}

		if (vr[i]->GetType() == "closebracket") {
			while (st.top()->GetType() != "openbracket") {
				PstForm.push_back(st.top());
				st.pop();
			}
			st.pop();
		}

		if (vr[i]->GetType() == "operand") {
			PstForm.push_back(vr[i]);
		}

		if (vr[i]->GetType() == "var") {
			PstForm.push_back(vr[i]);
		}

		if ((vr[i]->GetType()    == "operation" || vr[i]->GetType()    == "sub") && !st.empty() && 
			(st.top()->GetType() == "operation" || st.top()->GetType() == "sub")) {

			operation* OpFromStack   =  dynamic_cast<operation*>(st.top());
			operation* OpFromVector  =  dynamic_cast<operation*>(vr[i]);

			while (!st.empty() && OpFromStack->priority() >= OpFromVector->priority()) {
				PstForm.push_back(st.top());
				st.pop();

				if (!st.empty() && (st.top()->GetType() == "operation" || 
					st.top()->GetType() == "sub"))
					OpFromStack = dynamic_cast<operation*>(st.top());
				else
					break;
			}

			st.push(OpFromVector);
			continue;
		}

		if (vr[i]->GetType() == "operation" || vr[i]->GetType() == "sub") {
			st.push(vr[i]);
		}
	}
	
	while (!st.empty()) {
		PstForm.push_back(st.top());
		st.pop();
	}
	
	return PstForm;
}

static polynom Translator(std::string str) {
	std::vector<term*> tmp = LexicalAnalyser(str);
	if (Parser(tmp) == false) {
		std::cout << "incorrect input" << std::endl;
	}

	if (tmp.size() > 0)
		return Calculate(ToPostfix(tmp));
}

static void GetResult(std::string str) {
	std::vector<term*> tmp = LexicalAnalyser(str);
	if (Parser(tmp) == false) {
		std::cout << "incorrect input" << std::endl;
		return;
	}

	if (tmp.size() > 1 && tmp[1]->GetType() == "eq")
		Calculate(ToPostfix(tmp));

	else if (tmp.size() > 0)
		Calculate(ToPostfix(tmp)).print();
}
