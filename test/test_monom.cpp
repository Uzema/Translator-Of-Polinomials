#pragma once
#include <gtest.h>
#include "monom.h"

TEST(Monom, CreateMonom) {
	ASSERT_NO_THROW(monom a);
}

TEST(Monom, CreateMonomWithCoefficientAndDegree) {
	monom a(1.1, 1, 1, 1);
	EXPECT_EQ(1.1, a.GetCoefficient());
	EXPECT_EQ(111, a.GetDegree());
}

TEST(Monom, CorrectReturnDegreeXYZ) {
	monom a(1, 7, 4, 2);
	EXPECT_EQ(7, a.GetDegreeX());
	EXPECT_EQ(4, a.GetDegreeY());
	EXPECT_EQ(2, a.GetDegreeZ());
}

TEST(Monom, CorrectAddMonoms) {
	monom a(11, 7, 4, 2);
	monom b(21, 7, 4, 2);
	monom c = a + b;
	EXPECT_EQ(32, c.GetCoefficient());
	EXPECT_EQ(742, c.GetDegree());
}

TEST(Monom, ThrowWhenAddWithDifferentDegree) {
	monom a(11, 7, 5, 2);
	monom b(21, 7, 4, 2);
	ASSERT_ANY_THROW(a + b);
}

TEST(Monom, CorrectSubMonoms) {
	monom a(11, 7, 4, 2);
	monom b(21, 7, 4, 2);
	monom c = a - b;
	EXPECT_EQ(-10, c.GetCoefficient());
	EXPECT_EQ(742, c.GetDegree());
}

TEST(Monom, ThrowWhenSubWithDifferentDegree) {
	monom a(11, 7, 5, 2);
	monom b(21, 7, 4, 2);
	ASSERT_ANY_THROW(a - b);
}

TEST(Monom, CorrectMultiplicateMonoms) {
	monom a(11, 7, 4, 2);
	monom b(21, 2, 0, 2);
	monom c = a * b;
	EXPECT_EQ(231, c.GetCoefficient());
	EXPECT_EQ(944, c.GetDegree());
}

TEST(Monom, CorrectDivisionMonoms) {
	monom a(20, 7, 4, 2);
	monom b(10, 2, 0, 2);
	monom c = a / b;
	EXPECT_EQ(2, c.GetCoefficient());
	EXPECT_EQ(540, c.GetDegree());
}

TEST(Monom, ThrowWhenMultiplicateDegreeResultsGreat9) {
	monom a(11, 7, 5, 2);
	monom b(21, 7, 4, 2);
	ASSERT_ANY_THROW(a * b);
}

TEST(Monom, ThrowWhenDivisionByZeroMonom) {
	monom a(11, 7, 5, 2);
	monom b(0, 0);
	ASSERT_ANY_THROW(a / b);
}

TEST(Monom, CorrectMultiplicateMonomAndNumber) {
	monom a(11, 7, 4, 2);
	double b = -2;
	monom c = a * b;
	EXPECT_EQ(-22, c.GetCoefficient());
	EXPECT_EQ(742, c.GetDegree());
}

TEST(Monom, CorrectDivisionMonomAndNumber) {
	monom a(10, 7, 4, 2);
	double b = -2;
	monom c = a / b;
	EXPECT_EQ(-5, c.GetCoefficient());
	EXPECT_EQ(742, c.GetDegree());
}

TEST(Monom, ThrowWhenDivisionByZero) {
	monom a(11, 7, 5, 2);
	ASSERT_ANY_THROW(a / 0);
}

TEST(Monom, ThrowWhenDivisionDegreeResultsLessZero) {
	monom a(11, 7, 5, 2);
	monom b(21, 4, 2, 5);
	ASSERT_ANY_THROW(a / b);
}

TEST(Monom, CorrectAssigmentAddMonoms) {
	monom a(11, 7, 4, 2);
	monom b(21, 7, 4, 2);
	a += b;
	EXPECT_EQ(32, a.GetCoefficient());
	EXPECT_EQ(742, a.GetDegree());
}

TEST(Monom, ThrowWhenAssigmentAddWithDifferentDegree) {
	monom a(11, 7, 5, 2);
	monom b(21, 7, 4, 2);
	ASSERT_ANY_THROW(a += b);
}

