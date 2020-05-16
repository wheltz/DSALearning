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


#endif //DSA_LEARNING_VSTACK_H
