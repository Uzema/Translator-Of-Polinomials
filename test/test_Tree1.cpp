#include <gtest.h>
#include "AVLTree.h"

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

TEST(AVLTree, RotateRight) {//h+1 h+1 h
	AVLTree<float, int> t;
	t.insert(5, 1);
	t.insert(6, 1);
	t.insert(3, 1);
	t.insert(2, 1);
	t.insert(4, 1);
	t.insert(1, 1);
	t.insert(4.5, 1);
	ASSERT_NO_THROW();
}