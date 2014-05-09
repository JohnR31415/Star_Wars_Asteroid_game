#include "gtest\gtest.h"
#include "Engine.h"

TEST(MySampleTestCategory, MySampleTestName)
{
	int i = 5;
	int j = i * i;
	EXPECT_EQ(25, j);
	EXPECT_EQ(3, j); // Oh noes!

	EXPECT_TRUE(Engine::sampleFunctionThatReturnsTrue());
	EXPECT_FALSE(Engine::sampleFunctionThatReturnsTrue()); // Oh noes!
}