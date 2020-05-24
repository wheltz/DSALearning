//
// Created by zhichao on 2020/4/15.
//

#ifndef DSA_LEARNING_LQUEUE_H
#define DSA_LEARNING_LQUEUE_H

#include"List.h"
#include<iostream>

template<typename T>
class Queue : public List<T> {//size,empty以及其他开放接口沿用List
public:
	void enqueue(T const &e);

	T dequeue();

	T &front();
};

template<typename T>
T Queue<T>::dequeue() { return this->remove(this->first()); }

template<typename T>
T &Queue<T>::front() { return this->first->data; }

template<typename T>
void Queue<T>::enqueue(T const &e) { this->insertAsLast(e); }

#endif //DSA_LEARNING_LQUEUE_H
