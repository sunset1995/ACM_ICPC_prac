#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> preprocess() {
	vector<int> len;
	for(long long y=1; y<=500000; ++y)
		for(long long x=y+1;  ; ++x) {
			long long a = 2*x*y, b = x*x - y*y;
			if( a+b > 500000 ) break;
			int w = min(a, b), h = max(a, b);
			if( __gcd(w, h)!=1 ) continue;
			len.emplace_back( (w+h)<<1 );
		}
	sort(len.begin(), len.end());
	return len;
}

int main() {
	vector<int> len = preprocess();
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int L;
		scanf("%d", &L);
		int ans = 0;
		for(int i=0; i<len.size(); ++i)
			if( len[i] <= L ) {
				L -= len[i];
				++ans;
			}
			else break;
		printf("%d\n",ans);
	}
	return 0;
}
