#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
int main(){
	int *happy , *stack , top;
	happy = new int[100000];
	stack = new int[50000];
	memset(happy,-1,sizeof(int[100000]));
	happy[1] = 1;
	for(int i=2;i<=6;++i) happy[i] = 0;
	for(int i=7;i<=99999;++i){
		if( happy[i]>=0 ) continue;
		happy[i] = 0;
		top = -1;
		int now = i;
		do{
			stack[++top] = now;
			int next = 0;
			while(now!=0){
				int per = now%10;
				next +=  per*per;
				now/=10;
			}
			now = next;
		}while( happy[now]==-1 );
		if( happy[now]==0 )
			for(int r=0;r<=top;++r) happy[ stack[r] ] = 0;
		else
			for(int r=top,j=1;r>=0;--r,++j) happy[ stack[r] ] = happy[now]+j;
	}
	int l,h;
	bool first = true;
	while( scanf(" %d%d",&l,&h)!=EOF && l ){
		if( !first ) printf("\n");
		else first = false;
		while(l<=h){
			if( happy[l]>0 ) printf("%d %d\n",l,happy[l]);
			++l;
		}
	}
	delete [] happy;
	delete [] stack;
} 
