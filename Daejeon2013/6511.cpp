#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int link[100004];
char visited[100004];

int findCycle(int nowAt) {
	vector<int> stk;
	while( !visited[nowAt] ) {
		visited[nowAt] = true;
		stk.emplace_back(nowAt);
		nowAt = link[nowAt];
	}
	int cnt = 0;
	for(int i=0, find=0; i<stk.size(); ++i) {
		if( stk[i] == nowAt ) find = 1;
		if( find ) ++cnt;
	}
	return cnt;
}

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int n;
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			scanf("%d", &link[i]);
		memset(visited, 0, sizeof(visited));
		int ans = n;
		for(int i=1; i<=n; ++i)
			if( !visited[i] )
				ans -= findCycle(i);
		printf("%d\n",ans);
	}
	return 0;
}
