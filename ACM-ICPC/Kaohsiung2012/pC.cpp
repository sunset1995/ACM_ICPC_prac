#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct edge {
	int name, to;
	edge(){}
	edge(const int &name,const int &to)
	:name(name), to(to) {}
};
vector<edge> g[5004];
char fed[5004];

void init() {
	for(int i=0 ; i<5004 ; ++i)
		g[i].clear();
}

struct st {
	int step, from;
	edge p;
	st(){}
	st(const int &step,const int &from,const edge &p)
	:step(step), from(from), p(p) {}
};
struct myCmp {
	bool operator () (const st &l,const st &r) const {
		return l.step > r.step ||
				l.step == r.step && l.p.name > r.p.name;
	}
};
bool done[5004];
st from[5004];

int main() {
	int N;
	scanf("%d",&N);
	while( N-- ) {
		int P;
		scanf("%d",&P);
		for(int i=0 ; i<P ; ++i) {
			int id;
			scanf("%d",&id);
			scanf(" %c",&fed[id]);
			fed[id] -= 'A';
			int outE;
			scanf("%d",&outE);
			for(int j=0 ; j<outE ; ++j) {
				int name, to;
				scanf(" %*c%d%d",&name,&to);
				g[id].emplace_back(edge(name,to));
			}
		}
		int Q;
		scanf("%d",&Q);
		while( Q-- ) {
			int s, t;
			char str[30];
			scanf("%d%d%s",&s,&t,str);
			bool isfed[26];
			memset(isfed, 0, sizeof(isfed));
			for(int i=0 ; str[i]!='\0' ; ++i)
				isfed[str[i]-'A'] = true;
			memset(done, 0, sizeof(done));
			priority_queue<st, vector<st>, myCmp> myPQ;
			myPQ.push(st(0,s,edge(0,s)));
			while( myPQ.size() ) {
				st now = myPQ.top();
				myPQ.pop();
				if( done[now.p.to] ) continue;
				done[now.p.to] = true;
				from[now.p.to] = now;
				if( now.p.to == t ) break;
				for(auto &next : g[now.p.to]) {
					//if( done[next.to] ) continue;
					st nst(now.step, now.p.to, next);
					if( !isfed[fed[now.p.to]] || !isfed[fed[next.to]] )
						nst.step++;
					myPQ.push(nst);
				}
			}
			vector<st> ans;
			int ansid = t;
			while( ansid!=s ) {
				if( !isfed[fed[from[ansid].from]] ||
					 !isfed[fed[from[ansid].p.to]] )
					ans.emplace_back(from[ansid]);
				ansid = from[ansid].from;
			}
			for(int i=ans.size()-1 ; i>=0 ; --i) {
				printf("T%d",ans[i].p.name);
				if(i) printf(" ");
			}
			puts("");
		}
	}
	return 0;
}
