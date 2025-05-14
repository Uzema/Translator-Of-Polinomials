#pragma once
#include <gtest.h>
#include "Hash_Table2.h"
#include "Polynomial.h"

TEST(hashies, stuff) {
	HashO<std::string, int> yo;
	yo.insert("bebra", 1);
	EXPECT_EQ(1, yo["bebra"]);
}

TEST(HashO, createHashTable) {
	HashO<std::string, int> h;
	ASSERT_NO_THROW(h);
}

TEST(HashO, insertHashTable) {
	HashO<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	EXPECT_EQ(h.getSize(), 1);
}

TEST(HashO, insertTwoIdencialElementInHashTable) {
	HashO<std::string, int> h;
	h.insert("abb", 4);
	h.insert("abb", 8);
	EXPECT_EQ(h.find("abb").getValue(), 8);
	//ASSERT_NO_THROW();
}

TEST(HashO, findInHashTable) {
	HashO<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	ASSERT_NO_THROW(h.find("abb"));
}

TEST(HashO, ThrowWhenDidntFindElementInHashTable) {
	HashO<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	ASSERT_ANY_THROW(h.find("ab"));
}

TEST(HashO, eraseElementFromHashTable) {
	HashO<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	h.erase("abb");
	EXPECT_EQ(h.getSize(), 0);
}

TEST(HashO, throwWhenEraseNotExistElement) {
	HashO<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	ASSERT_ANY_THROW(h.erase("ab"));
}

TEST(HashO, stressTest) {
	HashO<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	std::string chars1 = "ABCDEFGHIJKLMNTUVWXY";
	std::string chars2 = "abcdefgmnopqrstuvwxyz";
	std::string chars3 = "0123456789hijklOPQRSZ";
	int s = 0;
	for (char i : chars1) {
		for (char j : chars2) {
			for (char k : chars3) {
				std::string key;
				key += i;
				key += j;
				key += k;
				h.insert(key, p);
				s++;
			}
		}
	}
	EXPECT_EQ(s, h.getSize());
}