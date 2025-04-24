#include <cmath>
#include <iostream>
#include <exception>
#include "Monom.h"

monom::monom() {
	coef = 0.0;
	exp = 0;
}

monom::monom(double c, int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 || x > 9 || y > 9 || z > 9)
		throw std::runtime_error("incorrect degree input");
	coef = c;
	exp = x * 100 + y * 10 + z;
}

monom::monom(double c, int p) {
	coef = c;
	exp = p;
}

double monom::GetCoefficient() {
	return coef;
}

int monom::GetDegree() {
	return exp;
}

int monom::GetDegreeX() {
	return exp / 100;
}
int monom::GetDegreeY() {
	return (exp / 10) % 10;
}
int monom::GetDegreeZ() {
	return exp % 10;
}

monom monom::operator+(const monom& m) {
	if (m.exp != exp) throw std::runtime_error("Degree are different");
	return monom(m.coef + coef, exp);
}

monom monom::operator-(const monom& m) {
	if (m.exp != exp) throw std::runtime_error("Degree are different");
	return monom(coef - m.coef, exp);
}

monom monom::operator*(monom& m) {
	if (GetDegreeX() + m.GetDegreeX() > 9 ||
		GetDegreeY() + m.GetDegreeY() > 9 ||
		GetDegreeZ() + m.GetDegreeZ() > 9)
		throw "";

	return monom(coef * m.coef, GetDegreeX() + m.GetDegreeX(),
		GetDegreeY() + m.GetDegreeY(), GetDegreeZ() + m.GetDegreeZ());
}

monom monom::operator/(monom& m) {
	if (GetDegreeX() - m.GetDegreeX() < 0 ||
		GetDegreeY() - m.GetDegreeY() < 0 ||
		GetDegreeZ() - m.GetDegreeZ() < 0 ||
		abs(m.coef) < 0.0000001)
		throw "";

	return monom(coef / m.coef, GetDegreeX() - m.GetDegreeX(),
		GetDegreeY() - m.GetDegreeY(), GetDegreeZ() - m.GetDegreeZ());
}

monom monom::operator*(double c) {
	return monom(c * coef, exp);
}

monom monom::operator/(double c) {
	if (abs(c) < 0.000000001) throw std::runtime_error("divide by zero");
	return monom(coef / c, exp);
}

monom& monom::operator+=(const monom& m) {
	if (exp != m.exp) throw std::runtime_error("Degree are different");
	coef += m.coef;
	return *this;
}

monom& monom::operator-=(const monom& m) {
	if (exp != m.exp) throw std::runtime_error("Degree are different");
	coef -= m.coef;
	return *this;
}

monom& monom::operator*=(monom& m) {
	if (GetDegreeX() + m.GetDegreeX() > 9 ||
		GetDegreeY() + m.GetDegreeY() > 9 ||
		GetDegreeZ() + m.GetDegreeZ() > 9)
		throw std::runtime_error("incorrect degree as a result");
	coef *= m.coef;

	exp = (GetDegreeX() + m.GetDegreeX()) * 100 +
		(GetDegreeY() + m.GetDegreeY()) * 10 +
		GetDegreeZ() + m.GetDegreeZ();
	return *this;
}

monom& monom::operator/=(monom& m) {
	if (GetDegreeX() - m.GetDegreeX() < 0 ||
		GetDegreeY() - m.GetDegreeY() < 0 ||
		GetDegreeZ() - m.GetDegreeZ() < 0 ||
		abs(m.coef) < 0.000000001)
		throw std::runtime_error("incorrect degree as a result");

	coef /= m.coef;
	exp = (GetDegreeX() - m.GetDegreeX()) * 100 +
		(GetDegreeY() - m.GetDegreeY()) * 10 +
		GetDegreeZ() - m.GetDegreeZ();
	return *this;
}

monom& monom::operator*=(double c) {
	coef *= c;
	return *this;
}

monom& monom::operator/=(double c) {
	if (abs(c) < 0.00000001) throw std::runtime_error("division by zero");
	coef /= c;
	return *this;
}

bool monom::operator==(const monom& m) {
	if (coef == m.coef && exp == m.exp)
		return true;
	return false;
}

bool monom::operator!=(const monom& m) {
	return !(*this == m);
}

bool monom::operator<(monom& m) {
	if (GetDegreeX() == m.GetDegreeX()) {
		if (GetDegreeY() == m.GetDegreeY()) {
			if (GetDegreeZ() == m.GetDegreeZ()) {
				if (GetCoefficient() < m.GetCoefficient())
					return true;
				return false;
			}
			else if (GetDegreeZ() < m.GetDegreeZ())
				return true;
			return false;
		}
		else if (GetDegreeY() < m.GetDegreeY())
			return true;
		return false;
	}
	else if (GetDegreeX() < m.GetDegreeX())
		return true;
	return false;
}

bool monom::operator>(monom& m) {
	return m < *this;
}