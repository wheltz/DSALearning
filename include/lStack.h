//
// Created by zhichao on 2020/4/15.
//

#ifndef DSA_LEARNING_LSTACK_H
#define DSA_LEARNING_LSTACK_H

#include<iostream>
#include"List.h"  //这里选择以列表为模板，派生栈模板类

using namespace std;

template<typename T>
class Stack : public List<T> {//size,empty以及其他开放接口沿用List
public:
	void push(T const &e);

	T pop();

	T &top();
};


#endif //DSA_LEARNING_LSTACK_H
