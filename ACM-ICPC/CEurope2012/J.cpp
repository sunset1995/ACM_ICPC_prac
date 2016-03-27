#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

vector<int> g[100004];
int inN1[100004] , inN2[100004];
int fac[100004];

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		for(int i=0 ; i<100004 ; ++i){
			inN1[i] = inN2[i] = 0;
			g[i].clear();
		}
		int n , m;
		scanf("%d%d",&n,&m);
		for(int i=1 ; i<=n ; ++i)
			scanf("%d",&fac[i]);
		for(int i=0,u,v ; i<m ; ++i){
			scanf("%d%d",&u,&v);
			g[u].push_back(v);
			++inN1[v] , ++inN2[v];
		}
		int ans1 = -1 , ans2 = -1;
		queue<int> q1 , q2;

		// 1
		for(int i=1 ; i<=n ; ++i)
			if( inN1[i]==0 ){
				if( fac[i]==1 ) q1.push(i);
				else q2.push(i);
			}
		while( q1.size() || q2.size() ){
			++ans1;
			if( q1.size() ){
				while( q1.size() ){
					int nowAt = q1.front();
					//printf("%d ",nowAt);
					q1.pop();
					for(auto &v : g[nowAt])
						if( --inN1[v] == 0 ){
							if( fac[v]==1 ) q1.push(v);
							else q2.push(v);
						}
				}
			}
			else{
				while( q2.size() ){
					int nowAt = q2.front();
					//printf("%d ",nowAt);
					q2.pop();
					for(auto &v : g[nowAt])
						if( --inN1[v] == 0 ){
							if( fac[v]==1 ) q1.push(v);
							else q2.push(v);
						}
				}
			}
		}
		//puts("");

		// 2
		for(int i=1 ; i<=n ; ++i)
			if( inN2[i]==0 ){
				if( fac[i]==1 ) q1.push(i);
				else q2.push(i);
			}
		while( q1.size() || q2.size() ){
			++ans2;
			if( q2.size() ){
				while( q2.size() ){
					int nowAt = q2.front();
					//printf("%d ",nowAt);
					q2.pop();
					for(auto &v : g[nowAt])
						if( --inN2[v] == 0 ){
							if( fac[v]==1 ) q1.push(v);
							else q2.push(v);
						}
				}
			}
			else{
				while( q1.size() ){
					int nowAt = q1.front();
					//printf("%d ",nowAt);
					q1.pop();
					for(auto &v : g[nowAt])
						if( --inN2[v] == 0 ){
							if( fac[v]==1 ) q1.push(v);
							else q2.push(v);
						}
				}
			}
		}
		//puts("");
		printf("%d\n",min(ans1,ans2) );
	}
}