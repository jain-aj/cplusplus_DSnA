#include <string>
#include "RBT.h"
using namespace std;

template<typename T>
RedBlackNode<T>::RedBlackNode() {
	_parent = NULL;
	_right = NULL;
	_left = NULL;
	_color = false;
	_value = T(0);
}

template<typename T>
RedBlackNode<T>::~RedBlackNode() {
	if (_left) delete _left;
	if (_right) delete _right;
	_parent = _left = _right = NULL;
}

template<typename T>
string RedBlackNode<T>::printNode() const {
	string s;
	s += string(" ") + to_string(_value);
	if (_left) s += _left->printNode();
	if (_right) s += _right->printNode();
	return s;
}

template<typename T>
RedBlackTree<T>::RedBlackTree() {
	_root = NULL;
}

template<typename T>
RedBlackTree<T>::~RedBlackTree() {
	if (_root) delete _root;
}

template<typename T>
string RedBlackTree<T>::printTree() const {
	string s;
	if (_root) s += _root->printNode();
	return s;
}


template<typename T>
void RedBlackTree<T>::add(T v) {
	RedBlackNode<T>* node = new RedBlackNode<T>();
	node->_value = v;

	RedBlackNode<T>* current = _root;
	RedBlackNode<T>* parent = NULL;

	while(current) {
		parent = current;
		if (current->_value > v) current = current->_left;
		else current = current->_right;
	}

	node->_parent = parent;

	if (!_root) {
		_root = node;
	}
	else {
		node->_color = true;
		if (parent->_value > v) parent->_left = node;
		else parent->_right = node;
		if (parent->_color) colorFix(node);
	}
	return;
}

template<typename T>
void RedBlackTree<T>::colorFix(RedBlackNode<T>* z) {
	if (!z->_parent) {
		z->_color = false;
		return;
	}
	else if (!z->_parent->_color) return;

	RedBlackNode<T>* parent = z->_parent;
	RedBlackNode<T>* grandParent = parent->_parent;
	RedBlackNode<T>* uncle = NULL;

	if (grandParent->_left == parent) uncle = grandParent->_right;
	else uncle = grandParent->_left;

	if (uncle && uncle->_color) {
		uncle->_color = false;
		parent->_color = false;
		grandParent->_color = true;
		colorFix(grandParent);
	}
	else {
		if (grandParent->_left == parent) {
			if (parent->_left == z) {
				rightRotate(grandParent, parent);
				grandParent->_color = true;
				parent->_color = false;
			}
			else {
				leftRotate(parent, z);
				colorFix(parent);
			}
		}
		else {
			if (parent->_right == z) {
				leftRotate(grandParent, parent);
				grandParent->_color = true;
				parent->_color = false;
			}
			else {
				rightRotate(parent, z);
				colorFix(parent);
			}
		}
	}
	return;
}

template<typename T>
void RedBlackTree<T>::rightRotate(
	RedBlackNode<T>* parent,
	RedBlackNode<T>* child
) {
	transplant(child, child->_right);
	transplant(parent, child);
	child->_right = parent;
	parent->_parent = child;
}

template<typename T>
void RedBlackTree<T>::leftRotate(
	RedBlackNode<T>* parent,
	RedBlackNode<T>* child
) {
	transplant(child, child->_left);
	transplant(parent, child);
	child->_left = parent;
	parent->_parent = child;
}

template<typename T>
void RedBlackTree<T>::transplant(
	RedBlackNode<T>* dst, 
	RedBlackNode<T>* value
) {
	if (!dst->_parent) {
		_root = value;
	}
	else if (dst->_parent->_left == dst) {
		dst->_parent->_left = value;
	}
	else dst->_parent->_right = value;
	if (value) value->_parent = dst->_parent;
	return;
}

