#include <cstdio>
#include <algorithm>
using namespace std;

struct node{
	node *l = nullptr , *r = nullptr;
	int lb , rb;
	int minH;
	long long sum;
	node(){}
	node(int _lb,int _rb){ lb=_lb , rb=_rb; }
};
char slope[1000004];
int h[1000004];
int cost[1000004];

long long cnt;
int queryMin(node *nd,int tl,int tr){
	++cnt;
	if( nd->lb == tl && nd->rb == tr ) return nd->minH;
	
	int mid = (nd->lb + nd->rb)/2;
	if( tr <= mid ) return queryMin(nd->l , tl,tr);
	if( tl >  mid ) return queryMin(nd->r , tl,tr);
	return min(
		queryMin(nd->l , tl,mid),
		queryMin(nd->r , mid+1,tr)
	);
}
long long querySum(node *nd,int tl,int tr){
	++cnt;
	if( nd->lb == tl && nd->rb == tr ) return nd->sum;
	
	int mid = (nd->lb + nd->rb)/2;
	if( tr <= mid ) return querySum(nd->l , tl,tr);
	if( tl >  mid ) return querySum(nd->r , tl,tr);
	return querySum(nd->l , tl,mid) + querySum(nd->r , mid+1,tr);
}

node mem[2400000] , *memtop;
node* build(int from,int to){
	++cnt;
	*memtop = node(from,to);
	node *now = memtop++;
	if( from==to ){
		now->minH = h[from];
		now->sum = 1LL * cost[from];
		return now;
	}
	int mid = (from+to)/2;
	now->l = build(from,mid);
	now->r = build(mid+1,to);
	now->minH = min( now->l->minH , now->r->minH );
	now->sum = now->l->sum + now->r->sum;
	return now;
}

int main () {
	int T;
	scanf("%d",&T);
	for(int NCASE=1 ; NCASE<=T ; ++NCASE){
		int M,N;
		scanf("%d%d%s",&N,&M,slope);
		int tmpMin = 0;
		h[0] = 0;
		for(int i=1 ; i<N ; ++i){
			h[i] = h[i-1];
			if( slope[i]=='\\' ) --h[i];
			if( slope[i-1]=='/' ) ++h[i];
			tmpMin = min(tmpMin , h[i]);
		}
		for(int i=0 ; i<N ; ++i)
			h[i] -= tmpMin;
		for(int i=0 ; i<N ; ++i){
			cost[i] = h[i]*2;
			if( slope[i]=='/' || slope[i]=='\\' ) cost[i] += 1;
		}
		/*
		for(int i=0 ; i<N ; ++i)
			printf("%3d ",h[i]);
		puts("");
		for(int i=0 ; i<N ; ++i)
			printf("%3d ",cost[i]);
		puts("");
		*/

		memtop = mem;
		cnt = 0LL;
		build(0 , N-1);
		//printf("%lld\n",cnt);

		long long minCost = 10000000000000000LL;
		for(int i=M-1 ; i<N ; ++i){
			//cnt = 0LL;
			long long nowCost = querySum(mem , i-(M-1) , i) - 2LL*M*queryMin(mem , i-(M-1) , i);
			if( nowCost < minCost )
				minCost = nowCost;
			//printf("%lld\n",cnt);
			//printf("%lld - %lld\n",querySum(mem , i-(M-1) , i) , 2LL*M*queryMin(mem , i-(M-1) , i));
		}
		printf("%lld\n",cnt);
		printf("Case #%d: %.1f\n",NCASE , 1.0*minCost/2.0);
	}
}