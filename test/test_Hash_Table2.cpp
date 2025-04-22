#pragma once
#include <gtest.h>
#include "Hash_Table2.h"

TEST(hashies, stuff) {
	HashO<std::string, int> yo;
	yo.insert("bebra", 1);
	EXPECT_EQ(1, yo["bebra"]);
	//ASSERT_NO_THROW();
}