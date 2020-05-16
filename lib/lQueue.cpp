//
// Created by zhichao on 2020/4/15.
//

#include "lQueue.h"
#include<iostream>
using namespace std;


template<typename T>
T Queue<T>::dequeue() {return remove(this->first());}

template<typename T>
T & Queue<T>::front() {return this->first->data;}

template<typename T> void Queue<T>::enqueue (T const &e) { insertAsLast(e); }
