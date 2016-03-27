#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int n, R, C1, C2, C3;
struct House {
	int l, r, sig;
	House(int l, int r, int sig)
	:l(l), r(r), sig(sig) {}
};
struct Key {
	int id;
	long long s1, s2;
	Key(int id, long long s1, long long s2)
	:id(id), s1(s1), s2(s2) {}
	bool operator < (const Key &rth) const {
		if( id != rth.id ) return id < rth.id;
		if( s1 != rth.s1 ) return s1 < rth.s1;
		if( s2 != rth.s2 ) return s2 < rth.s2;
		return false;
	}
};

typedef long long lld;
typedef const vector<House> vechs;

map<Key, lld> dp;
lld recur(vechs &hs, int id, lld s1, lld s2) {
	if( id >= hs.size() ) return 0;
	Key nowst = Key(id, s1, s2);
	auto it = dp.find(nowst);
	if( it != dp.end() )
		return it->second;
	lld res;
	if( hs[id].sig == 1 ) {
		if( hs[id].l <= s1 )
			return recur(hs, id+1, s1, s2);
		s1 = 2LL*R + hs[id].r;
		lld tmp1 = C1 + recur(hs, id+1, s1, s2);
		lld tmp3 = C3 + recur(hs, id+1, s1, max(s2, s1));
		res = min(tmp1, tmp3);
	}
	else {
		if( hs[id].l <= s2 )
			return recur(hs, id+1, s1, s2);
		s2 = 2LL*R + hs[id].r;
		lld tmp2 = C2 + recur(hs, id+1, s1, s2);
		lld tmp3 = C3 + recur(hs, id+1, max(s1, s2), s2);
		res = min(tmp2, tmp3);
	}
	dp[nowst] = res;
	return res;
}

int main() {
	while( scanf("%d%d%d%d%d", &n, &R, &C1, &C2, &C3)!=EOF ) {
		if( !n && !R && !C1 && !C2 && !C3 ) break;
		vector<House> hs;
		for(int i=0,x1,x2,sig; i<n; ++i) {
			scanf("%d%d%d", &x1, &x2, &sig);
			hs.emplace_back(House(x1, x2, sig));
		}
		sort(hs.begin(), hs.end(), [](const House &a, const House &b) {
			return a.r < b.r;
		});
		dp.clear();
		lld ans = recur(hs, 0, -1, -1);
		printf("%lld\n", ans);
	}
	return 0;
}
