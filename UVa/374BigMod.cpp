#include<cstdio>
using namespace std;
int B,P,M;
int recursive(int);
int main(){
	while(scanf(" %d%d%d",&B,&P,&M)!=EOF){
		B=B%M;
		printf("%d\n",recursive(P)%M);
	}
}
int recursive(int po){
	if(po==0) return 1;
	if(po==1) return B;
	unsigned int temp = recursive(po/2)%M;
	temp=(temp*temp)%M;
	if(po%2==1) temp=(temp*B)%M;
	return temp;
}
