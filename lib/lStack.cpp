//
// Created by zhichao on 2020/3/30.
//
#include"lStack.h"

template<typename T>
void Stack<T>::push(const T &e) {
	insertAsLast(e);
}

template<typename T>
T Stack<T>::pop() {
	return remove(this->last());
}

template<typename T>
T &Stack<T>::top() {
	return this->last()->data;
}