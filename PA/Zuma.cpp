#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define Pdict dict*
char str[10002];

struct dict{
	char value;
	int num;
	Pdict pred;
	Pdict succ;
	dict(){};
	dict(char va,Pdict p = NULL,Pdict s = NULL, int n = 1)
		:value(va),pred(p),succ(s),num(n) {}
	Pdict insertAsPred(char value){
		Pdict x = new dict(value, pred, this);
		pred->succ = x; pred = x;
		return x;
	}
	Pdict insertAsSucc(char value){
		Pdict x = new dict(value, this,succ);
		succ->pred = x; succ = x;
		return x;
	}
};

class List{
	Pdict header; Pdict trailer;int _size = 0;
protected:
	void init(char *str,int n){
		header = new dict(); trailer = new dict();
		header->succ = trailer; header->pred = NULL;
		trailer->succ = NULL; trailer->pred = header;
		int dir;
		Pdict Cur;
		for(int i=0; i<n; i++){
			if(i == 0)   {
				Cur = header->insertAsSucc(str[0]);
		}
			else if(str[i] == str[i-1]) {
				Cur->num += 1;
			}else {
				Cur = Cur->insertAsSucc(str[i]);
			}
			_size++;
		}
	}
	char remove(Pdict p){
		char temp = p->value;
		p->pred->succ = p->succ; p->succ->pred = p->pred;
		_size -= p->num;
		delete p;
		return temp;
	}
	void clear() {
		Pdict p = header;
		while(p->succ) {
			remove(p->succ);
		}
	}

public:
	List(char*str,int n) {init(str,n);}
	~List(){
		clear();
		delete header; delete trailer;
	}
	int size(){
		return _size;
	}
	void printAlpha(){
		Pdict p = header;
		int i;
		while (p = p->succ) {
			for(i=0; i<p->num;i++)
				printf("%c",p->value);
		}printf("\n");
	}
	void printnum() {
		Pdict p = header;
		while (p = p->succ) {
			printf("%2d", p->num);
		}printf("\n");
	}
	bool duplicate(int n,char nvalue) {
		int seq = 0; bool flag = 0;
		Pdict q = header;
		if (_size == 0) {
			header->insertAsSucc(nvalue);
			_size++;
			return _size;
		}
		while(q = q->succ){
			if( seq<=n && n <= (seq += q->num)){
				if(nvalue == q->value || ((nvalue == q->succ->value)? flag = 1:flag =0)){
					if(flag)    q = q->succ;
					if(q->num == 2 ) {
						int i = 0;
						Pdict le = q;
						Pdict ri = q;
						while ((le = le->pred)->value == (ri = ri->succ)->value && (le->num + ri->num >= 3))
							i++;
						for (int j = 0; j < i; j++) {
							remove(le->succ);
							remove(ri->pred);
						}
						remove(q);
						return _size;
					}else {
						q->num++; _size++;  return _size;
					}
				}// 不是相同值
				else {
					if (n == seq) q->insertAsSucc(nvalue);
					else if (n == seq - (q->num)) q->insertAsPred(nvalue);
					else {
						Pdict q2 = new dict(q->value, q->pred, q->succ);
						q2->pred = q;
						q->succ->pred = q2;
						q->succ = q2;
						q->num = 1;
						q->insertAsPred(nvalue);
					}
					_size++;
					return _size;
				}
				}
			}
		}
};

int main() {
	int n,seq;
	char solo;
	scanf("%s",str);
	n = strlen(str);
	List list(str, n);
	scanf("%d",&n);
	for(int i = 0; i<n; i++){
		scanf("%d %c",&seq,&solo);
		if(list.duplicate(seq,solo)) list.printAlpha();
		else    printf(" -\n");
	}

	return 0;
}

