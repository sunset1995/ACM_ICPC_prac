#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;

char slope[1000004];
int h[1000004];
long long cost[1000004];

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
		for(int i=1 ; i<=N ; ++i){
			cost[i] = h[i-1]*2;
			if( slope[i-1]=='/' || slope[i-1]=='\\' ) cost[i] += 1;
			cost[i] += cost[i-1] ;
		}
		deque<long long> q , ind;
		long long minCost = 10000000000000000LL;
		for(int i=0 ; i<M-1 ; i++) {
			while(!q.empty() && h[i]<=q.back()) {
				q.pop_back();
				ind.pop_back();
			}
			q.push_back(h[i]);
			ind.push_back(i);
		}
		for(int i=M-1 ; i<N ; ++i){
			if(!ind.empty() && i-ind.front()+1 > M) {
				q.pop_front();
				ind.pop_front();
			}
			while(!q.empty() && h[i]<=q.back()) {
				q.pop_back();
				ind.pop_back();
			}
			q.push_back(h[i]);
			ind.push_back(i);
			long long nowCost = cost[i+1] - cost[i-M+1] - 2LL*M*q.front();
			if( nowCost < minCost )
				minCost = nowCost;
		}
		printf("Case #%d: %.1f\n",NCASE , 1.0*minCost/2.0);
	}
}
