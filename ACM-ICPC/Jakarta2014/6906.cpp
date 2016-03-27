#include <cstdio>
#include <algorithm>
using namespace std;

int A[104];

int main(){
	int T;
	scanf("%d",&T);
	for(int NCASE = 1 ; NCASE<=T ; ++NCASE){
		int N , K;
		scanf("%d%d",&N,&K);
		for(int i=0 ; i<N ; ++i)
			scanf("%d",&A[i]);
		sort( A , &A[N] );
		int ans = 1;
		for(int i=1 ; i<N ; ++i)
			if( A[i]-A[i-1] > K ) ++ans;
		printf("Case #%d: %d\n",NCASE , ans);
	}
	return 0;
}