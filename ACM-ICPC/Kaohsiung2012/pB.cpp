#include <cstdio>
#include <queue>
#include <unordered_set>
using namespace std;

const long long mask = 15LL;

struct state {
	long long v;
	int st, r, c;
};

long long init, target;
inline long long swapBit(long long val,int id1,int id2) {
	long long v1 = val&(mask<<(id1*4));
	val &= ~(mask<<(id1*4));
	long long v2 = val&(mask<<(id2*4));
	val &= ~(mask<<(id2*4));
	val |= (v1>>(id1*4))<<(id2*4);
	val |= (v2>>(id2*4))<<(id1*4);
	return val;
}
inline int cv(const int &r,const int &c) {
	return (2-r)*3 + (2-c);
}
inline bool upd(queue<state> &myQ, unordered_set<long long> &vis, int np, int nr, int nc) {
	long long nextV = swapBit(myQ.front().v, np, cv(nr,nc));
	if( nextV==target ) return true;
	if( vis.find(nextV)==vis.end() ) {
		myQ.push({nextV, myQ.front().st+1, nr, nc});
		vis.insert(nextV);
	}
	return false;
}

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		init = target = 0LL;
		int nowr, nowc;
		for(int i=0,val ; i<3 ; ++i)
			for(int j=0 ; j<3 ; ++j) {
				scanf("%d",&val);
				init <<= 4;
				init += val;
				if( val==0 )
					nowr = i, nowc = j;
			}
		for(int i=0,val ; i<3 ; ++i)
			for(int j=0 ; j<3 ; ++j) {
				scanf("%d",&val);
				target <<= 4;
				target += val;
			}
		queue<state> myQ;
		unordered_set<long long> visited;
		myQ.push({init, 0, nowr, nowc});
		visited.insert(init);
		int ans = -1;
		while( myQ.size() ) {
			long long val = myQ.front().v;
			if( val==target ) {
				ans = myQ.front().st;
				break;
			}
			int st = myQ.front().st;
			int nr = myQ.front().r;
			int nc = myQ.front().c;
			int np = cv(nr, nc);
			if( nr!=0 && upd(myQ, visited, np, nr-1, nc) ) {
				ans = myQ.front().st + 1;
				break;
			}
			if( nr!=2 && upd(myQ, visited, np, nr+1, nc) ) {
				ans = myQ.front().st + 1;
				break;
			}
			if( nc!=0 && upd(myQ, visited, np, nr, nc-1) ) {
				ans = myQ.front().st + 1;
				break;
			}
			if( nc!=2 && upd(myQ, visited, np, nr, nc+1) ) {
				ans = myQ.front().st + 1;
				break;
			}
			if( nr!=2 && nc!=0 && upd(myQ, visited, np, nr+1, nc-1) ) {
				ans = myQ.front().st + 1;
				break;
			}
			myQ.pop();
		}
		printf("%d\n",ans);
	}
	return 0;
}
