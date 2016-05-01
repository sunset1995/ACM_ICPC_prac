#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

typedef pair<int,int> pii;

class Dinic{
private:
	static const int maxN = 104;
	int cap [maxN][maxN];
	int pipe[maxN][maxN];
	vector<int> g[maxN];
	bool sside[maxN];

	int level[maxN];
	bool bfsLabeling(int s, int t){
		memset(level , 0 , sizeof(level));
		queue<int> myQ;
		myQ.push( s );
		level[s] = 1;
		while( !myQ.empty() ){
			int nowAt = myQ.front();
			myQ.pop();
			for(int i=0;i<g[nowAt].size();++i)
				if( !level[g[nowAt][i]] && pipe[nowAt][g[nowAt][i]] ){
					level[g[nowAt][i]] = level[nowAt] + 1;
					myQ.push( g[nowAt][i] );
				}
		}
		return level[t];
	}
	int dfsFindRoute(int nowAt, int t, int maxC) {
		if( nowAt==t ){
			maxFlow += maxC;
			return maxC;
		}
		for(int i=0; i<g[nowAt].size(); ++i) {
			int next = g[nowAt][i];
			if( level[next] != level[nowAt]+1 ) continue;
			if( !pipe[nowAt][next] ) continue;
			int nowOut = dfsFindRoute(next ,t ,min(maxC , pipe[nowAt][next]));
			if( nowOut==0 )
				continue;
			pipe[nowAt][next] -= nowOut;
			pipe[next][nowAt] += nowOut;
			return nowOut;
		}
		return 0;
	}
	void dfsFindMinCut(int nowAt) {
		sside[nowAt] = 1;
		for(auto v : g[nowAt])
			if( !sside[v] && pipe[nowAt][v] )
				dfsFindMinCut(v);
	}

public:
	int maxFlow;
	vector<pii> minCut;

	void init(){
		memset(cap  , 0, sizeof(cap));
		memset(pipe , 0, sizeof(pipe));
		memset(sside, 0, sizeof(sside));
		for(int i=0;i<maxN;++i)
			g[i].clear();
		maxFlow = 0;
		minCut.clear();
	}
	void addEdge(int u, int v, int c) {
		if( u==v ) return;
		if( cap[u][v]==0 )
			g[u].emplace_back(v);
		cap[u][v] += c;
	}
	void coculAll(int s, int t) {
		memcpy(pipe, cap, sizeof(pipe));

		// max flow
		while( bfsLabeling(s,t) )
			while( dfsFindRoute(s,t,1023456789) )
				;

		// min cut
		dfsFindMinCut(s);
		for(int u=0; u<maxN; ++u)
		if( sside[u] )
			for(auto v : g[u])
			if( !sside[v] )
				minCut.push_back({u, v});
	}
};

int main() {
	Dinic solver;
	int N, M;
	while( scanf("%d%d", &N, &M)!=EOF ) {
		if( N==0 && M==0 ) break;
		solver.init();
		for(int i=0,u,v,c; i<M; ++i) {
			scanf("%d%d%d", &u, &v, &c);
			solver.addEdge(u, v, c);
			solver.addEdge(v, u, c);
		}
		solver.coculAll(1, 2);
		for(int i=0; i<solver.minCut.size(); ++i)
			printf("%d %d\n",
					solver.minCut[i].first,
					solver.minCut[i].second);
		puts("");
	}
	return 0;
}
