#pragma once

class monom {
	double coef;
	int exp;
public:
	monom();
	monom(double c, int x, int y, int z);
	monom(double c, int p);

	double GetCoefficient();
	int GetDegree();
	int GetDegreeX();
	int GetDegreeY();
	int GetDegreeZ();

	monom operator+(const monom& m);
	monom operator-(const monom& m);
	monom operator*(monom& m);
	monom operator/(monom& m);

	monom& operator+=(const monom& m);
	monom& operator-=(const monom& m);
	monom& operator*=(monom& m);
	monom& operator/=(monom& m);

	monom operator*(double c);
	monom operator/(double c);
	monom& operator*=(double c);
	monom& operator/=(double c);

	bool operator<(monom& m);
	bool operator>(monom& m);
	bool operator==(const monom& m);
	bool operator!=(const monom& m);
};