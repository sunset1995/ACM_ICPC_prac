#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<int> g[100004];
char critical[100004];
int team[100004];
int pairNum[100004];

void init() {
	memset(critical, 0, sizeof(critical));
	memset(team, -1 , sizeof(team));
	memset(pairNum, 0, sizeof(pairNum));
	for(int i=0 ; i<100004 ; ++i)
		g[i].clear();
}

void dfs(int nowAt,int p) {
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( g[nowAt][i]!=p )	{
			dfs(g[nowAt][i], nowAt);
			pairNum[nowAt] += pairNum[g[nowAt][i]];
			if( team[nowAt]==-1 && team[g[nowAt][i]]==-1 ) {
				team[g[nowAt][i]] = nowAt;
				team[nowAt] = g[nowAt][i];
				++pairNum[nowAt];
			}
		}
}

int main() {
	int NCASE;
	scanf("%d",&NCASE);
	while( NCASE-- ) {
		init();
		int n;
		scanf("%d",&n);
		for(int i=1,p ; i<n ; ++i) {
			scanf("%d",&p);
			g[p].push_back(i);
			g[i].push_back(p);
		}
		dfs(0,-1);
		printf("%d\n",pairNum[0]);
	}
	return 0;
}
