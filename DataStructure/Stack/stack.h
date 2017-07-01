#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack {

	public:
		Stack();
		~Stack();

		void set_size(size_t);
		void push(T);
		T pop();

		T* _data;
		size_t _size, _current;
};

#endif
