#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;

bool ok(const vector<PII> &ps, int maxCost, int maxCut) {
	int minY = ps[0].second, maxY = ps[0].second;
	for(int i=1; i<ps.size(); ++i) {
		minY = min(minY, ps[i].second);
		maxY = max(maxY, ps[i].second);
		if( maxY - minY > maxCost ) {
			if( --maxCut <= 0 ) return false;
			minY = maxY = ps[i].second;
		}
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int n, k;
		scanf("%d%d", &n, &k);
		vector<PII> ps;
		for(int i=0,x,y; i<n; ++i) {
			scanf("%d%d", &x, &y);
			ps.emplace_back(make_pair(x,y));
		}
		sort(ps.begin(), ps.end());
		int l=0, r=200000000;
		while( l<r ) {
			int c = (l+r)>>1;
			if( ok(ps, c, k) ) r = c;
			else l = c+1;
		}
		printf("%.1f\n", l/2.0);
	}
	return 0;
}
