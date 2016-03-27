#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int val[500004];
bool visited[500004];
struct myCmp {
	bool operator()(const int &l, const int &r) const {
		return val[l] < val[r]
			|| (val[l]==val[r] && l>r);
	}
};
typedef priority_queue<int, vector<int>, myCmp> PQ;

inline void add(int id, int n, int m, PQ &pq) {
	visited[id] = 1;
	int pid=id>>1, lid=id<<1, rid=(id<<1)+1;
	if( pid>0 && !visited[pid] ) {
		val[pid] += (id-pid) % m;
		pq.push(pid);
	}
	if( lid<=n && !visited[lid] ) {
		val[lid] += (lid-id) % m;	
		pq.push(lid);
	}
	if( rid<=n && !visited[rid] ) {
		val[rid] += (rid-id) % m;
		pq.push(rid);
	}
}

int main() {
	int k;
	scanf("%d", &k);
	while( k-- ) {
		int n, s, m;
		scanf("%d%d%d", &n, &s, &m);
		memset(visited, 0, sizeof(visited));
		memset(val, 0, sizeof(val));
		printf("%d", s);
		PQ pq;
		add(s, n, m, pq);
		while( pq.size() ) {
			int id = pq.top();
			pq.pop();
			if( visited[id] ) continue;
			printf(" %d", id);
			add(id, n, m, pq);
		}
		puts("");
	}
	return 0;
}
