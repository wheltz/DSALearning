//
// Created by zhichao on 2020/4/19.
//

#include<iostream>
#include"vStack.h"

struct Queen{
	int x,y;  //�ʺ��������ϵ�λ������
	Queen (int xx=0,int yy=0): x(xx),y(yy){};
	bool operator== (Queen const& q) const{ //�����еȲ��������Լ�ⲻͬ�ʺ�֮����ܷ����ĳ�ͻ
		return (x == q.x)   //�г�ͻ����һ���ʵ���ϲ����ᷢ������ʡ�ԣ�
				|| (y == q.y) //�г�ͻ
				|| (x+y == q.x + q.y) //�����Խ��߳�ͻ�����½���ԭ��
				|| (x - y == q.x - q.y); //�ط��Խ��߳�ͻ
	}
	bool operator!= (Queen const& q) const{
		return !(*this == q);
	}
};

//������̽���ݲ��ԣ���ʵ��ͨ�õ�N�ʺ��㷨

void placeQueens(int N){  //N�ʺ��㷨�������棩��������̽
	Stack<Queen> solu;  //��ţ����֣����ջ
	Queen q(0,0);  //��ԭ�����
	do { //������̽������
		if( N <= solu.size() || N <= q.y){
			q = solu.pop(); q.y++;
		}else {
			while ((q.y < N) && (0 <= solu.find(q)))      //�����find �õ���֮ǰ���ص�==�ͣ�=
			{q.y++; nCheck++;} //�����ҵ��ɰڷ���һ�ʺ����
			if (N > q.y) {
				solu.push(q);
				if (N <= solu.size()) nSolu++;  //�����ֽ��Գ�Ϊȫ�ֽ⣬��ͨ��ȫ�ֱ���nSolu++����
				q.x++; q.y = 0; //ת����һ�У��ӵ�0�п�ʼ����̽��һ�ʺ�
			}
		}
	}while( ( 0 < q.x) || ( q.y < N));  //���з�֧���ѻ���ٻ��֦�Ժ��㷨����
}