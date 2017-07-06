#include "gtest/gtest.h"
#include "BST.h"
using namespace std;

class BinarySearchTreeTest : public testing::Test {
 protected:
   virtual void SetUp() {
   }
   virtual void TearDown() {
   }

   BinarySearchTree<int> tree;
};

TEST_F(BinarySearchTreeTest, add) {
   tree.add(5);
   tree.add(3);
   tree.add(7);
   EXPECT_STREQ(
      " 3 5 7",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, add_same_number) {
   tree.add(10);
   tree.add(10);
   tree.add(9);
   EXPECT_STREQ(
      " 9 10 10",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_not_found) {
   tree.add(10);
   tree.add(13);
   tree.remove(12);
   EXPECT_STREQ(
      " 10 13",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_leave) {
   tree.add(8);
   tree.add(10);
   tree.add(7);
   tree.add(13);
   tree.remove(13);
   EXPECT_STREQ(
      " 7 8 10",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_middle) {
   tree.add(8);
   tree.add(10);
   tree.add(9);
   tree.add(7);
   tree.add(13);
   tree.remove(10);
   EXPECT_STREQ(
      " 7 8 9 13",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_root) {
   tree.add(8);
   tree.add(10);
   tree.add(9);
   tree.add(7);
   tree.add(13);
   tree.remove(8);
   EXPECT_STREQ(
      " 7 9 10 13",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_root_left_child) {
   tree.add(8);
   tree.add(10);
   tree.add(9);
   tree.add(7);
   tree.add(5);
   tree.add(8);
   tree.add(13);
   tree.remove(7);
   EXPECT_STREQ(
      " 5 8 8 9 10 13",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_successor_is_leaf) {
   tree.add(8);
   tree.add(10);
   tree.add(9);
   tree.add(7);
   tree.add(13);
   tree.add(14);
   tree.add(12);
   tree.add(22);
   tree.remove(10);
   EXPECT_STREQ(
      " 7 8 9 12 13 14 22",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_successor_with_right_branch) {
   tree.add(8);
   tree.add(10);
   tree.add(9);
   tree.add(7);
   tree.add(11);
   tree.add(13);
   tree.add(12);
   tree.add(14);
   tree.remove(10);
   EXPECT_STREQ(
      " 7 8 9 11 12 13 14",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_single_root) {
   tree.add(8);
   tree.remove(8);
   EXPECT_STREQ(
      "",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_node_without_left_branch) {
   tree.add(8);
   tree.add(10);
   tree.add(13);
   tree.add(12);
   tree.remove(8);
   EXPECT_STREQ(
      " 10 12 13",
      tree.printTree().c_str()
   );
}

TEST_F(BinarySearchTreeTest, remove_node_without_right_branch) {
   tree.add(8);
   tree.add(6);
   tree.add(4);
   tree.add(5);
   tree.add(3);
   tree.add(2);
   tree.remove(6);
   EXPECT_STREQ(
      " 2 3 4 5 8",
      tree.printTree().c_str()
   );
}
