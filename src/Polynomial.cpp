#include <vector>
#include <iostream>
#include "Polynomial.h"

polynom::polynom() {
	List<monom> l;
}

polynom::polynom(monom m) {
	polynom p;
	p.l.insert(m, l.get_head());
}

monom polynom::operator[](int index) {
	return this->l[index];
}

void polynom::print() {
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++) {
		if (abs(i->GetCoefficient()) < 0.0000000001)
			continue;

		if (i->GetCoefficient() > 0 && i != this->l.begin())
			std::cout << '+';
		if (abs(i->GetCoefficient() + 1) < 0.0000000001)
			std::cout << '-';

		if (abs(i->GetCoefficient() - 1) > 0.0000000001 &&
			abs(i->GetCoefficient() + 1) > 0.0000000001)
			std::cout << i->GetCoefficient();

		if (i->GetDegreeX() == 1)
			std::cout << 'x';
		else if (i->GetDegreeX() > 1)
			std::cout << 'x' << i->GetDegreeX();

		if (i->GetDegreeY() == 1)
			std::cout << 'y';
		else if (i->GetDegreeY() > 1)
			std::cout << 'y' << i->GetDegreeY();

		if (i->GetDegreeZ() == 1)
			std::cout << 'z';
		else if (i->GetDegreeZ() > 1)
			std::cout << 'z' << i->GetDegreeZ();
	}
	std::cout << std::endl;
}

void polynom::insert(double c, int exp) {
	monom m(c, exp);
	List<monom>::iterator ne = this->l.begin();
	List<monom>::iterator pr = this->l.end();

	while (ne != this->l.end()) {
		if (ne->GetDegree() == m.GetDegree()) {
			*ne += m;
			return;
		}
		if (*ne > m) {
			this->l.insert(m, pr.get_node());
			return;
		}
		ne++;
		pr++;
	}
	this->l.insert(m, pr.get_node());
}

polynom polynom::operator+(polynom& p) {
	polynom res;
	List<monom>::iterator j = this->l.begin();
	List<monom>::iterator k = res.l.begin();

	for (List<monom>::iterator i = p.l.begin(); i != p.l.end(); i++) {
		if (j == this->l.end()) {
			res.l.insert(*i, k.get_node());
			k++;
			continue;
		}
		if (i->GetDegree() == j->GetDegree()) {
			res.l.insert(monom(i->GetCoefficient() + j->GetCoefficient(),
				i->GetDegree()), k.get_node());
			j++;
			k++;
			continue;
		}
		while (*j < *i) {
			if (j->GetCoefficient() == 0 && j->GetDegree() == 0)
				break;
			res.l.insert(*j, k.get_node());
			k++;
			j++;
		}
		//if (j != this->l.end() && *i < *j) {
			res.l.insert(*i, k.get_node());
			k++;
		//}
	}

	while (j != this->l.end()) {
		if (j->GetCoefficient() == 0 && j->GetDegree() == 0)
			break;
		res.l.insert(*j, k.get_node());
		j++;
		k++;
	}

	return res;
}

polynom& polynom::operator+=(polynom p) {
	List<monom>::iterator j = p.l.begin();
	List<monom>::iterator i = this->l.begin();
	List<monom>::iterator pr = this->l.end();

	for (i; i != this->l.end(); i++, pr++) {
		if (i->GetDegree() == j->GetDegree()) {
			*i += *j;
			j++;
		}
		while (*j < *i && j != p.l.end()) {
			this->l.insert(*j, pr.get_node());
			j++;
			pr++;
		}
	}

	while (j != p.l.end()) {
		this->l.insert(*j, pr.get_node());
		j++;
		pr++;
	}

	return *this;
}

polynom polynom::operator-(polynom& p) {
	polynom res;
	List<monom>::iterator j = this->l.begin();
	List<monom>::iterator k = res.l.begin();

	for (List<monom>::iterator i = p.l.begin(); i != p.l.end(); i++) {
		if (j == this->l.end()) {
			res.l.insert(*i * (-1), k.get_node());
			k++;
			continue;
		}
		if (i->GetDegree() == j->GetDegree()) {
			res.l.insert(monom(j->GetCoefficient() - i->GetCoefficient(),
				j->GetDegree()), k.get_node());
			j++;
			k++;
			continue;
		}
		while (*j < *i) {
			if (j->GetCoefficient() == 0 && j->GetDegree() == 0)
				break;
			res.l.insert(*j, k.get_node());
			k++;
			j++;
		}
		//if (*i < *j) {
			res.l.insert(*i * (-1), k.get_node());
			k++;
		//}
	}

	while (j != this->l.end()) {
		if (j->GetCoefficient() == 0 && j->GetDegree() == 0)
			break;
		res.l.insert(*j, k.get_node());
		j++;
		k++;
	}

	return res;
}

polynom& polynom::operator-=(polynom& p) {
	List<monom>::iterator j = p.l.begin();
	List<monom>::iterator i = this->l.begin();
	List<monom>::iterator pr = this->l.end();

	for (i; i != this->l.end(); i++, pr++) {
		if (i->GetDegree() == j->GetDegree()) {
			*i -= *j;
			j++;
		}
		while (*j < *i && j != p.l.end()) {
			this->l.insert(*j * (-1), pr.get_node());
			j++;
			pr++;
		}
	}

	while (j != p.l.end()) {
		this->l.insert(*j * (-1), pr.get_node());
		j++;
		pr++;
	}

	return *this;
}

