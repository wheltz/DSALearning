//
// Created by zhichao on 2020/3/30.
//
#include"vStack.h"
template<typename T>
void Stack<T>::push(const T &e) {
	insert(this->size(), e);   //入栈等效于新元素作为向量的末元素入栈
}

template<typename T>
T Stack<T>::pop() {
	return remove(this->size() - 1); //出栈等效于删除向量的末元素
}

template<typename T>
T &Stack<T>::top() {
	return (*this)[this->size() - 1];  //取顶：直接返回末元素
}



