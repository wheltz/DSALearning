//
// Created by zhichao on 2020/5/24.
//

#include"lQueue.h"

struct Custormer { //�˿��࣬�������ڡ�����ʱ��
	int window;
	unsigned int time;
};

int bestWindow(Queue<Custormer> *, int);

void simulate(int nWin, int servTime) { //��ָ����������������ʱ��ģ������ҵ��
	Queue<Custormer> *windows = new Queue<Custormer>[nWin]; //Ϊÿһ�����ڴ���һ������
	for (int now = 0; now < servTime; now++) {  //���°�֮ǰ��ÿ��һ����λʱ��
		if (rand() % (1 + nWin)) {//�¹˿���nWin/nWin+1�ĸ��ʵ���
			Custormer c;
			c.time = 1 + rand() % 98; //�¹˿͵������ʱ�����
			c.window = bestWindow(windows, nWin);//�ҳ���ѵķ��񴰿�
			windows[c.window].enqueue(c); //�¹˿ͼ����Ӧ�Ķ���
		}
		for (int i = 0; i < nWin; i++) { //�ֱ���
			if (!windows[i].empty()) //���ǿն���
				if (--windows[i].front().time <= 0) //���׹˿͵ķ���ʱ������һ����λ
					windows[i].dequeue(); //������ϵĹ˿ͳ��У��ɺ�̹˿ͽ���
		}
	}   //for
	delete[] windows;  //�ͷ����ж���(��ǰ��~List���Զ���ն���)
}

int bestWindow(Queue<Custormer> windows[], int nWin) {
	int minSize = windows[0].size(), optWin = 0; //���Ŷ���(����)
	for (int i = 1; i < nWin; i++) {
		if (minSize > windows[i].size()) {
			minSize = windows[i].size();
			optWin = i;
		}
	}
	return optWin;
}