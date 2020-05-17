//
// Created by zhichao on 2020/4/19.
//

#include<iostream>
#include"vStack.h"

struct Queen{
	int x,y;  //皇后在棋盘上的位置坐标
	Queen (int xx=0,int yy=0): x(xx),y(yy){};
	bool operator== (Queen const& q) const{ //重载判等操作符，以检测不同皇后之间可能发生的冲突
		return (x == q.x)   //行冲突（这一情况实际上并不会发生，可省略）
				|| (y == q.y) //行冲突
				|| (x+y == q.x + q.y) //沿主对角线冲突，左下角是原点
				|| (x - y == q.x - q.y); //沿反对角线冲突
	}
	bool operator!= (Queen const& q) const{
		return !(*this == q);
	}
};

//基于试探回溯策略，可实现通用的N皇后算法

void placeQueens(int N){  //N皇后算法（迭代版）：采用试探
	Stack<Queen> solu;  //存放（部分）解的栈
	Queen q(0,0);  //从原点出发
	do { //反复试探，回溯
		if( N <= solu.size() || N <= q.y){
			q = solu.pop(); q.y++;
		}else {
			while ((q.y < N) && (0 <= solu.find(q)))      //这里的find 用到了之前重载的==和！=
			{q.y++; nCheck++;} //尝试找到可摆放下一皇后的列
			if (N > q.y) {
				solu.push(q);
				if (N <= solu.size()) nSolu++;  //当部分解以成为全局解，则通过全局变量nSolu++计数
				q.x++; q.y = 0; //转向下一行，从第0列开始，试探下一皇后
			}
		}
	}while( ( 0 < q.x) || ( q.y < N));  //所有分支均已或穷举或剪枝以后，算法结束
}