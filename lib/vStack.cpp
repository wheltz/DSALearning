//
// Created by zhichao on 2020/3/30.
//
#include"vStack.h"
template<typename T>
void Stack<T>::push(const T &e) {
	insert(this->size(), e);   //��ջ��Ч����Ԫ����Ϊ������ĩԪ����ջ
}

template<typename T>
T Stack<T>::pop() {
	return remove(this->size() - 1); //��ջ��Ч��ɾ��������ĩԪ��
}

template<typename T>
T &Stack<T>::top() {
	return (*this)[this->size() - 1];  //ȡ����ֱ�ӷ���ĩԪ��
}



