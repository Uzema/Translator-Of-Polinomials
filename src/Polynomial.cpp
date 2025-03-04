#include<vector>
#include<iostream>
#include"polynomial.h"

polynom::polynom() {
	List<monom> l;
}

polynom::polynom(monom& m) {
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
			res.l.insert(*j, k.get_node());
			k++;
			j++;
		}
		if (*i < *j) {
			res.l.insert(*i, k.get_node());
			k++;
		}
	}

	while (j != this->l.end()) {
		res.l.insert(*j, k.get_node());
		j++;
		k++;
	}

	return res;
}

polynom& polynom::operator+=(polynom& p) {
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
			res.l.insert(*j, k.get_node());
			k++;
			j++;
		}
		if (*i < *j) {
			res.l.insert(*i * (-1), k.get_node());
			k++;
		}
	}

	while (j != this->l.end()) {
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
	if (abs(c) < 0.0000000001) throw "division by zero";
	polynom res = *this;
	for (List<monom>::iterator i = res.l.begin(); i != res.l.end(); i++)
		*i /= c;
	return res;
}

polynom& polynom::operator/=(double c) {
	if (abs(c) < 0.0000000001) throw "division by zero";
	for (List<monom>::iterator i = this->l.begin(); i != this->l.end(); i++)
		*i /= c;
	return *this;
}