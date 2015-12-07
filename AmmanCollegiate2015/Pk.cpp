#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

int num[100004];

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int N,K;
		scanf(" %d%d",&N,&K);
		memset(num , 0 , sizeof(num));
		for(int i=0,val;i<N;++i){
			scanf(" %d",&val);
			++num[val];
		}
		int to = sqrt(K) + 1 , X = 1;
		bool findAns = false;
		for(int i=1;i<=to && !findAns;++i){
			if( num[i]==0 )
				continue;
			--num[i];
			if( K%i == 0 && num[K/i] > 0 )
				findAns = true , X = i;
		}
		if( findAns )
			printf("%d %d\n",X , K/X);
		else
			printf("-1\n");
	}
}