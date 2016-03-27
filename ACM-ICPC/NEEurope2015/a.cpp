#include <cstdio>
using namespace std;

bool doneR[1000004], doneC[1000004];
long long n;
long long r_ops, c_ops;
long long r_record, c_record;
long long queryC(long long c) {
	if( doneC[c] )
		return 0LL;
	doneC[c] = true;
	long long res = c*(n-r_ops);
	res += n*(n+1)/2.0 - r_record;
	++c_ops;
	c_record += c;
	return res;
}
long long queryR(long long r) {
	if( doneR[r] )
		return 0LL;
	doneR[r] = true;
	long long res = r*(n-c_ops);
	res += n*(n+1)/2.0 - c_record;
	++r_ops;
	r_record += r;
	return res;
}

int main() {
	freopen("adjustment.in", "r", stdin);
	freopen("adjustment.out", "w", stdout);

	int q;
	scanf("%lld%d", &n, &q);
	while( q-- ) {
		char cmd[5];
		int v;
		scanf("%s%d", cmd, &v);
		if( cmd[0]=='R' )
			printf("%lld\n", queryR(v));
		else
			printf("%lld\n", queryC(v));
	}

	return 0;
}
