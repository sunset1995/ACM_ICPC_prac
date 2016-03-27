#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char has[10000004];

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		memset(has , 0 , sizeof(has));
		int N,K,S,C1,C2,M;
		scanf("%d%d%d%d%d%d",&N,&K,&S,&C1,&C2,&M);
		long long now = S%M;
		for(int i=1 ; i<=N ; ++i){
			if( has[now]<100 )
				++has[now];
			now = (now*C1 % M + 1LL*C2) % M;
		}
		int id = 0;
		for(int i=0 ; i<K ; ++i){
			while( id<=10000000 && has[id]==0 )
				++id;
			printf("%d ",id);
			--has[id];
		}
		puts("");
	}
	return 0;
}
