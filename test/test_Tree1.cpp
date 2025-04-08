#pragma once
#include <gtest.h>
#include "AVLTree.h"

class TreeTesting : public::testing::Test {
protected:
	virtual void SetUp() {
		t.insert(5, 1);
		t.insert(6, 1);
		t.insert(4, 1);
	}

	virtual void TearDown() {
		t.testAVLProperties();
	}

	AVLTree<float, int> t;
};


TEST(AVLTree, CanCreateTree) {
	AVLTree<int, int> t;
	ASSERT_NO_THROW();
}


TEST(AVLTree, CorrectSize) {
	AVLTree<int, int> t;
	t.insert(5, 1);
	t.insert(6, 1);
	t.insert(4, 1);
	t.insert(7, 1);
	t.insert(8, 1);
	EXPECT_EQ(5, t.size());
}

TEST(AVLTree, EmptyTree1) {
	AVLTree<int, int> t;
	EXPECT_EQ(true, t.empty());
}

TEST(AVLTree, EmptyTree2) {
	AVLTree<int, int> t;
	t.insert(5, 1);
	EXPECT_EQ(false, t.empty());
}

TEST(AVLTree, CanGetValue) {
	AVLTree<int, int> t;
	t.insert(5, 228);
	EXPECT_EQ(228, t.getValue(5));
}

TEST_F(TreeTesting, RotateRight) {//h+2(h+1 h+1) h
	t.insert(2, 1);
	t.insert(4.2, 1);
	t.insert(1, 1);
	t.insert(4.5, 1);
	EXPECT_EQ(3, t.getHeight());
}

TEST_F(TreeTesting, RotateLeft) {//h h+2(h+1 h+1)
	t.insert(7, 1);
	t.insert(5.5, 1);
	t.insert(5.2, 1);
	t.insert(8, 1);
	EXPECT_EQ(3, t.getHeight());
}

TEST(AVLTree, StressTest) {
	AVLTree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	int j = 1;
	int maxsize = 0;
	for (int i = 0; i < 1000000; i++) {
		int r = rand() % 10;
		if (maxsize < t.size())
			maxsize = t.size();
		if (r < 7 || i < 500000)
			t.insert(i, p);
		else {
			t.erase(j);
			j++;
		}
	}
	//std::cout << maxsize;
	ASSERT_NO_THROW(t);
}