#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int root[100004], dis[100004];
int find_root(int id) {
	if( root[id]==id ) return id;
	int master = find_root(root[id]);
	dis[id] += dis[root[id]];
	return root[id] = master;
}

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int n;
		scanf("%d",&n);
		for(int i=1; i<=n; ++i) {
			root[i] = i;
			dis[i] = 0;
		}
		int num = 0;
		for(int i=1,master; i<=n; ++i) {
			scanf("%d", &master);
			if( find_root(master)==i )
				num += dis[master] + 1;
			else {
				root[i] = master;
				dis[i] = 1;
			}
		}
		printf("%d\n",n-num);
	}
	return 0;
}
