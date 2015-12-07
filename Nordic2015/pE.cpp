#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct tt {
	int id, type, cor;
	bool operator < (const tt &rth) const {
		return id < rth.id ||
				 id == rth.id && type > rth.type;
	}
};

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	vector<tt> es;
	for(int i=0,s,e ; i<n ; ++i) {
		scanf("%d%d",&s,&e);
		es.push_back({s,0,e});
		es.push_back({e,1,s});
	}
	sort(es.begin(), es.end());
	map<int, int> mp;
	int ans = 0, cnt = 0;
	for(auto &e : es) {
		if( e.type == 1 ) {
			if( mp.find(e.id)!=mp.end() ) {
				++ans, --cnt;
				if( --mp[e.id] == 0 )
					mp.erase(e.id);
			}
			continue;
		}
		mp[e.cor]++;
		++cnt;
		if( cnt>k ) {
			auto it = mp.rbegin();
			if( --it->second == 0 )
				mp.erase(it->first);
			--cnt;
		}
	}
	printf("%d\n",ans);
	return 0;
}
