#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> g[100004];
vector<int> ans;
char canFound[100004];
int team[100004];

void init() {
	memset(canFound, -1, sizeof(canFound));
	memset(team, -1 , sizeof(team));
	for(int i=0 ; i<100004 ; ++i)
		g[i].clear();
	ans.clear();
}

void dfs(int nowAt,int p) {
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( g[nowAt][i]!=p )	{
			dfs(g[nowAt][i], nowAt);
			if( team[nowAt]==-1 && team[g[nowAt][i]]==-1 ) {
				team[g[nowAt][i]] = nowAt;
				team[nowAt] = g[nowAt][i];
			}
		}
}
char canFindAugment(int nowAt) {
	if( canFound[nowAt]!=-1 ) {
		//printf("good at %d\n",nowAt);
		return canFound[nowAt];
	}
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( g[nowAt][i]!=team[nowAt] && team[g[nowAt][i]]==-1 )
			return (canFound[nowAt] = 1);
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( g[nowAt][i]!=team[nowAt] &&
			 canFindAugment(team[g[nowAt][i]]) )
			return (canFound[nowAt] = 1);
	return (canFound[nowAt] = 0);
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
		int cntPair=0, cntCri=0;
		for(int i=0 ; i<n ; ++i) {
			if( team[i]==-1 ) continue;
			++cntPair;
			if( !canFindAugment(team[i]) ) {
				++cntCri;
				ans.push_back(-i);
				sort(ans.begin(), ans.end());
				while( ans.size() > 3 )
					ans.pop_back();
			}
		}
		printf("%d %d\n",cntPair>>1, cntCri);
		for(int i=0 ; i<ans.size() ; ++i) {
			if( i ) putchar(' ');
			printf("%d",-ans[i]);
		}
		puts("");
	}
	return 0;
}
