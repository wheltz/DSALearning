//
// Created by zhichao on 2020/4/19.
//
#include<iostream>
#include"vStack.h"


#define N_OPTR 9 //运算符总数
typedef enum {
	ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator;
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = {  //运算符优先等级 [栈顶][当前]
		/*            |------当前运算符--------------------------------|  */
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

Operator optr2rank(char op){ //有运算符编译出符号
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

void append( char*& rpn,float opn){ //将操作数接至RPN末尾
	int n = strlen(rpn);
	char buf[64];
	if (opnd != (float)(int)opnd) sprintf(buf,"%.2f \0",opnd); //浮点数格式
	else sprintf(buf,"%d \0");  //整数格式
	rpn = (char*) realloc(rpn,sizeof(char)*(n+strlen(buf)+1)); //realloc重新扩展空间
	strcat(rpn,buf);  //RPN加长
}

void append(char*& rpn,char optr){  //将操作符接至RPN末尾
	int n = strlen(rpn);
	rpn = (char*)realloc(rpn,sizeof(char)*(n+3));  //扩展空间
	sprintf(rpn+n,"%c ",optr); rpn[n+2] = '\0'; 接入指定的运算符
}
//求值算法
float evaluate(char* S,char* & RPN) {       //对（已剔除空白的）表达式求值，并转换为逆波兰式RPN
	Stack<float> opnd; Stack<char> optr;  //运算数栈，运算符栈
	optr.push('\0'); //尾哨兵'\0'作为头哨兵首先入栈
	while( !optr.empty()){
		if(isdigit(*S)){
			readNumber(S,opnd); append(RPN,opnd.top());//读入操作数，并将其接入RPN末尾
		}else //若当前字符为运算符,则
			switch(orderBetween(optr.top(),*S)){
			case '<':
				optr.push(*S); S++;
				break;
			case'=':        //当优先级相等时(当前运算符为右括号时或者尾部哨兵'\0'）
				optr.pop();S++; //脱括号，或者移除'\0'
				break;
			case'>':{       //当栈顶运算符优先级更高时，进行相应运算
				char op = optr.pop(); append(RPN,op);   //栈顶运算符出栈并续接至RPN末尾
				if( '!' == op ){
					float pOpnd = opnd.pop();     //只需取出一个操作数，并
					opnd.push(calcu(op,pOpnd));  //实施一元运算，结果入栈
				}else {
					float pOpnd2 = opnd.pop();  pOpnd1 = opnd.pop();
					opnd.push(calcu(pOpnd1,op,pOpnd2));
				}break;
			}
			defalut:exit(-1);   //遇到语法错误，不做处理直接退出
		}
	}
	return opnd.pop();  //弹出并返回最后的计算结果
}


