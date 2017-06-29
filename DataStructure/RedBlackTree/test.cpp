#include "gtest/gtest.h"
#include "RBT.h"
using namespace std;

class RedBlackTreeTest : public testing::Test {
 protected:
   virtual void SetUp() {
   }
   virtual void TearDown() {
   }

	RedBlackTree<int> tree;
};

TEST_F(RedBlackTreeTest, empty_tree) {
	EXPECT_STREQ(
		"",
		tree.printTree().c_str()
	);
}

TEST_F(RedBlackTreeTest, add) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	EXPECT_STREQ(
		" 5 3 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_color
	);
}

TEST_F(RedBlackTreeTest, add_same_number) {
	tree.add(10);
	tree.add(10);
	tree.add(9);
	EXPECT_STREQ(
		" 10 9 10",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_color
	);
}

TEST_F(RedBlackTreeTest, transplant) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	RedBlackNode<int>* root_node = tree._root;
	RedBlackNode<int>* left_node = tree._root->_left;
	tree.transplant(root_node, left_node);
	left_node->_right = root_node;
	root_node->_parent = left_node;
	root_node->_left = NULL;
	EXPECT_STREQ(
		" 3 5 7",
		tree.printTree().c_str()
	);
}

TEST_F(RedBlackTreeTest, right_rotate) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.rightRotate(tree._root, tree._root->_left);
	EXPECT_STREQ(
		" 3 5 7",
		tree.printTree().c_str()
	);
}

TEST_F(RedBlackTreeTest, left_rotate) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.leftRotate(tree._root, tree._root->_right);
	EXPECT_STREQ(
		" 7 5 3",
		tree.printTree().c_str()
	);
}

TEST_F(RedBlackTreeTest, uncle_is_red) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(6);
	EXPECT_STREQ(
		" 5 3 7 6",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_left->_color
	);
}

TEST_F(RedBlackTreeTest, uncle_is_black_right_rotate) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(5);
	tree.add(6);
	EXPECT_STREQ(
		" 5 3 6 5 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_right->_color
	);
}

TEST_F(RedBlackTreeTest, uncle_is_black_left_rotate) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(6);
	tree.add(5);
	EXPECT_STREQ(
		" 5 3 6 5 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_right->_color
	);
}

TEST_F(RedBlackTreeTest, left_branch_uncle_is_black_right_rotate) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(4);
	tree.add(3);
	EXPECT_STREQ(
		" 5 3 3 4 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_right->_color
	);
}

TEST_F(RedBlackTreeTest, left_branch_uncle_is_black_left_rotate) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(4);
	tree.add(4);
	EXPECT_STREQ(
		" 5 4 3 4 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_right->_color
	);
}

TEST_F(RedBlackTreeTest, left_branch_uncle_is_red) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(1);
	EXPECT_STREQ(
		" 5 3 1 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_left->_color
	);
}

TEST_F(RedBlackTreeTest, add_10_nodes) {
	tree.add(5);
	tree.add(1);
	tree.add(10);
	tree.add(3);
	tree.add(6);
	tree.add(7);
	tree.add(4);
	tree.add(2);
	tree.add(8);
	tree.add(9);
	EXPECT_STREQ(
		" 5 3 1 2 4 7 6 9 8 10",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_right->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_left->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_right->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_right->_right->_color
	);
}

TEST_F(RedBlackTreeTest, delete_node_not_exist) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.remove(8);
	EXPECT_STREQ(
		" 5 3 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_color
	);
}

TEST_F(RedBlackTreeTest, delete_red_leaf) {
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.remove(3);
	EXPECT_STREQ(
		" 5 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_right->_color
	);
}

TEST_F(RedBlackTreeTest, delete_single_root) {
	tree.add(5);
	tree.remove(5);
	EXPECT_STREQ(
		"",
		tree.printTree().c_str()
	);
}

TEST_F(RedBlackTreeTest, delete_red_with_right_child_successor) {
	tree.add(5);
	tree.add(4);
	tree.add(7);
	tree.add(1);
	tree.add(3);
	tree.add(2);
	tree.remove(3);
	EXPECT_STREQ(
		" 5 2 1 4 7",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_right->_color
	);
}

TEST_F(RedBlackTreeTest, delete_red_with_leaf_successor) {
	tree.add(7);
	tree.add(5);
	tree.add(9);
	tree.add(1);
	tree.add(3);
	tree.add(2);
	tree.add(4);
	tree.add(6);
	tree.remove(3);
	EXPECT_STREQ(
		" 7 4 1 2 5 6 9",
		tree.printTree().c_str()
	);
	EXPECT_FALSE(
		tree._root->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_right->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_left->_color
	);
	EXPECT_FALSE(
		tree._root->_left->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_left->_right->_color
	);
	EXPECT_TRUE(
		tree._root->_left->_right->_right->_color
	);
}