template<typename T>
void RedBlackTree<T>::remove(T value) {
	RedBlackNode<T>* current = _root;
	while(current && current->_value != value) {
		if (current->_value > value) {
			current = current->_left;
		}
		else {
			current = current->_right;
		}
	}

	if (current) {
		bool notColorFix = current->_color;
		RedBlackNode<T>* colorFixNodeParent = current->_parent;
		RedBlackNode<T>* colorFixNode = NULL;

		if(!current->_left) {
			transplant(current, current->_right);
			colorFixNode = current->_right;
		}
		else if (!current->_right) {
			transplant(current, current->_left);
			colorFixNode = current->_left;
		}
		else {
			RedBlackNode<T>* successor = findSuccessor(current);
			colorFixNodeParent = successor;
			notColorFix = successor->_color; 
			colorFixNode = successor->_right;
			if (successor != current->_right) {
				colorFixNodeParent = successor->_parent;
				transplant(successor, successor->_right);
				current->_right->_parent = successor;
				successor->_right = current->_right;
			}
			transplant(current, successor);
			current->_left->_parent = successor;
			successor->_left = current->_left;
			successor->_color = current->_color;
		}

		if (!notColorFix) {
			deleteColorFix(
				colorFixNodeParent,
				colorFixNode
			);
		}

		current->_left = current->_right = NULL;
		delete current;
	}
	return;
}

template<typename T>
RedBlackNode<T>* RedBlackTree<T>::findSuccessor(
	RedBlackNode<T>* current
) const {
	if (!current) return NULL;
	if (current->_right) {
		RedBlackNode<T>* node = current->_right;
		while(node && node->_left) {
			node = node->_left;
		}
		return node;
	}
	else {
		RedBlackNode<T>* node = current->_parent;
		while (node && node->_right == current) {
			current = node;
			node = current->_parent;
		}
		return node;
	}
}


template<typename T>
void RedBlackTree<T>::deleteColorFix(
	RedBlackNode<T>* parent, 
	RedBlackNode<T>* node
) {
	if (!parent) return;
	if (node && node->_color) {
		node->_color = false;
		return;
	}

	RedBlackNode<T>* sibling = NULL;
	if (parent->_left == node) {
		sibling = parent->_right;
   	if (sibling->_color) {
			parent->_color = true;
			sibling->_color = false;
			leftRotate(parent, sibling);
			deleteColorFix(parent, node);
   	}
   	else {
   		bool leftColor = (sibling->_left != NULL) && sibling->_left->_color;
   		bool rightColor = (sibling->_right != NULL) && sibling->_right->_color;
   		if (!leftColor && !rightColor) {
   			sibling->_color = true;
   			parent->_color = false;
   			deleteColorFix(parent->_parent, parent);
   		}	
   		else if (leftColor) {
				sibling->_color = true;
				sibling->_left->_color = false;
				rightRotate(sibling, sibling->_left);
				deleteColorFix(parent, node);
   		}
			else {
				sibling->_color = parent->_color;
				parent->_color = false;
				sibling->_right->_color = false;
				leftRotate(parent, sibling);
			}
   	}
	}
	else {
		sibling = parent->_left;
   	if (sibling->_color) {
			parent->_color = true;
			sibling->_color = false;
			rightRotate(parent, sibling);
			deleteColorFix(parent, node);
   	}
   	else {
   		bool leftColor = (sibling->_left != NULL) && sibling->_left->_color;
   		bool rightColor = (sibling->_right != NULL) && sibling->_right->_color;
   		if (!leftColor && !rightColor) {
   			sibling->_color = true;
   			parent->_color = false;
   			deleteColorFix(parent->_parent, parent);
   		}	
   		else if (leftColor) {
				sibling->_color = parent->_color;
				parent->_color = false;
				sibling->_left->_color = false;
				rightRotate(parent, sibling);
   		}
			else {
				sibling->_color = true;
				sibling->_right->_color = false;
				leftRotate(sibling, sibling->_right);
				deleteColorFix(parent, node);
			}
   	}
	}
	return;
}

template class RedBlackNode<int>;
template class RedBlackTree<int>;
