#include <cstdio>
#include <map>
using namespace std;

int n, k;
int t[10004];
int sum=0;

void show_ans() {
	printf("%d\n", sum);
	for(int i=0; i<n; ++i)
		printf("%d ", t[i]);
	puts("");
}

int main() {
	freopen("generators.in", "r", stdin);
	freopen("generators.out", "w", stdout);

	scanf("%d%d", &n, &k);
	int notkId=-1, notkT=-1, notkVal=-1;
	for(int i=0,x0,a,b,c; i<n; ++i) {
		scanf("%d%d%d%d", &x0, &a, &b, &c);
		int id = 0;
		map<int, int> mp;
		x0 %= c;
		while( mp.find(x0)==mp.end() ) {
			mp[x0] = id++;
			x0 = (a*x0 + b) % c;
		}
		int nowMax = mp.rbegin()->first;
		for(auto it=mp.begin(); it!=mp.end(); ++it) {
			int nowVal = nowMax-(it->first);
			if( nowVal%k!=0
				&& (notkVal==-1 || notkVal>nowVal) ) {
				notkId = i;
				notkT = it->second;
				notkVal = nowVal;
			}
		}
		t[i] = mp.rbegin()->second;
		sum += nowMax;
	}
	if( sum%k != 0 ) {
		show_ans();
		return 0;
	}
	if( notkVal==-1 ) {
		printf("-1\n");
		return 0;
	}
	sum -= notkVal;
	t[notkId] = notkT;
	show_ans();
	return 0;
}
