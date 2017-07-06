#include <cstdlib>
#include <utility>
#include <string>
#include "gtest/gtest.h"
#include "optimalBST.h"
using namespace std;

class OptimalBSTTest : public testing::Test {
 protected:
   virtual void SetUp() {
      optimizer = new OptimalBST(100);
   }
   virtual void TearDown() {
      delete optimizer;
      optimizer = NULL;
   }
   OptimalBST* optimizer;
};

TEST_F(OptimalBSTTest, testcase1) {
   const float p[] = {0.3};
   const float q[] = {0.4, 0.3};
   EXPECT_FLOAT_EQ(
      1.70,
      optimizer->optimize(p, q, 1)
   );
   EXPECT_STREQ(
      " 0",
      optimizer->printTree(0, 0, 1).c_str()
   );
   optimizer->drawTree(0, 0, 1, "", false);
}

TEST_F(OptimalBSTTest, testcase2) {
   const float p[] = {0.15, 0.10, 0.05, 0.10, 0.20};
   const float q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
   EXPECT_FLOAT_EQ(
      2.75,
      optimizer->optimize(p, q, 5)
   );
   EXPECT_STREQ(
      " 1 0 4 3 2",
      optimizer->printTree(0, 4, 5).c_str()
   );
   optimizer->drawTree(0, 4, 5, "", false);
}

TEST_F(OptimalBSTTest, testcase3) {
   const float p[] = {0.65, 0.05, 0.05, 0.05, 0.05, 0.05};
   const float q[] = {0.04, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
   EXPECT_FLOAT_EQ(
      1.81,
      optimizer->optimize(p, q, 6)
   );
   EXPECT_STREQ(
      " 0 2 1 4 3 5",
      optimizer->printTree(0, 5, 6).c_str()
   );
   optimizer->drawTree(0, 5, 6, "", false);
}
TEST_F(OptimalBSTTest, testcase4) {
   const float p[] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.65};
   const float q[] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.04};
   EXPECT_FLOAT_EQ(
      1.81,
      optimizer->optimize(p, q, 6)
   );
   EXPECT_STREQ(
      " 5 1 0 3 2 4",
      optimizer->printTree(0, 5, 6).c_str()
   );
   optimizer->drawTree(0, 5, 6, "", false);
}
TEST_F(OptimalBSTTest, testcase5) {
   const float p[] = {0.1, 0.15, 0.2, 0.15, 0.1};
   const float q[] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
   EXPECT_FLOAT_EQ(
      2.50,
      optimizer->optimize(p, q, 5)
   );
   EXPECT_STREQ(
      " 2 1 0 3 4",
      optimizer->printTree(0, 4, 5).c_str()
   );
   optimizer->drawTree(0, 4, 5, "", false);
}

TEST_F(OptimalBSTTest, testcase6) {
   const float p[] = {0.1, 0.15, 0.2, 0.15, 0.1};
   const float q[] = {0.15, 0.15, 0.00, 0.00, 0.00, 0.00};
   EXPECT_FLOAT_EQ(
      2.45,
      optimizer->optimize(p, q, 5)
   );
   EXPECT_STREQ(
      " 1 0 3 2 4",
      optimizer->printTree(0, 4, 5).c_str()
   );
   optimizer->drawTree(0, 4, 5, "", false);
}
