//
// Created by zhichao on 2020/5/24.
//

#include<iostream>
#include<lStack.h>

typedef enum {
	AVAILABLE, ROUTE, BACKTRACKD, WALL
} Status; //�Թ���Ԫ״̬
// ԭʼ���õġ� �ڵ�ǰ·���ϵġ����з��������ʧ�ܺ���ݹ��ġ�����ʹ�õ�

typedef enum {
	UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY
} ESWN;//��Ԫ������ڽӷ�ʽ
//δ���������ϡ�����������·��ͨ

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }  //����ת����һ�ڽӷ�ʽ

struct Cell {  //�Թ������
	int x, y;
	Status status; //x���꣬y���꣬����
	ESWN incoming, outgoing; //���롢�߳�����
};

#define LABY_MAX 24     //����Թ��ߴ�
Cell laby[LABY_MAX][LABY_MAX];      //�Թ�

inline Cell *neighbor(Cell *cell) {  //��ѯ��ǰλ�õ����ڸ��
	switch (cell->outgoing) {
		case EAST:
			return cell + LABY_MAX;
		case SOUTH:
			return cell + 1;
		case WEST:
			return cell - LABY_MAX;
		case NORTH:
			return cell - 1;
		default:
			exit(-1);
	}
}

inline Cell *advance(Cell *cell) {  //�ɵ�ǰλ��ת�����ڸ��
	Cell *next;
	switch (cell->outgoing) {
		case EAST:
			next = cell + LABY_MAX;
			next->incoming = WEST;
			break;  //��
		case SOUTH:
			next = cell + 1;
			next->incoming = NORTH;
			break; //����
		case WEST:
			next = cell - LABY_MAX;
			next->incoming = EAST;
			break; //����
		case NORTH:
			next = cell - 1;
			next->incoming = SOUTH;
			break; //��
		default:
			exit(-1);
	}
	return next;
}



//��̽���ݲ����㷨ʵ�����£�

//�Թ�Ѱ���㷨���ڸ�Ԫs��t֮��滮һ��ͨ·��������ڣ�
bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell *s, Cell *t) {
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false;  //�˻����
	Stack<Cell *> path; //��ջ��¼��·(Theseus��������
	s->incoming = UNKNOWN;
	s->status = ROUTE;
	path.push(s);  //���
	do {
		Cell *c = path.top();  //��鵱ǰλ��(ջ��)
		if (c == t) return true; //���ѵִ��յ㣬���ҵ���һ��ͨ·����������δ��̽�ķ��������̽
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) //ע�������еķ���
			if (AVAILABLE == neighbor(c)->status) break;  //��ͼ�ҵ���δ��̽�ķ���
		if (NO_WAY <= c->outgoing)  //�����з����ѳ��Թ�
		{
			c->status = BACKTRACKD;
			c = path.pop();
		} else {
			path.push(c = advance(c));
			c->outgoing = UNKNOWN;
			c->status = ROUTE;
		}
	} while (!path.empty());
	return false;
}