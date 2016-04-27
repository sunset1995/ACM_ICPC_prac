#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int now,c1,c2,c3;
	while( scanf(" %d%d%d%d",&now,&c1,&c2,&c3)!=EOF ){
		if( now==0 && c1==0 && c2==0 && c3==0 ) break;
		int count = 80-now;
		if( c1>=30 ) count += 40;
		else count += c1*2;
		count += 40-c2;
		if(c3>=c2) count += c3-c2;
		else count += 40-c2+c3;
		printf("%d\n",count*9);
	}
}
