#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

vector<pii> primeFac(int n) {
	vector<pii> ret;
	for(int i=2; n>1; ++i){
		if( n%i != 0 ) continue;
		int e = 0;
		while( n%i == 0 ) ++e , n/=i;
		ret.push_back({i, e});
	}
	return ret;
}
int phi(int n){
	// euler function: in [0,n], # of coprime(i, n)
	vector<pii> fac = primeFac(n);
	int num = 1 , m = 1;
	for(auto &p : fac)
		num *= (p.first-1) , m *= p.first;
	return n/m * num;
}
long long fastPow(long long x, int n, long long m){
	long long ans = 1LL;
	while( n ){
		if( n&1 ) ans = ans * x % m;
		x = x*x % m;
		n >>= 1;
	}
	return ans;
}
long long modInv_euler(long long x, long long m){
	// must be gcd(x,m)==1
	// phi is euler function: O(sqrt(x))
	return fastPow(x, phi(m)-1, m);
}
int china(const vector<pii> &rule){
	// x = ai mod mi, mi coprime to each others
	long long MM = 1LL;
	for(auto &r : rule)
		MM *= r.second;
	long long x = 0LL;
	for(auto &r : rule){
		long long ai = r.first;
		long long mi = r.second;
		long long Mi = MM / r.second;
		long long Mv = modInv_euler(Mi%mi, mi);
		long long tmp = ai*Mi%MM *Mv %MM;
		x = (x+tmp) % MM;
	}
	return x;
}

int main() {
	int NOWCASE = 0;
	int p, e, i, d;
	int step = 23*28*33;
	while( scanf("%d%d%d%d", &p, &e, &i, &d)!=EOF ) {
		if( p==e && e==i && i==d && d==-1 ) break;
		vector<pii> rules = {
			{p%23, 23},
			{e%28, 28},
			{i%33, 33}
		};
		int start = china(rules);
		int ans   = (step+start-d)%step;
		if( ans==0 ) ans = step;
		printf("Case %d: the next triple peak occurs in %d days.\n", ++NOWCASE, ans);
	}
	return 0;
}
