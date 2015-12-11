#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> G[104];
vector<int> root;
int ans;

void init() {
	for(int i=0 ; i<104 ; ++i)
		G[i].clear();
	root.clear();
	ans = 0;
}
int dfs(int nowAt) {
	if( G[nowAt].empty() ) {
		++ans;
		return 1;
	}
	int cnt = 0, IhavePicked = 0;
	for(int i=0 ; i<G[nowAt].size() ; ++i) {
		int res = dfs(G[nowAt][i]);
		if( res==1 ) ++cnt;
		else if( res==2 ) {
			if( !IhavePicked ) IhavePicked = 1;
			else --ans;
		}
	}
	if( IhavePicked ) return 1;
	if( cnt>=2 ) return 0;
	++ans;
	return cnt==0? 1 : 2;
}

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		init();
		int n;
		scanf("%d",&n);
		for(int i=1,u ; i<=n ; ++i) {
			scanf("%d",&u);
			if( u<i ) G[u].push_back(i);
			else root.push_back(i);
		}
		for(int i=0 ; i<root.size() ; ++i)
			dfs(root[i]);
		printf("%d\n",ans);
	}
	return 0;
}
