#include <cstdio>
#include <cstring>
using namespace std;

char str[1004];
int P[1004];
int S[1004];
int R[1004];

int query(int *a,int from,int to){
	if( to<from ) return 0;
	if( from==0 ) return a[to];
	return a[to] - a[from-1];
}

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int N;
		scanf(" %d%s",&N,str);
		memset(P , 0 , sizeof(P));
		memset(S , 0 , sizeof(S));
		memset(R , 0 , sizeof(R));
		for(int i=0 ; i<N ; ++i){
			P[i+1] = P[i];
			S[i+1] = S[i];
			R[i+1] = R[i];
			if( str[i]=='R' )
				++P[i+1] , --S[i+1];
			else if( str[i]=='S' )
				++R[i+1] , --P[i+1];
			else
				++S[i+1] , --R[i+1];
		}
		P[N+1] = P[N];
		R[N+1] = R[N];
		S[N+1] = S[N];
		int cnt = 0;
		for(int i=0;i<=N;++i)
			for(int j=i;j<=N;++j)
				if( query(R,0,i) + query(P,i+1,j) + query(S,j+1,N+1) > 0 )
					++cnt;
		printf("%d\n",cnt);
	}
}