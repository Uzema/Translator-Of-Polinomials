#pragma once
#include<gtest.h>
#include"Hash_Table1.h"
#include "Polynomial.h"

TEST(HashTable, createHashTable) {
	HashTable<int, int> h;
	ASSERT_NO_THROW(h);
}

TEST(HashTable, insertHashTable) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	EXPECT_EQ(1, h.size());
}

TEST(HashTable, throwWhenInsertTwoIdencialElementInHashTable) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	ASSERT_ANY_THROW(h.insert("abb",p));
}

TEST(HashTable, findInHashTable) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	ASSERT_NO_THROW(h.find("abb"));
}

TEST(HashTable, notFindNotExistingElementInHashTable) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	EXPECT_EQ(h.end(), h.find("ab"));
}

TEST(HashTable, eraseElementFromHashTable) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	h.erase("abb");
	EXPECT_EQ(0, h.size());
}

TEST(HashTable, throwWhenEraseNotExistElement) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	ASSERT_ANY_THROW(h.erase("ab"));
}

TEST(HashTable, iteratorCycleInHashTable) {
	HashTable<std::string, polynom> h;
	polynom p = polynom(monom(1, 100));
	h.insert("abb", p);
	h.insert("aba", p);
	h.insert("ahh", p);
	for(HashTable<std::string, polynom>::iterator it = h.begin(); it != h.end(); ++it)
		ASSERT_NO_THROW(*it);
}

TEST(HashTable, stressTest) {
	HashTable<std::string, polynom> h(262127);
	polynom p = polynom(monom(1, 100));
	std::string chars1 = "ABCDEFGHIJKLMNTUVWXY";
	std::string chars2 = "abcdefgmnopqrstuvwxyz";
	std::string chars3 = "0123456789hijklOPQRSZ";
	int s = 0;
	for (char i:chars1) {
		for (char j:chars2) {
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
	EXPECT_EQ(s, h.size());
}