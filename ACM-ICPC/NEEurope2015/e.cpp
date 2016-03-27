#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);

	int n, k;
	scanf("%d%d", &n, &k);

	vector<int> pbset[14];
	for(int i=0; i<n; ++i) {
		int pi, val;
		scanf("%d", &pi);
		while( pi-- ) {
			scanf("%d", &val);
			pbset[i].emplace_back(val);
		}
	}

	int ans = 0, selected=0;
	for(int i=0; i<k && selected<k; ++i)
		for(int j=0; j<n && selected<k; ++j) {
			if( i>=pbset[j].size() )
				pbset[j].emplace_back(50);
			if( pbset[j][i] >= ans ) {
				ans += pbset[j][i];
				++selected;
			}
		}
	ans += (k-selected)*50;
	printf("%d\n", ans);
	return 0;
}
