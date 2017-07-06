#ifndef BST_H
#define BST_H
#include <string>
using namespace std;

template<typename T>
class BinaryTreeNode;

template<typename T>
class BinarySearchTree {
   public:
      BinarySearchTree();
      ~BinarySearchTree();

      void add(T);
      void remove(T);
      string printTree() const;

   protected:
      BinaryTreeNode<T>* findSuccessor(BinaryTreeNode<T>*) const;
      void transplant(BinaryTreeNode<T>*, BinaryTreeNode<T>*);

      BinaryTreeNode<T>* _root;
};

template<typename T>
class BinaryTreeNode {

   friend class BinarySearchTree<T>;

   public:
      BinaryTreeNode();
      ~BinaryTreeNode();

      string printNode() const;

   protected:
      T _value;
      BinaryTreeNode* _left;
      BinaryTreeNode* _right;
      BinaryTreeNode* _parent;
};

#endif
