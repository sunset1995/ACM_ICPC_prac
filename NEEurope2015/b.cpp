#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> bindec;
void addOne(bindec &rth) {
	int i=0;
	while( i<rth.size() && rth[i]==1 )
		rth[i] = 0, ++i;
	if( i==rth.size() ) rth.emplace_back(1);
	else rth[i] = 1;
}
void div2(bindec &rth) {
	int last = 0;
	for(int i=rth.size()-1; i>=0; --i) {
		int nlast = (last*10 + rth[i])%2;
		rth[i] = (last*10 + rth[i])/2;
		last = nlast;
	}
	while( rth.back()==0 )
		rth.pop_back();
}
void show(const bindec &rth) {
	for(int i=rth.size()-1; i>=0; --i)
		printf("%d", rth[i]);
	puts("");
}
bool ok(const bindec &rth) {
	bindec dec = rth;
	int cnt = 0;
	while( cnt!=rth.size() ) {
		if( dec[0]%2 != rth[cnt] )
			return false;
		++cnt;
		div2(dec);
	}
	return true;
}

int main() {
	//freopen("binary.in", "r", stdin);
	//freopen("binary.in", "w", stdout);

	int n;
	scanf("%d", &n);

	bindec now = {1};
	while( true ) {
		while( !ok(now) )
			addOne(now);
		if( --n==0 ) break;
		addOne(now);
	}
	show(now);

	return 0;
}
