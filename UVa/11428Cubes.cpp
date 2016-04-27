#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int N;
	while( scanf(" %d",&N)!=EOF && N ){
		int until = sqrt(N)+1 , x=-1 , y=-1;
		for(int i=until;i>0;--i){
			if( N%i!=0 ) continue;
			int A=N/i , B=i;
			if( (4*A-B*B)%3!=0 ) continue;
			int tmp1 = (4*A-B*B)/3;
			int tmp2 = sqrt( tmp1 );
			if( tmp2*tmp2!=tmp1 ) continue;
			tmp2 -= B;
			if( tmp2<0 || tmp2%2!=0 ) continue;
			y = tmp2 /2;
			x = B+y;
			break;
		}
		if( y==-1 )
			printf("No solution\n");
		else
			printf("%d %d\n",x,y);
	}
}
