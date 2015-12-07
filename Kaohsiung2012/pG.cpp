#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct force{
	char name;
	int pa, pb;
};
bool dp[500004];
int workDP(vector<int> &fs,int target) {
	memset(dp, 0, sizeof(dp));
	dp[0] = true;
	for(auto &f : fs) {
		for(int i=target ; i>=f ; --i)
			if( dp[i-f] ) dp[i] = true;
	}
	for(int i=target ; i>=0 ; --i)
		if( dp[i] ) return i;
}
void process(force &fs) {
	int nworker;
	scanf("%d",&nworker);
	vector<int> vec;
	int sum = 0;
	for(int i=0,v ; i<nworker; ++i) {
		scanf("%d",&v);
		vec.emplace_back(v);
		sum += v;
	}
	fs.pa = workDP(vec, sum>>1);
	fs.pb = sum - fs.pa;
}

int main() {
	int n;
	scanf("%d",&n);
	while( n-- ) {
		force fs[4];
		process(fs[0]); fs[0].name = 'A';
		process(fs[1]); fs[1].name = 'B';
		process(fs[2]); fs[2].name = 'C';
		sort(fs, fs+3, [](const force &l,const force &r){
			return l.pb - l.pa < r.pb - r.pa ||
					l.pb - l.pa == r.pb - r.pa &&
					l.pb + l.pa > r.pb + r.pa;
		});
		printf("%c %d %d\n", fs[0].name, fs[0].pa, fs[0].pb);
	}
	return 0;
}
