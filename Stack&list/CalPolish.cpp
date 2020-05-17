//
// Created by zhichao on 2020/4/19.
//
#include<iostream>
#include"vStack.h"


#define N_OPTR 9 //���������
typedef enum {
	ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator;
//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char pri[N_OPTR][N_OPTR] = {  //��������ȵȼ� [ջ��][��ǰ]
		/*            |------��ǰ�����--------------------------------|  */
		/*              +     -     *   /    ^    !    (    )   \0              */
		/*--   + */     '>', '>', '<', '<', '<', '<', '<', '>', '>',
		/*--   - */     '>', '>', '<', '<', '<', '<', '<', '>', '>',
		/*--   * */     '>', '>', '>', '>', '<', '<', '<', '>', '>',
		/*--   / */     '>', '>', '>', '>', '<', '<', '<', '>', '>',
		/*--   ^ */     '>', '>', '>', '>', '>', '<', '<', '>', '>',
		/*--   ! */     '>', '>', '>', '>', '>', '>', ' ', '>', '>',
		/*--   ( */     '<', '<', '<', '<', '<', '<', '<', '=', ' ',
		/*--   ) */     ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		/*--  \0 */     '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

void readNumber(char* &p,Stack<float>& stk){
	stk.push((float)(*p - '\0'));
	while( isdigit( *(++p)))
		stk.push(stk.pop()*10 + (*p - '0'));
	if('.' != *p) return;
	float fraction = 1;
	while(isdigit( *(++p)))
		stk.push(stk.pop() + (*p - '\0')*fraction/10);
}

Operator optr2rank(char op){ //����������������
	switch(op) {
		case '+': return ADD;
		case '-': return SUB;
		case '*': return MUL;
		case '/': return DIV;
		case '^': return POW;
		case '!': return FAC;
		case '(': return L_P;
		case ')': return R_P;
		case '\0':return EOE;
		defalult :exit(-1);
	}
}

char orderBetween(char op1,char op2){
	return pri[optr2rank(op1)][optr2rank(opo2)];
}

void append( char*& rpn,float opn){ //������������RPNĩβ
	int n = strlen(rpn);
	char buf[64];
	if (opnd != (float)(int)opnd) sprintf(buf,"%.2f \0",opnd); //��������ʽ
	else sprintf(buf,"%d \0");  //������ʽ
	rpn = (char*) realloc(rpn,sizeof(char)*(n+strlen(buf)+1)); //realloc������չ�ռ�
	strcat(rpn,buf);  //RPN�ӳ�
}

void append(char*& rpn,char optr){  //������������RPNĩβ
	int n = strlen(rpn);
	rpn = (char*)realloc(rpn,sizeof(char)*(n+3));  //��չ�ռ�
	sprintf(rpn+n,"%c ",optr); rpn[n+2] = '\0'; ����ָ���������
}
//��ֵ�㷨
float evaluate(char* S,char* & RPN) {       //�ԣ����޳��հ׵ģ����ʽ��ֵ����ת��Ϊ�沨��ʽRPN
	Stack<float> opnd; Stack<char> optr;  //������ջ�������ջ
	optr.push('\0'); //β�ڱ�'\0'��Ϊͷ�ڱ�������ջ
	while( !optr.empty()){
		if(isdigit(*S)){
			readNumber(S,opnd); append(RPN,opnd.top());//��������������������RPNĩβ
		}else //����ǰ�ַ�Ϊ�����,��
			switch(orderBetween(optr.top(),*S)){
			case '<':
				optr.push(*S); S++;
				break;
			case'=':        //�����ȼ����ʱ(��ǰ�����Ϊ������ʱ����β���ڱ�'\0'��
				optr.pop();S++; //�����ţ������Ƴ�'\0'
				break;
			case'>':{       //��ջ����������ȼ�����ʱ��������Ӧ����
				char op = optr.pop(); append(RPN,op);   //ջ���������ջ��������RPNĩβ
				if( '!' == op ){
					float pOpnd = opnd.pop();     //ֻ��ȡ��һ������������
					opnd.push(calcu(op,pOpnd));  //ʵʩһԪ���㣬�����ջ
				}else {
					float pOpnd2 = opnd.pop();  pOpnd1 = opnd.pop();
					opnd.push(calcu(pOpnd1,op,pOpnd2));
				}break;
			}
			defalut:exit(-1);   //�����﷨���󣬲�������ֱ���˳�
		}
	}
	return opnd.pop();  //�������������ļ�����
}