TEST(Monom, CorrectAssigmentSubMonoms) {
	monom a(11, 7, 4, 2);
	monom b(21, 7, 4, 2);
	a -= b;
	EXPECT_EQ(-10, a.GetCoefficient());
	EXPECT_EQ(742, a.GetDegree());
}

TEST(Monom, ThrowWhenAssigmentSubWithDifferentDegree) {
	monom a(11, 7, 5, 2);
	monom b(21, 7, 4, 2);
	ASSERT_ANY_THROW(a -= b);
}

TEST(Monom, CorrectAssigmentMultiplicateMonoms) {
	monom a(11, 7, 4, 2);
	monom b(21, 2, 0, 2);
	a *= b;
	EXPECT_EQ(231, a.GetCoefficient());
	EXPECT_EQ(944, a.GetDegree());
}

TEST(Monom, ThrowWhenAssigmentMultiplicateDegreeResultsGreat9) {
	monom a(11, 7, 5, 2);
	monom b(21, 7, 4, 2);
	ASSERT_ANY_THROW(a *= b);
}

TEST(Monom, ThrowWhenAssigmentDivisionByZeroMonom) {
	monom a(11, 7, 5, 2);
	monom b(0, 0);
	ASSERT_ANY_THROW(a /= b);
}

TEST(Monom, CorrectAssigmentMultiplicateMonomAndNumber) {
	monom a(11, 7, 4, 2);
	double b = -2;
	a *= b;
	EXPECT_EQ(-22, a.GetCoefficient());
	EXPECT_EQ(742, a.GetDegree());
}

TEST(Monom, CorrectAssigmentDivisionMonomAndNumber) {
	monom a(10, 7, 4, 2);
	double b = -2;
	a /= b;
	EXPECT_EQ(-5, a.GetCoefficient());
	EXPECT_EQ(742, a.GetDegree());
}

TEST(Monom, CorrectAssigmentDivisionMonoms) {
	monom a(10, 7, 4, 2);
	monom b(5, 3, 4, 0);
	a /= b;
	EXPECT_EQ(2, a.GetCoefficient());
	EXPECT_EQ(402, a.GetDegree());
}

TEST(Monom, ThrowWhenAssigmentDivisionByZero) {
	monom a(11, 7, 5, 2);
	ASSERT_ANY_THROW(a /= 0);
}

TEST(Monom, EqualMonoms) {
	monom a(11, 0, 0, 2);
	monom b(11, 0, 0, 2);
	EXPECT_EQ(true, a == b);
}

TEST(Monom, NotEqualCoefficientOfMonoms) {
	monom a(11, 0, 0, 2);
	monom b(10, 0, 0, 2);
	EXPECT_EQ(true, a != b);
}

TEST(Monom, NotEqualDegreeOfMonoms) {
	monom a(11, 0, 0, 2);
	monom b(11, 1, 0, 2);
	EXPECT_EQ(true, a != b);
}

TEST(Monom, DegreeXofMonomLess) {
	monom a(11, 1, 2, 2);
	monom b(11, 2, 2, 2);
	EXPECT_EQ(true, a < b);
}

TEST(Monom, DegreeYofMonomLess) {
	monom a(11, 2, 1, 2);
	monom b(11, 2, 2, 2);
	EXPECT_EQ(true, a < b);
}

TEST(Monom, DegreeZofMonomLess) {
	monom a(11, 2, 2, 1);
	monom b(11, 2, 2, 2);
	EXPECT_EQ(true, a < b);
}

TEST(Monom, CoefficientOfMonomLess) {
	monom a(10, 2, 2, 2);
	monom b(11, 2, 2, 2);
	EXPECT_EQ(true, a < b);
}

TEST(Monom, CoefficientOfMonomGreate) {
	monom a(12, 2, 2, 2);
	monom b(11, 2, 2, 2);
	EXPECT_EQ(true, a > b);
}

TEST(Monom, DegreeXOfMonomGreate) {
	monom a(11, 2, 2, 2);
	monom b(11, 1, 2, 2);
	EXPECT_EQ(true, a > b);
}

