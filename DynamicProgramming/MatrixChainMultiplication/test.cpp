#include <cstdlib>
#include <utility>
#include <string>
#include "gtest/gtest.h"
#include "matrixChainMultiplication.h"
using namespace std;

class MatrixChainMultiplicationTest : public testing::Test {
 protected:
   virtual void SetUp() {
      _matrixChain = (matrix*) malloc(100 * sizeof(matrix));
      if (!_matrixChain) exit(1);
      optimizer = new MatrixChainMultiplication(100);
   }
   virtual void TearDown() {
      free(_matrixChain);
      delete optimizer;
      optimizer = NULL; 
   }
   matrix* _matrixChain;
   MatrixChainMultiplication* optimizer;
};

TEST_F(MatrixChainMultiplicationTest, testcase1) {
   _matrixChain[0] = make_pair(10, 100);
   _matrixChain[1] = make_pair(100, 5);
   _matrixChain[2] = make_pair(5, 50);
   EXPECT_EQ(
      7500, 
      optimizer->optimize(_matrixChain, 3)
   );
   EXPECT_STREQ(
      "((A0A1)A2)", 
      optimizer->printOrder(0, 2).c_str()
   );
}

TEST_F(MatrixChainMultiplicationTest, testcase2) {
   _matrixChain[0] = make_pair(10, 200);
   _matrixChain[1] = make_pair(200, 3);
   _matrixChain[2] = make_pair(3, 60);
   _matrixChain[3] = make_pair(60, 10);
   _matrixChain[4] = make_pair(10, 100);
   EXPECT_EQ(
      13800, 
      optimizer->optimize(_matrixChain, 5)
   );
   EXPECT_STREQ(
      "((A0A1)((A2A3)A4))", 
      optimizer->printOrder(0, 4).c_str()
   );
}
TEST_F(MatrixChainMultiplicationTest, testcase3) {
   _matrixChain[0] = make_pair(300, 200);
   _matrixChain[1] = make_pair(200, 100);
   _matrixChain[2] = make_pair(100, 50);
   _matrixChain[3] = make_pair(50, 5);
   EXPECT_EQ(
      425000, 
      optimizer->optimize(_matrixChain, 4)
   );
   EXPECT_STREQ(
      "(A0(A1(A2A3)))", 
      optimizer->printOrder(0, 3).c_str()
   );
}
TEST_F(MatrixChainMultiplicationTest, testcase4) {
   _matrixChain[0] = make_pair(10, 300);
   _matrixChain[1] = make_pair(300, 20);
   _matrixChain[2] = make_pair(20, 20);
   _matrixChain[3] = make_pair(20, 300);
   _matrixChain[4] = make_pair(300, 10);
   EXPECT_EQ(
      126000, 
      optimizer->optimize(_matrixChain, 5)
   );
   EXPECT_STREQ(
      "((A0A1)(A2(A3A4)))", 
      optimizer->printOrder(0, 4).c_str()
   );
}
