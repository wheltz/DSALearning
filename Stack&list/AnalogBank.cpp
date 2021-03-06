//
// Created by zhichao on 2020/5/24.
//

#include"lQueue.h"

struct Custormer { //顾客类，所属窗口、服务时长
	int window;
	unsigned int time;
};

int bestWindow(Queue<Custormer> *, int);

void simulate(int nWin, int servTime) { //按指定窗口数，服务总时间模拟银行业务
	Queue<Custormer> *windows = new Queue<Custormer>[nWin]; //为每一个窗口创建一个队列
	for (int now = 0; now < servTime; now++) {  //在下班之前，每隔一个单位时间
		if (rand() % (1 + nWin)) {//新顾客以nWin/nWin+1的概率到达
			Custormer c;
			c.time = 1 + rand() % 98; //新顾客到达，服务时长随机
			c.window = bestWindow(windows, nWin);//找出最佳的服务窗口
			windows[c.window].enqueue(c); //新顾客加入对应的队列
		}
		for (int i = 0; i < nWin; i++) { //分别检查
			if (!windows[i].empty()) //各非空队列
				if (--windows[i].front().time <= 0) //队首顾客的服务时长减少一个单位
					windows[i].dequeue(); //服务完毕的顾客出列，由后继顾客接替
		}
	}   //for
	delete[] windows;  //释放所有队列(此前，~List会自动清空队列)
}

int bestWindow(Queue<Custormer> windows[], int nWin) {
	int minSize = windows[0].size(), optWin = 0; //最优队列(窗口)
	for (int i = 1; i < nWin; i++) {
		if (minSize > windows[i].size()) {
			minSize = windows[i].size();
			optWin = i;
		}
	}
	return optWin;
}