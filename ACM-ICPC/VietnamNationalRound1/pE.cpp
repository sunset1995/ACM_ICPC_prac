#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ans;
int L[100004] , R[100004] , K[100004];
int vL[100004] , vR[100004];

int dfs_a(int,int);
int dfs_b(int,int);
void find_ans(int);

void dfs(int id){
	find_ans(id);
	if( L[id] ) find_ans(L[id]);
	if( R[id] ) find_ans(R[id]);
}
void find_ans(int id){
	int x = dfs_a(L[id] , K[id]);
	int y = dfs_b(R[id] , K[id]);
	ans = max(ans , x+y+1);
}
int dfs_a(int id,int k){
	if( !id ) return 0;
	if( vL[id]==-1 )
		vL[id] = dfs_a(L[id] , K[L[id]]);
	int tmp = 0;
	if( R[id] && K[R[id]] < k )
		tmp = dfs_a(R[id] , k);
	return vL[id] + tmp + 1;
}
int dfs_b(int id,int k){
	if( !id ) return 0;
	if( vR[id]==-1 )
		vR[id] = dfs_b(R[id] , K[R[id]]);
	int tmp = 0;
	if( L[id] && K[L[id]] > k )
		tmp = dfs_b(L[id] , k);
	return vR[id] + tmp + 1;
}

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		int N;
		scanf("%d",&N);
		for(int i=1 ; i<=N ; ++i)
			scanf("%d%d%d",&L[i],&R[i],&K[i]);
		for(int i=1 ; i<=N ; ++i){
			if( K[L[i]] >= K[i] ) L[i] = 0;
			if( K[R[i]] <= K[i] ) R[i] = 0;
		}
		memset(vL , -1 , sizeof(vL));
		memset(vR , -1 , sizeof(vR));
		ans = 1;
		dfs(1);
		//for(int i=1 ; i<=N ; ++i)
		//	printf("%d L%d R%d\n",K[i],vL[i],vR[i]);
		printf("%d\n",ans);
	}
	return 0;
}
