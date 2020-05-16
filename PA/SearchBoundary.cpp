#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int BUF[1 << 20];

int compare(const void*a,const void*b){
	int* pa = (int*)a;
	int* pb = (int*)b;
	return (*pa) - (*pb);
}

int BinarySearch(int* buf,int n,int num){
	int mi;
	int lo = 0;
	if(n==0) {
		return 0;
	}
	while(lo<n){
		mi = (lo+n)/2;

		(num < buf[mi])? n=mi:lo = mi+1;

	}
	return  --lo;
}

int main(){

	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d",&BUF[i]);
	}
	qsort(BUF,n,sizeof(int),compare);
	int a,b,ans,ans2;
	for(int j=0; j<m; j++){
		scanf("%d%d",&a,&b);
		ans = BinarySearch(BUF, n, b);
		ans2 = BinarySearch(BUF, n, a);

		printf("%d\n",ans2>0 && BUF[ans2] == a?ans - ans2 + 1 :ans - ans2);
	}
	strstr("abcdde","dd");

}
