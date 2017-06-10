#include <string>
#include "BST.h"
using namespace std;

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode() {
	_value = T(0);
	_left = NULL;
	_right = NULL;
	_parent = NULL;
}

template<typename T>
BinaryTreeNode<T>::~BinaryTreeNode() {
	if (_right) delete _right;
	if (_left) delete _left;
	_right = _left = NULL;
}

template<typename T>
string BinaryTreeNode<T>::printNode() const {
	string s = string();
	if (_left) s += _left->printNode();
	s += string(" ") + to_string(_value);
	if (_right) s += _right->printNode(); 
	return s;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
	_root = NULL;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	if (_root) delete _root;
}

template<typename T>
void BinarySearchTree<T>::add(T v) {
	BinaryTreeNode<T>* node = new BinaryTreeNode<T>();
	node->_value = v;

	BinaryTreeNode<T>* current_node = _root;
	BinaryTreeNode<T>** current_node_address = &_root;
	BinaryTreeNode<T>* parent_node = NULL;
	while(current_node) {
		parent_node = current_node;
		if (current_node->_value > v) {
			current_node_address = &current_node->_left;
			current_node = current_node->_left;
		}
		else {
			current_node_address = &current_node->_right;
			current_node = current_node->_right;
		}
	}
	node->_parent = parent_node;
	*current_node_address = node;
	return;	
}

template<typename T>
void BinarySearchTree<T>::remove(T v) {
	BinaryTreeNode<T>* current_node = _root;
	while(current_node && current_node->_value != v) {
		if (current_node->_value > v) current_node = current_node->_left;	
		else current_node = current_node->_right;
	}

	if (current_node) {
		if (!current_node->_left and !current_node->_right) {
			if (current_node->_parent) {
				transplant(current_node, NULL);
			}
			else {
				_root = NULL;
			}
		}
		else if (!current_node->_left) {
			if (current_node->_parent) {
				transplant(current_node, current_node->_right);
				current_node->_right->_parent = current_node->_parent;
			}
			else {
				_root = current_node->_right;
				current_node->_right->_parent = NULL;
			}
		}
		else if (!current_node->_right) {
			if (current_node->_parent) {
				transplant(current_node, current_node->_left);
				current_node->_left->_parent = current_node->_parent;
			}
			else {
				_root = current_node->_left;
				current_node->_left->_parent = NULL;
			}
		}
		else {
   		BinaryTreeNode<T>* successor = findSuccessor(current_node);
			if (!successor->_right) {
				transplant(successor, NULL);
			}
			else {
				transplant(successor, successor->_right);
				successor->_right->_parent = successor->_parent;
			}

			if (current_node->_parent) {
				transplant(current_node, successor);
				successor->_parent = current_node->_parent;
			}
			else {
				_root = successor;
				successor->_parent = NULL;
			}
			successor->_left = current_node->_left;
			successor->_right = current_node->_right;
		}
		current_node->_left = current_node->_right = NULL;
		delete current_node;
	}
	return;
}


template<typename T>
void BinarySearchTree<T>::transplant(
	BinaryTreeNode<T>* dst, 
	BinaryTreeNode<T>* value
) {
	if (dst && dst->_parent) {
		if (dst->_parent->_left == dst) dst->_parent->_left = value;
		else dst->_parent->_right = value;
	}
	return;
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::findSuccessor(
	BinaryTreeNode<T>* current
) const {
	while(current && current->_left) {
		current = current->_left;
	}
	return current;
}

template<typename T>
string BinarySearchTree<T>::printTree() const {
	if (_root) return _root->printNode();
	return string("");
}

template class BinaryTreeNode<int>;
template class BinarySearchTree<int>;
