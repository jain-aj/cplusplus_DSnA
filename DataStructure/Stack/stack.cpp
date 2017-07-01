#include <cstdlib>
#include "stack.h"
using namespace std;

template<typename T>
Stack<T>::Stack() {
	_data = NULL;
	_current = _size = 0;
}

template<typename T>
Stack<T>::~Stack() {
	free(_data);
}

template<typename T>
void Stack<T>::set_size(size_t size) {
	_size = size;
	_current = 0;
	_data = (T*) malloc(sizeof(T) * size);
}

template<typename T>
void Stack<T>::push(T t) {
	if (_current < _size) {
		_data[_current] = t;
		_current++;
	}
}

template<typename T>
T Stack<T>::pop() {
	T t;
	if (_current > 0) {
		_current--;
		t = _data[_current];
	}
	return t;
}

template class Stack<int>;
