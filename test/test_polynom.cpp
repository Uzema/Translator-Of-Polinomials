#include <gtest.h>
#include "Polynomial.h"

TEST(Polynomial, CreatePolynom) {
	ASSERT_NO_THROW(polynom p);
}

TEST(Polynomial, Polynom) {
	polynom p(monom(1, 100));
	polynom p1(monom(1, 10));
	p = p1 + p;
	EXPECT_EQ(1, p[0].GetCoefficient());
	EXPECT_EQ(10, p[0].GetDegree());
	EXPECT_EQ(1, p[1].GetCoefficient());
	EXPECT_EQ(100, p[1].GetDegree());
}

TEST(Polynomial, CreatePolynomWithPolynom) {
	polynom p(monom(1.1, 147));
	EXPECT_EQ(1.1, p[0].GetCoefficient());
	EXPECT_EQ(147, p[0].GetDegree());
}

TEST(Polynomial, CorrectInsertMonom) {
	polynom p;
	p.insert(1.4, 123);
	EXPECT_EQ(1.4, p[0].GetCoefficient());
	EXPECT_EQ(123, p[0].GetDegree());
}

TEST(Polynomial, CorrectInsertDifferentMonoms) {
	polynom p;
	p.insert(1.4, 333);
	p.insert(1.4, 111);
	p.insert(1.4, 222);

	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(222, p[1].GetDegree());
	EXPECT_EQ(333, p[2].GetDegree());
}

TEST(Polynomial, CorrectInsertMonomsWithSimilarDegree) {
	polynom p;
	p.insert(1, 111);
	p.insert(1, 111);
	p.insert(1, 111);

	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(3, p[0].GetCoefficient());
}

TEST(Polynomial, CorrectAddPolynomsWithDifferentDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.4, 333);
	p1.insert(1.4, 111);

	p2.insert(1.4, 332);
	p2.insert(1.4, 112);

	polynom p = p1 + p2;

	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(112, p[1].GetDegree());
	EXPECT_EQ(332, p[2].GetDegree());
	EXPECT_EQ(333, p[3].GetDegree());
}

TEST(Polynomial, CorrectAddEmptyPolynom) {
	polynom p1;
	polynom p2;
	p2.insert(1.4, 332);
	p2.insert(1.4, 112);

	polynom p = p1 + p2;

	EXPECT_EQ(332, p[1].GetDegree());
	EXPECT_EQ(112, p[0].GetDegree());
}

TEST(Polynomial, CorrectAddPolynomsWithSimilarDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.4, 222);
	p1.insert(2.4, 111);

	p2.insert(2.4, 111);
	p2.insert(1.4, 222);

	polynom p = p1 + p2;

	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(222, p[1].GetDegree());
	EXPECT_EQ(4.8, p[0].GetCoefficient());
	EXPECT_EQ(2.8, p[1].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentAddPolynomsWithDifferentDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.4, 333);
	p1.insert(1.4, 111);

	p2.insert(1.4, 332);
	p2.insert(1.4, 112);

	p1 += p2;

	EXPECT_EQ(111, p1[0].GetDegree());
	EXPECT_EQ(112, p1[1].GetDegree());
	EXPECT_EQ(332, p1[2].GetDegree());
	EXPECT_EQ(333, p1[3].GetDegree());
}

TEST(Polynomial, CorrectAssigmentAddPolynomsWithSimilarDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.4, 222);
	p1.insert(2.4, 111);

	p2.insert(2.4, 111);
	p2.insert(1.4, 222);

	p1 += p2;

	EXPECT_EQ(111, p1[0].GetDegree());
	EXPECT_EQ(222, p1[1].GetDegree());
	EXPECT_EQ(4.8, p1[0].GetCoefficient());
	EXPECT_EQ(2.8, p1[1].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentAddEmptyPolynom) {
	polynom p1;
	polynom p2;
	p2.insert(1.4, 332);
	p2.insert(1.4, 112);

	p1 += p2;

	EXPECT_EQ(332, p1[1].GetDegree());
	EXPECT_EQ(112, p1[0].GetDegree());
}

