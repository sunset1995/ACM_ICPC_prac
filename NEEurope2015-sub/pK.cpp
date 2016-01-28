#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct task{
	int id, l;
	task(const int &id,const int &l)
	:id(id), l(l) {}
};
vector<task> t[100004];
long long ans[100004];

inline long long eval(long long T,long long id) {
	return t[id].back().l - (T-id)*(T-id);
}
inline void process(long long &nowT,int id) {
	if( nowT<=id )
		nowT = id + t[id].back().l;
	else
		nowT += t[id].back().l;
	ans[ t[id].back().id ] = nowT;
	t[id].pop_back();
}

int main() {
	int n;
	scanf("%d",&n);
	for(int i=0,li,ti ; i<n ; ++i) {
		scanf("%d%d",&li,&ti);
		t[ti].emplace_back(task(i,li));
	}
	for(int i=0 ; i<100004 ; ++i)
		sort(t[i].begin(), t[i].end(), [](const task &l,const task &r){
			return l.l > r.l ||
					 l.l == r.l && l.id > r.id;
		});
	int id = 0;
	long long nowT = 0;
	for(int i=0 ; i<n ; ++i) {
		while( t[id].empty() ) ++id;
		if( nowT<id ) {
			process(nowT, id);
			continue;
		}
		long long diff2 = (nowT-id)*(nowT-id);
		int minid = id;
		int minval = eval(nowT, id);
		int to = min(100000LL, nowT);
		for(int j=id+1,diff=1 ; j<=to &&
										diff2-(nowT-j)*(nowT-j)<=100004 ; ++j) { 
			if( t[j].empty() ) continue;
			int val = eval(nowT, j);
			if( val<minval ||
				 val==minval && t[j].back().id<t[minid].back().id ) {
				minval = val;
				minid = j;
			}
		}
		process(nowT, minid);
	}
	for(int i=0 ; i<n ; ++i)
		printf("%lld ",ans[i]);
	puts("");
	return 0;
}
