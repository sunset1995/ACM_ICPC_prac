#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Cake{
	int len , wid;
	int id , id1 , id2;
} cake[4004];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0,a,b ; i<n ; ++i){
		scanf("%d%d",&a,&b);
		cake[i].len = max(a,b);
		cake[i].wid = min(a,b);
		cake[i].id = i;
	}

	vector<int> id1s , id2s;
	for(int i=0 ; i<n ; ++i){
		id1s.emplace_back(i);
		id2s.emplace_back(i);
	}
	sort(id1s.begin() , id1s.end() , [](const int &l,const int &r){
		return cake[l].len > cake[r].len || 
				 cake[l].len==cake[r].len && cake[l].id < cake[r].id;
	});
	sort(id2s.begin() , id2s.end() , [](const int &l,const int &r){
		return cake[l].wid > cake[r].wid ||
				 cake[l].wid==cake[r].wid && cake[l].id < cake[r].id;
	});
	for(int i=0 ; i<n ; ++i){
		cake[ id1s[i] ].id1 = i;
		cake[ id2s[i] ].id2 = i;
	}

	long long ansArea = 0LL;
	int ansL , ansW;
	for(int i=0 ; i<n ; ++i){
		long long nowL = cake[ id1s[i] ].len;
		int to = cake[ id1s[i] ].id2;
		int cnt = 0;
		for(int j=0 ; j<to ; ++j){
			if( cake[ id2s[j] ].id1 > i ) continue;
			++cnt;
		}
		for(int j=to ; j<n ; ++j){
			if( cake[ id2s[j] ].id1 > i ) continue;
			++cnt;
			long long nowW = cake[ id2s[j] ].wid;
			if( nowL*nowW*cnt > ansArea ){
				ansArea = nowL*nowW*cnt;
				ansL = nowL;
				ansW = nowW;
			}
		}
	}
	printf("%lld\n%d %d\n",ansArea,ansL,ansW);
	return 0;
}
