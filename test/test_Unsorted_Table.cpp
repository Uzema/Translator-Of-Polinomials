#include <gtest.h>
#include <random>
#include "Polynomial.h"
#include "Unsorted_Table.h"

TEST(UnsortedTable, CanInsert) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	ASSERT_NO_THROW(t.insert("abc", p));
}

TEST(UnsortedTable, CorrectInsersionOrder) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abd", p);
	t.insert("abe", p);
	t.insert("abc", p);
	t.insert("abb", p);
	EXPECT_EQ("abd", t[0].first);
	EXPECT_EQ("abe", t[1].first);
	EXPECT_EQ("abc", t[2].first);
	EXPECT_EQ("abb", t[3].first);
}

TEST(UnsortedTable, ThrowsWhenElemenetsWithSameKeyGetInserted) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abd", p);
	t.insert("abe", p);
	t.insert("abc", p);
	t.insert("abb", p);
	ASSERT_ANY_THROW(t.insert("abc", p));
}

TEST(UnsortedTable, CorrectlyFindsElement) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abd", p);
	t.insert("abe", p);
	t.insert("abc", p);
	t.insert("abb", p);
	auto it = t.begin();
	++(++it);
	EXPECT_EQ(it, t.find("abc"));
}

TEST(UnsortedTable, CorrectlyDoesntFindElement) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abd", p);
	t.insert("abe", p);
	t.insert("abc", p);
	t.insert("abb", p);
	EXPECT_EQ(t.end(), t.find("aaa"));
}

TEST(UnsortedTable, CorrectlyEraseElement) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abd", p);
	t.insert("abe", p);
	t.insert("abc", p);
	t.insert("abb", p);
	auto it = t.begin();
	++(++it);
	EXPECT_EQ(it, t.erase("abc"));
}

TEST(UnsortedTable, ThrowsWhenTryToEraseNotExistingElement) {
	UnsortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abd", p);
	t.insert("abe", p);
	t.insert("abc", p);
	t.insert("abb", p);
	ASSERT_ANY_THROW(t.erase("a"));
}

TEST(UnsortedTable, StressTest) {
	UnsortedTable<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	int count = 0;

	for (int i = 0; i < 1000; i++) {
		int r = rand() % 10;
		if (r < 7 || i < 50) {
			t.insert(i, p);
			count++;
		}
		else {
			int j = i / 2;
			while (t.find(j) == t.end()) {
				j--;
			}
			if (t.find(j) != t.end()) {
				t.erase(j);
				count--;
			}
		}
	}

	EXPECT_EQ(count, t.size());
}