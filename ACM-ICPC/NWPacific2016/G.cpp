#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int maxNum = 100004;

long long fwk[maxNum], cnt;
long long lowbit(long long x) {
	return x & (-x);
}
void update(long long x,long long v) {
	for(; x <= cnt; x += lowbit(x))
		fwk[x] = max(fwk[x], v);
}
long long query(long long x) {
	long long Mx = 0;
	for(; x > 0; x -= lowbit(x))
		Mx = max(Mx, fwk[x]);
	return Mx;
}

struct Point{
	long long x, y, bl, br;
	bool operator < (const Point &p) const {
		if(bl != p.bl) return bl > p.bl;
		return br > p.br;
	}
};
Point ps[maxNum];
int main() {
	memset(fwk, 0, sizeof(fwk));
	long long m, n, r, w, h;
	scanf("%I64d%I64d%I64d%I64d", &n, &r, &w, &h);
	m = r;
	map<long long,long long,greater<long long> > mp;
	for(long long i=0; i<n; ++i) {
		scanf("%I64d%I64d", &ps[i].x, &ps[i].y);
		ps[i].bl = ps[i].y - m * ps[i].x;
		ps[i].br = ps[i].y + m * ps[i].x;
		mp.insert(make_pair(ps[i].br, 0));
	}
	cnt = 1;
	for(map<long long,long long>::iterator it = mp.begin(); it!=mp.end(); it++)
		it->second = cnt++;
	sort(ps, ps+n);
	long long ans = 1;
	//puts("------");
	for(long long i = 0; i < n; i++) {
		//printf("%lld %lld\n",ps[i].x,ps[i].y);
		long long index = mp[ps[i].br];
		//printf("index = %d\n",index);
		long long k = query(index) + 1;
		update(index, k);
		ans = max(ans, k);
	}
	printf("%I64d\n", ans);
	return 0;
}