polynom polynom::operator*(polynom& p) {
	polynom res;
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++) {
		polynom tmp;
		List<monom>::iterator k = tmp.l.begin();
		for (List<monom>::iterator j = p.l.begin(); j != p.l.end(); j++, k++)
			tmp.l.insert(*i * *j, k.get_node());
		res += tmp;
	}
	return res;
}

polynom polynom::operator/(monom& m) {
	polynom res;
	List<monom>::iterator k = res.l.begin();
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++, k++)
		res.l.insert(*i / m, k.get_node());
	return res;
}

polynom& polynom::operator*=(polynom& p) {
	*this = *this * p;
	return *this;
}

polynom& polynom::operator/=(monom& m) {
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++)
		*i /= m;
	return *this;
}

polynom polynom::operator*(double c) {
	polynom res = *this;
	for (List<monom>::iterator i = res.l.begin(); i != res.l.end(); i++)
		*i *= c;
	return res;
}

polynom& polynom::operator*=(double c) {
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++)
		*i *= c;
	return *this;
}

polynom polynom::operator/(double c) {
	if (abs(c) < 0.0000000001) throw std::runtime_error("division by zero");
	polynom res = *this;
	for (List<monom>::iterator i = res.l.begin(); i != res.l.end(); i++)
		*i /= c;
	return res;
}

polynom& polynom::operator/=(double c) {
	if (abs(c) < 0.0000000001) throw std::runtime_error("division by zero");
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++)
		*i /= c;
	return *this;
}

polynom& polynom::parser(std::string s) {
	if (s.empty())
		return *this;
	std::vector<std::string> v;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') continue;

		if (s[i] == '+' || s[i] == '*' || s[i] == '-' || s[i] == '^' ||
			s[i] == 'x' || s[i] == 'y' || s[i] == 'z')
			v.push_back(std::string(1, s[i]));

		else if (s[i] >= 48 && s[i] <= 57) {
			int k = 1;
			std::string num;

			while (s[i] >= 48 && s[i] <= 57 || s[i] == ',' || s[i] == '.') {
				num += s[i];
				if (s[i] == ',' || s[i] == '.')
					k--;
				if (k < 0) throw std::runtime_error("Incorrect input");
				i++;
			}
			if (!num.empty()) {
				v.push_back(num);
				i--;
			}
		}
		else throw std::runtime_error("Incorrect input");
	}

	enum class state { S, Op, Num, Var, Exp, Mul, Error };
	state ka = state::S;
	for (int i = 0; i < v.size(); i++) {
		switch (ka) {

		case state::S:
			if (v[i] == "+" || v[i] == "-")
				ka = state::Op;
			else if (v[i] == "x" || v[i] == "y" || v[i] == "z")
				ka = state::Var;
			else if (v[i][0] >= 48 && v[i][0] <= 57)
				ka = state::Num;
			else ka = state::Error;
			continue;

		case state::Op:
			if (v[i] == "x" || v[i] == "y" || v[i] == "z")
				ka = state::Var;
			else if (v[i][0] >= 48 && v[i][0] <= 57)
				ka = state::Num;
			else ka = state::Error;
			continue;

		case state::Num:
			if (v[i] == "+" || v[i] == "-")
				ka = state::Op;
			else if (v[i] == "x" || v[i] == "y" || v[i] == "z")
				ka = state::Var;
			else if (v[i] == "*")
				ka = state::Mul;
			else ka = state::Error;
			continue;

		case state::Mul:
			if (v[i] == "x" || v[i] == "y" || v[i] == "z")
				ka = state::Var;
			else ka = state::Error;
			continue;

		case state::Exp:
			if (v[i][0] >= 48 && v[i][0] <= 57)
				ka = state::Num;
			else ka = state::Error;
			continue;

		case state::Var:
			if (v[i] == "+" || v[i] == "-")
				ka = state::Op;
			else if (v[i] == "x" || v[i] == "y" || v[i] == "z")
				ka = state::Var;
			else if (v[i][0] >= 48 && v[i][0] <= 57)
				ka = state::Num;
			else if (v[i] == "*")
				ka = state::Mul;
			else if (v[i] == "^")
				ka = state::Exp;
			else ka = state::Error;
			continue;

		default: ka = state::Error;
		}
	}

	if (ka != state::Num && ka != state::Var)
		throw std::runtime_error("Incorrect input");

	bool t = 1;
	for (int i = 0; i < v.size(); i++) {
		double c = 1;
		int xd = 0, yd = 0, zd = 0;
		char p = ' ';

		if (v[i] == "-") {
			t = 0;
			i++;
		}
		if (v[i] == "+") {
			t = 1;
			i++;
		}

		while (i < v.size() && v[i] != "+" && v[i] != "-") {
			if (v[i] == "x") {
				p = 'x';
				xd = 1;
			}
			else if (v[i] == "y") {
				p = 'y';
				yd = 1;
			}
			else if (v[i] == "z") {
				p = 'z';
				zd = 1;
			}
			else if (v[i][0] >= 48 && v[i][0] <= 57) {
				if (p == ' ') c = stod(v[i]);
				if (p == 'x') xd = stoi(v[i]);
				if (p == 'y') yd = stod(v[i]);
				if (p == 'z') zd = stoi(v[i]);
			}
			i++;
		}
		i--;
		if (!t) c *= -1;
		*this += polynom(monom(c, xd * 100 + yd * 10 + zd));
	}
	return *this;
}