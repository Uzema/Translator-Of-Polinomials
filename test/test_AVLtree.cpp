#pragma once
#include <gtest.h>
#include "AVLTree.h"

class TreeTesting : public::testing::Test {
protected:
	virtual void SetUp() {
		t.insert(5, p);
		t.insert(6, p);
		t.insert(4, p);
	}

	virtual void TearDown() {
		t.testAVLProperties();
	}

	AVLTree<float, polynom> t;
	polynom p = polynom(monom(1, 100));
};


TEST(AVLTree, CanCreateTree) {
	AVLTree<int, int> t;
	ASSERT_NO_THROW();
}

TEST(AVLTree, CorrectSize) {
	AVLTree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(5, p);
	t.insert(6, p);
	t.insert(4, p);
	t.insert(7, p);
	t.insert(8, p);
	EXPECT_EQ(5, t.size());
}

TEST(AVLTree, EmptyTree1) {
	AVLTree<int, polynom> t;
	EXPECT_EQ(true, t.empty());
}

TEST(AVLTree, EmptyTree2) {
	AVLTree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	t.insert(5, p);
	EXPECT_EQ(false, t.empty());
}

TEST(AVLTree, CanGetValue) {
	AVLTree<int, int> t;
	t.insert(5, 228);
	EXPECT_EQ(228, t.getValue(5));
}

TEST_F(TreeTesting, CantInsertUsingTheSameKey) {
	ASSERT_ANY_THROW(t.insert(5, p));
}

TEST_F(TreeTesting, RotateRight1) {//h+2(h+1 h+1) h
	t.insert(2, p);
	t.insert(4.2, p);
	t.insert(1, p);
	t.insert(4.5, p);
	EXPECT_EQ(3, t.getHeight());
}

TEST_F(TreeTesting, RotateRight2) {//h+2(h+1 h) h
	t.insert(2, p);
	t.insert(4.2, p);
	t.insert(1, p);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, BigRotateRight) {//h+2(h h+1) h
	t.insert(2, p);
	t.insert(4.2, p);
	t.insert(4.5, p);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, RotateLeft1) {//h h+2(h+1 h+1)
	t.insert(7, p);
	t.insert(5.5, p);
	t.insert(5.2, p);
	t.insert(8, p);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, RotateLeft2) {//h h+2(h h+1)
	t.insert(7, p);
	t.insert(5.5, p);
	t.insert(8, p);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, BigRotateLeft) {//h h+2(h+1 h)
	t.insert(7, p);
	t.insert(5.5, p);
	t.insert(5.2, p);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, Erase) {
	t.erase(6);
	EXPECT_EQ(2, t.size());
}

TEST_F(TreeTesting, EraseThrowsWhenTryToEraseNotExisting) {
	ASSERT_ANY_THROW(t.erase(20));
}

TEST_F(TreeTesting, EraseDoesntBreakBalance1) {
	t.insert(2, p);
	t.insert(4.2, p);
	t.insert(1, p);
	t.insert(4.5, p);
	t.erase(6);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, EraseDoesntBreakBalance2) {
	t.insert(2, p);
	t.insert(4.2, p);
	t.insert(1, p);
	t.insert(4.5, p);
	t.erase(5);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, EraseDoesntBreakBalance3) {
	t.insert(7, p);
	t.insert(5.5, p);
	t.insert(5.2, p);
	t.insert(8, p);
	t.erase(4);
	EXPECT_EQ(2, t.getHeight());
}

TEST_F(TreeTesting, EraseDoesntBreakBalance4) {
	t.insert(7, p);
	t.insert(5.5, p);
	t.insert(5.2, p);
	t.insert(8, p);
	t.erase(5);
	EXPECT_EQ(2, t.getHeight());
}

TEST(AVLTree, Copy) {
	AVLTree<float, int> t;
	t.insert(5, 123);
	t.insert(6, 234);
	t.insert(4, 345);

	AVLTree<float, int> ot(t);
	EXPECT_EQ(123, ot.getValue(5));
	EXPECT_EQ(234, ot.getValue(6));
	EXPECT_EQ(345, ot.getValue(4));
}

TEST(AVLTree, CopyAssignment) {
	AVLTree<float, int> t;
	t.insert(5, 123);
	t.insert(6, 234);
	t.insert(4, 345);

	AVLTree<float, int> ot = t;
	EXPECT_EQ(123, ot.getValue(5));
	EXPECT_EQ(234, ot.getValue(6));
	EXPECT_EQ(345, ot.getValue(4));
}

TEST(AVLTree, StressTest) {
	AVLTree<int, polynom> t;
	polynom p = polynom(monom(1, 100));
	int j = 1;
	for (int i = 0; i < 1000000; i++) {
		int r = rand() % 10;
		if (r < 7 || i < 500000)
			t.insert(i, p);
		else {
			t.erase(j);
			j++;
		}
	}
	ASSERT_NO_THROW();
}