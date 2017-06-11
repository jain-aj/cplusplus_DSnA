#ifndef RBT_H
#define RBT_H
#include <string>
using namespace std;

class RedBlackTreeTest;

template<typename T>
class RedBlackTree;

template<typename T>
class RedBlackNode {
	friend class RedBlackTree<T>;

	public:
		RedBlackNode();
		~RedBlackNode();

		string printNode() const;

		//public for easy testing
		RedBlackNode* _parent;
		RedBlackNode* _left;
		RedBlackNode* _right;
		bool _color;
		T _value;
};

template<typename T>
class RedBlackTree {
	public:
		RedBlackTree();
		~RedBlackTree();

		string printTree() const;
		void add(T);
		void remove(T);

		//public for easy testing
		void rightRotate(RedBlackNode<T>*, RedBlackNode<T>*);
		void leftRotate(RedBlackNode<T>*, RedBlackNode<T>*);
		void colorFix(RedBlackNode<T>*);
		RedBlackNode<T>* findSuccessor(RedBlackNode<T>*) const;
		void transplant(RedBlackNode<T>*, RedBlackNode<T>*);

		RedBlackNode<T>* _root;
};

#endif
