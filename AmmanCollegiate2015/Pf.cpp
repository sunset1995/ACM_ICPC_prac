#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct path{
	int to , c;
};
bool inQ[100004];
int cost[100004];
vector<path> g[100004];

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int N,M;
		scanf(" %d%d",&N,&M);
		for(int i=0;i<=N;++i)
			inQ[i] = false;
		for(int i=0;i<=N;++i)
			cost[i] = 1e6;
		for(int i=0;i<=N;++i)
			g[i].clear();
		for(int i=0,x,y,c;i<M;++i){
			scanf(" %d%d%d",&x,&y,&c);
			g[x].push_back( (path){y,c} );
			g[y].push_back( (path){x,c} );
		}
		queue<int> myQ;
		cost[1] = 0;
		myQ.push( 1 );
		while( !myQ.empty() ){
			int nowAt = myQ.front();
			myQ.pop();
			inQ[nowAt] = false;
			for(int i=0;i<g[nowAt].size();++i)
				if( cost[ g[nowAt][i].to ] > max( cost[nowAt] , g[nowAt][i].c ) ){
					cost[ g[nowAt][i].to ] = max( cost[nowAt] , g[nowAt][i].c );
					if( !inQ[ g[nowAt][i].to ] )
						myQ.push( g[nowAt][i].to );
				}
		}
		int ans = 0;
		for(int i=1;i<=N;++i)
			ans = max(ans , cost[i]);
		printf("%d\n",ans);
	}
}