TEST(Polynomial, CorrectSubPolynomsWithDifferentDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.4, 333);
	p1.insert(1.4, 111);

	p2.insert(1.4, 332);
	p2.insert(1.4, 112);

	polynom p = p1 - p2;

	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(112, p[1].GetDegree());
	EXPECT_EQ(332, p[2].GetDegree());
	EXPECT_EQ(333, p[3].GetDegree());
	EXPECT_EQ(1.4, p[0].GetCoefficient());
	EXPECT_EQ(-1.4, p[1].GetCoefficient());
	EXPECT_EQ(-1.4, p[2].GetCoefficient());
	EXPECT_EQ(1.4, p[3].GetCoefficient());
}

TEST(Polynomial, CorrectSubEmptyPolynom) {
	polynom p1;
	polynom p2;
	p2.insert(1.4, 332);
	p2.insert(1.5, 112);

	polynom p = p1 - p2;

	EXPECT_EQ(-1.5, p[0].GetCoefficient());
	EXPECT_EQ(-1.4, p[1].GetCoefficient());
}

TEST(Polynomial, CorrectSubPolynomsWithSimilarDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.4, 222);
	p1.insert(2, 111);

	p2.insert(3, 111);
	p2.insert(1.4, 222);

	polynom p = p1 - p2;

	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(222, p[1].GetDegree());
	EXPECT_EQ(-1, p[0].GetCoefficient());
	EXPECT_EQ(0, p[1].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentSubPolynomsWithDifferentDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.5, 333);
	p1.insert(1.4, 111);

	p2.insert(1.5, 332);
	p2.insert(1.4, 112);

	p1 -= p2;

	EXPECT_EQ(111, p1[0].GetDegree());
	EXPECT_EQ(112, p1[1].GetDegree());
	EXPECT_EQ(332, p1[2].GetDegree());
	EXPECT_EQ(333, p1[3].GetDegree());
	EXPECT_EQ(1.4, p1[0].GetCoefficient());
	EXPECT_EQ(-1.4, p1[1].GetCoefficient());
	EXPECT_EQ(-1.5, p1[2].GetCoefficient());
	EXPECT_EQ(1.5, p1[3].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentSubPolynomsWithSimilarDegree) {
	polynom p1;
	polynom p2;
	p1.insert(1.5, 222);
	p1.insert(2.5, 111);

	p2.insert(1.5, 111);
	p2.insert(0.5, 222);

	p1 -= p2;

	EXPECT_EQ(111, p1[0].GetDegree());
	EXPECT_EQ(222, p1[1].GetDegree());
	EXPECT_EQ(1, p1[0].GetCoefficient());
	EXPECT_EQ(1, p1[1].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentSubEmptyPolynom) {
	polynom p1;
	polynom p2;
	p2.insert(1.4, 332);
	p2.insert(1.5, 112);

	p1 -= p2;

	EXPECT_EQ(-1.5, p1[0].GetCoefficient());
	EXPECT_EQ(-1.4, p1[1].GetCoefficient());
}

TEST(Polynomial, CorrectMultiplicatePolynomAndNumber) {
	polynom p1;
	p1.insert(1.5, 332);
	p1.insert(-1.4, 112);
	polynom p = p1 * 2;

	EXPECT_EQ(3, p[1].GetCoefficient());
	EXPECT_EQ(-2.8, p[0].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentMultiplicatePolynomAndNumber) {
	polynom p;
	p.insert(1.5, 332);
	p.insert(-1.4, 112);
	p *= 2;

	EXPECT_EQ(3, p[1].GetCoefficient());
	EXPECT_EQ(-2.8, p[0].GetCoefficient());
}

TEST(Polynomial, CorrectDivisionPolynomAndNumber) {
	polynom p1;
	p1.insert(1.6, 332);
	p1.insert(-1.4, 112);
	polynom p = p1 / 2;

	EXPECT_EQ(0.8, p[1].GetCoefficient());
	EXPECT_EQ(-0.7, p[0].GetCoefficient());
}

TEST(Polynomial, CorrectAssigmentDivisionPolynomAndNumber) {
	polynom p;
	p.insert(1.6, 332);
	p.insert(-1.4, 112);
	p /= 2;

	EXPECT_EQ(0.8, p[1].GetCoefficient());
	EXPECT_EQ(-0.7, p[0].GetCoefficient());
}

TEST(Polynomial, CorrectMultiplicatePolynoms) {
	polynom p1;
	polynom p2;
	p1.insert(1, 332);
	p1.insert(-1, 112);
	p2.insert(-2, 111);
	p2.insert(5, 212);
	polynom p = p1 * p2;

	EXPECT_EQ(2, p[0].GetCoefficient());
	EXPECT_EQ(-5, p[1].GetCoefficient());
	EXPECT_EQ(-2, p[2].GetCoefficient());
	EXPECT_EQ(5, p[3].GetCoefficient());
	EXPECT_EQ(223, p[0].GetDegree());
	EXPECT_EQ(324, p[1].GetDegree());
	EXPECT_EQ(443, p[2].GetDegree());
	EXPECT_EQ(544, p[3].GetDegree());
}

TEST(Polynomial, CorrectMultiplicateAndCombiningLikeTerms) {
	polynom p1;
	polynom p2;
	p1.insert(1, 111);
	p1.insert(1, 222);
	p2.insert(1, 0);
	p2.insert(1, 111);
	polynom p = p1 * p2;

	EXPECT_EQ(1, p[0].GetCoefficient());
	EXPECT_EQ(2, p[1].GetCoefficient());
	EXPECT_EQ(1, p[2].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(222, p[1].GetDegree());
	EXPECT_EQ(333, p[2].GetDegree());
}

TEST(Polynomial, CorrectMultiplicatePolynomWithEmptyPolynom) {
	polynom p1;
	polynom p2;
	p1.insert(1, 332);
	p1.insert(-1, 112);
	polynom p = p1 * p2;

	EXPECT_EQ(0, p[0].GetCoefficient());
}

TEST(Polynomial, ThrowWhenDegreeResultsGreate9) {
	polynom p1;
	polynom p2;
	p1.insert(1, 999);
	p2.insert(-1, 10);

	ASSERT_ANY_THROW(p1 * p2);
}

TEST(Polynomial, CorrectDivisionPolynom) {
	polynom p;
	monom m(2, 212);
	p.insert(10, 332);
	p.insert(-6, 312);
	p = p / m;

	EXPECT_EQ(-3, p[0].GetCoefficient());
	EXPECT_EQ(5, p[1].GetCoefficient());
	EXPECT_EQ(100, p[0].GetDegree());
	EXPECT_EQ(120, p[1].GetDegree());
}

TEST(Polynomial, ThrowWhenDivisionPolynomWithEmptyMonom) {
	polynom p;
	monom m;
	p.insert(1, 332);
	p.insert(-1, 112);

	ASSERT_ANY_THROW(p / m);
}

TEST(Polynomial, ThrowWhenDegreeResultsLessZero) {
	polynom p;
	monom m(-1, 211);
	p.insert(1, 111);

	ASSERT_ANY_THROW(p / m);
}
TEST(Polynomial, CorrectAssigmentDivisionPolynom) {
	polynom p;
	monom m(2, 212);
	p.insert(10, 332);
	p.insert(-6, 312);
	p /= m;

	EXPECT_EQ(-3, p[0].GetCoefficient());
	EXPECT_EQ(5, p[1].GetCoefficient());
	EXPECT_EQ(100, p[0].GetDegree());
	EXPECT_EQ(120, p[1].GetDegree());
}

TEST(Polynomial, ThrowWhenAssigmentDivisionPolynomWithEmptyMonom) {
	polynom p;
	monom m;
	p.insert(1, 332);
	p.insert(-1, 112);

	ASSERT_ANY_THROW(p /= m);
}

TEST(Polynomial, ThrowWhenDegreeResultsAssigmentDivisionLessZero) {
	polynom p;
	monom m(-1, 211);
	p.insert(1, 111);

	ASSERT_ANY_THROW(p /= m);
}

TEST(Polynomial, CorrectAssigmentMultiplicatePolynoms) {
	polynom p1;
	polynom p2;
	p1.insert(1, 332);
	p1.insert(-1, 112);
	p2.insert(-2, 111);
	p2.insert(5, 212);
	p1 *= p2;

	EXPECT_EQ(2, p1[0].GetCoefficient());
	EXPECT_EQ(-5, p1[1].GetCoefficient());
	EXPECT_EQ(-2, p1[2].GetCoefficient());
	EXPECT_EQ(5, p1[3].GetCoefficient());
	EXPECT_EQ(223, p1[0].GetDegree());
	EXPECT_EQ(324, p1[1].GetDegree());
	EXPECT_EQ(443, p1[2].GetDegree());
	EXPECT_EQ(544, p1[3].GetDegree());
}

TEST(Polynomial, CorrectAssigmentMultiplicateAndCombiningLikeTerms) {
	polynom p1;
	polynom p2;
	p1.insert(1, 111);
	p1.insert(1, 222);
	p2.insert(1, 0);
	p2.insert(1, 111);
	p1 *= p2;

	EXPECT_EQ(1, p1[0].GetCoefficient());
	EXPECT_EQ(2, p1[1].GetCoefficient());
	EXPECT_EQ(1, p1[2].GetCoefficient());
	EXPECT_EQ(111, p1[0].GetDegree());
	EXPECT_EQ(222, p1[1].GetDegree());
	EXPECT_EQ(333, p1[2].GetDegree());
}

TEST(Polynomial, CorrectAssigmentMultiplicatePolynomWithEmptyPolynom) {
	polynom p1;
	polynom p2;
	p1.insert(1, 332);
	p1.insert(-1, 112);
	p1 *= p2;

	EXPECT_EQ(0, p1[0].GetCoefficient());
}


TEST(Parser, InputNumber) {
	polynom p;
	p.parser("7");
	EXPECT_EQ(7, p[0].GetCoefficient());
	EXPECT_EQ(0, p[0].GetDegree());
}

TEST(Parser, InputDoubleNumber) {
	polynom p;
	p.parser("7.1");
	EXPECT_EQ(7.1, p[0].GetCoefficient());
	EXPECT_EQ(0, p[0].GetDegree());
}

TEST(Parser, InputNegstiveNumber) {
	polynom p;
	p.parser("-7");
	EXPECT_EQ(-7, p[0].GetCoefficient());
	EXPECT_EQ(0, p[0].GetDegree());
}

TEST(Parser, CalculateNumbers) {
	polynom p;
	p.parser("- 2 + 15.5 - 10.5");
	EXPECT_EQ(3, p[0].GetCoefficient());
	EXPECT_EQ(0, p[0].GetDegree());
}

TEST(Parser, InputOnlyX) {
	polynom p;
	p.parser("x");
	EXPECT_EQ(1, p[0].GetCoefficient());
	EXPECT_EQ(100, p[0].GetDegree());
}

TEST(Parser, InputOnlyNegativeX) {
	polynom p;
	p.parser("-x");
	EXPECT_EQ(-1, p[0].GetCoefficient());
	EXPECT_EQ(100, p[0].GetDegree());
}

TEST(Parser, InputMonomWithoutCoefficient) {
	polynom p;
	p.parser("xyz");
	EXPECT_EQ(1, p[0].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
}

TEST(Parser, InputMonomWithNegativeCoefficient) {
	polynom p;
	p.parser("-4xyz");
	EXPECT_EQ(-4, p[0].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
}

TEST(Parser, InputMonomWithMultiplicationSign) {
	polynom p;
	p.parser("-4*x*y*z");
	EXPECT_EQ(-4, p[0].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
}

TEST(Parser, InputMonomWithDegree) {
	polynom p;
	p.parser("-4*x4y2z1");
	EXPECT_EQ(-4, p[0].GetCoefficient());
	EXPECT_EQ(421, p[0].GetDegree());
}

TEST(Parser, InputMonomWithDegreeSign) {
	polynom p;
	p.parser("-4*x^4y^2z^1");
	EXPECT_EQ(-4, p[0].GetCoefficient());
	EXPECT_EQ(421, p[0].GetDegree());
}

TEST(Parser, InputMonomWithDegreeAndMultiplicationSign) {
	polynom p;
	p.parser("-4*x^4*y^2*z^1");
	EXPECT_EQ(-4, p[0].GetCoefficient());
	EXPECT_EQ(421, p[0].GetDegree());
}

TEST(Parser, InputPolynom) {
	polynom p;
	p.parser("x^4*y^2*z^1 + 2xyz");
	EXPECT_EQ(2, p[0].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(1, p[1].GetCoefficient());
	EXPECT_EQ(421, p[1].GetDegree());
}

TEST(Parser, InputPolynomWithNegativeMonom) {
	polynom p;
	p.parser("x^4*y^2*z^1 - 2xyz");
	EXPECT_EQ(-2, p[0].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
	EXPECT_EQ(1, p[1].GetCoefficient());
	EXPECT_EQ(421, p[1].GetDegree());
}

TEST(Parser, InputPolynomWithCombiningLikeTerms) {
	polynom p;
	p.parser("- 2xyz + xyz");
	EXPECT_EQ(-1, p[0].GetCoefficient());
	EXPECT_EQ(111, p[0].GetDegree());
}
