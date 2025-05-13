#include <gtest.h>
#include "BRTree.h"
#include "Polynomial.h"

TEST(BRtree, createTree) {
	BRtree<std::string, polynom> t;
	ASSERT_NO_THROW(t);
}

TEST(BRtree, insertInTree) {
	BRtree<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	ASSERT_NO_THROW(t.insert("abc", p));
}

TEST(BRtree, copiedTreeHasItsOwnMemory) {
	BRtree<std::string, polynom> t1;
	BRtree<std::string, polynom> t2(t1);
	EXPECT_NE(&t1, &t2);
}

TEST(BRtree, canAssignTreeToItself) {
	BRtree<std::string, polynom> t;
	ASSERT_NO_THROW(t = t);
}

TEST(BRtree, correctlyCopyTree) {
	BRtree<std::string, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert("aba", p);
	t.insert("abc", p);
	t.insert("abb", p);
	BRtree<std::string, polynom> tc = t;
	BRtree<std::string, polynom>::iterator it = tc.begin();
	EXPECT_EQ("aba", it.GetKey());
	++it;
	EXPECT_EQ("abb", it.GetKey());
	++it;
	EXPECT_EQ("abc", it.GetKey());
}

TEST(BRtree, SizeAfterInsertAndErasee) {
	BRtree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(3, p);
	t.insert(1, p);
	t.insert(4, p);
	t.erase(1);
	t.insert(5, p);
	t.erase(3);
	t.insert(6, p);
	EXPECT_EQ(3, t.size());
}

TEST(BRtree, findInTree) {
	BRtree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(3, p);
	t.insert(1, p);
	t.insert(4, p);
	t.insert(5, p);
	t.insert(2, p);
	t.insert(6, p);
	ASSERT_NO_THROW(t.find(5));
}

TEST(BRtree, NotFindNotExistingElement) {
	BRtree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(3, p);
	t.insert(1, p);
	t.insert(4, p);
	t.insert(5, p);
	t.insert(2, p);
	t.insert(6, p);
	ASSERT_NO_THROW(t.find(7));
}

TEST(BRtree, EraseFromTree) {
	BRtree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(2, p);
	t.insert(3, p);
	t.insert(1, p);
	t.erase(3);
	ASSERT_NO_THROW(t);
}

TEST(BRtree, EraseFromTreeNotExistingElement) {
	BRtree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(3, p);
	t.insert(1, p);
	ASSERT_ANY_THROW(t.erase(2));
}

TEST(BRtree, insertInTreeSimilarKey) {
	BRtree<std::string, int> t;
	t.insert("abc", 4);
	t.insert("abc", 8);
	EXPECT_EQ(8, t.find("abc")->value);
}

TEST(BRtree, iteratorCycle) {
	BRtree<int, polynom> t;
	polynom p0 = polynom(monom(1, 100));
	polynom p1 = polynom(monom(1, 100));
	polynom p2 = polynom(monom(1, 100));
	t.insert(4, p0);
	t.insert(3, p1);
	t.insert(2, p2);
	t.insert(5, p1);
	t.insert(6, p2);
	int i = 2;
	BRtree<int, polynom>::iterator it = t.begin();
	for (it; it != t.end(); ++it) {
		EXPECT_EQ(i, it.GetKey());
		i++;
	}
}

TEST(BRtree, StressTest) {
	BRtree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	int j = 1;
	int maxsize = 0;
	for (int i = 0; i < 100000; i++) {
		int r = rand() % 10;
		if(maxsize < t.size())
			maxsize = t.size();
		if (r < 7 || i < 50000)
			t.insert(i, p);
		else {
			t.erase(j);
			j++;
		}
	}
	//std::cout << maxsize;
	ASSERT_NO_THROW(t);
}