//
// Created by zhichao on 2020/4/15.
//

#ifndef DSA_LEARNING_VSTACK_H
#define DSA_LEARNING_VSTACK_H

#include<iostream>
#include<cstdio>
#include"Vector.h"  //这里选择以向量为模板，派生栈模板类

using namespace std;

template<typename T>
class Stack : public Vector<T> {
public:
	void push(T const &e);

	T pop();

	T &top();
};

template<typename T>
void Stack<T>::push(const T &e) {
	this->insert(this->size(), e);   //入栈等效于新元素作为向量的末元素入栈
}

template<typename T>
T Stack<T>::pop() {
	return this->remove(this->size() - 1); //出栈等效于删除向量的末元素
}

template<typename T>
T &Stack<T>::top() {
	return (*this)[this->size() - 1];  //取顶：直接返回末元素
}

#endif //DSA_LEARNING_VSTACK_H
