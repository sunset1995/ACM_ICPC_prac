#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<int> g[14];
int S, T, cnt;
bool visited[14];

void dfs(int nowAt) {
	if( nowAt==T ) {
		++cnt;
		return;
	}
	visited[nowAt] = true;
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( !visited[g[nowAt][i]] )
			dfs(g[nowAt][i]);
	visited[nowAt] = false;
}

void init() {
	for(int i=0 ; i<14 ; ++i)
		g[i].clear();
	memset(visited, 0, sizeof(visited));
	cnt = 0;
}

int main() {
	int NCASE;
	scanf("%d",&NCASE);
	while( NCASE-- ) {
		init();
		int N, D;
		scanf("%d%d%d%d",&N,&D,&S,&T);
		for(int i=1,n ; i<=N ; ++i) {
			scanf("%d",&n);
			for(int j=0,v ; j<n ; ++j) {
				scanf("%d",&v);
				g[i].push_back(v);
			}
		}
		dfs(S);
		printf("%d\n",cnt);
	}
	return 0;
}
