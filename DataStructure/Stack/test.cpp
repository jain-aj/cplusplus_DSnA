#include "gtest/gtest.h"
#include "stack.h"
using namespace std;

class StackTest : public testing::Test {
 protected:
   virtual void SetUp() {
		stack.set_size(100);
   }
   virtual void TearDown() {
   }

	Stack<int> stack;
};

TEST_F(StackTest, max_size) {
	EXPECT_EQ(100, stack._size);
}

TEST_F(StackTest, push_then_pop) {
	stack.push(10);
	stack.push(12);
	EXPECT_EQ(
		12,
		stack.pop()
	);
	EXPECT_EQ(
		10,
		stack.pop()
	);
}

TEST_F(StackTest, pop_then_push) {
	stack.pop();
	stack.push(10);
	stack.push(12);
	EXPECT_EQ(
		12,
		stack.pop()
	);
	stack.push(1917);
	EXPECT_EQ(
		1917,
		stack.pop()
	);
}
