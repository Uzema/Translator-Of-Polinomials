#include <gtest.h>
#include <random>
#include "Sorted_Table.h"

TEST(SortedTable, CanInsert) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	ASSERT_NO_THROW(t.insert("abc", p));
}

TEST(SortedTable, CorrectInsertionOrder) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abc", p);
	t.insert("abd", p);
	t.insert("abb", p);
	EXPECT_EQ("abb", t[0].first);
	EXPECT_EQ("abc", t[1].first);
	EXPECT_EQ("abd", t[2].first);
}

TEST(SortedTable, ThrowWhenInsertTwoIdencialElement) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abc", p);
	ASSERT_ANY_THROW(t.insert("abc", p));
}

TEST(SortedTable, CorrectFindElement) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abc", p);
	t.insert("abd", p);
	t.insert("abb", p);
	EXPECT_EQ(t.begin(), t.find("abb"));
}

TEST(SortedTable, NotFindNotExistingElement) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abc", p);
	t.insert("abd", p);
	t.insert("abb", p);
	EXPECT_EQ(t.end(), t.find("a"));
}

TEST(SortedTable, CorrectEraseElement) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abc", p);
	t.insert("abd", p);
	t.insert("abb", p);
	t.erase("abc");
	EXPECT_EQ("abb", t[0].first);
	EXPECT_EQ("abd", t[1].first);
}

TEST(SortedTable, ThrowWhenEraseNotExistingElement) {
	SortedTable<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("abc", p);
	t.insert("abd", p);
	t.insert("abb", p);
	ASSERT_ANY_THROW(t.erase("ab"));
}

TEST(SortedTable, StressTest) {
	SortedTable<int, polynom> t;
	polynom p = polynom(monom(1, 100));

	for (int i = 0; i < 1000; i++) {
		int r = rand()%10;
		if (r < 7 || i < 50)
			t.insert(i, p);
		else {
			int j = i / 2;
			while (t.find(j) == t.end())
				j--;
			if(t.find(j) != t.end())
				t.erase(j);
		}
	}

	for(int i = 1;i < t.size();i++)
		EXPECT_LE(t[i - 1].first, t[i].first);
}
