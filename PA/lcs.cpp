#include <stdio.h>
#include<cstring>

using namespace std;

void printTable(int* ta,int length,int width) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			printf("%3d", *(ta+length*i+j));
		}
		printf("\n");
	}
}

int MaxLCS(char* str1,char* str2,int n,int m){
	int table[n][m];
	char ichar;
	for(int i=0; i < n; i++) {
		ichar = str1[i];
		for(int j = 0; j < m; j++) {
			table[i][j] = i? table[i-1][j] : 0;
			if(ichar == str2[j]){
				table[i][j] += 1;
				for(int p = j+1 ; p < m ; p++) {
					table[i][p] = table[i][p - 1];
				}
				break;
			}
		}
	}
	printTable((int*)table,n,m);
	return  table[n][m];
}

int main(){
	printf("lcs = %d",MaxLCS("advantage","didactical",strlen("advantage"),strlen("didactical")));
	return 0;
};

