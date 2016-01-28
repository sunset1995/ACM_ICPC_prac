#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cctype>
#define INF 1023456789
using namespace std;

char mp[104][104];
int N, M;
int label(int r, int c) { return r*100 + c; }

const int dr[4] = {0,0,1,-1};
const int dc[4] = {1,-1,0,0};
struct pos {
	int r, c, len;
	vector<int> nr, nc;
	bool operator < (const pos &rth) const {
		return len > rth.len;
	}
	pos(int r, int c, int len)
	:r(r), c(c), len(len) {
		for(int i=0; i<4; ++i) {
			if( r+dr[i]<0 || c+dc[i]<0 || r+dr[i]>=N || c+dc[i]>=M )
				continue;
			if( mp[r+dr[i]][c+dc[i]]<'1' || mp[r+dr[i]][c+dc[i]]>'9' )
				continue;
			nr.emplace_back(r+dr[i]);
			nc.emplace_back(c+dc[i]);
		}
	}
};

int dA[10004], dB[10004];
void dijkstra(int r, int c, int *d) {
	static char visited[10004];
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<10004; ++i)
		d[i] = INF;
	d[label(r, c)] = 0;
	priority_queue<pos, vector<pos>> myPQ;
	myPQ.push(pos(r, c, 0));
	while( myPQ.size() ) {
		pos now = myPQ.top();
		myPQ.pop();
		if( visited[label(now.r, now.c)] ) continue;
		visited[label(now.r, now.c)] = 1;
		vector<int> nr = now.nr, nc = now.nc;
		for(int i=0; i<nr.size(); ++i)
			if( d[label(now.r, now.c)] + mp[nr[i]][nc[i]] - '0'
				< d[label(nr[i], nc[i])] ) {
				d[label(nr[i], nc[i])]
				= d[label(now.r, now.c)] + mp[nr[i]][nc[i]] - '0';
				myPQ.push(pos(nr[i], nc[i], d[label(nr[i], nc[i])]));
			}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int NOWCASE=1; NOWCASE<=T; ++NOWCASE) {
		scanf("%d%d", &N, &M);
		int sr, sc, er, ec, sum=0;
		for(int i=0; i<N; ++i) {
			scanf("%s", mp[i]);
			if( strchr(mp[i], 'A')!=nullptr ) {
				sr = i;
				sc = strchr(mp[i], 'A') - mp[i];
			}
			if( strchr(mp[i], 'B')!=nullptr ) {
				er = i;
				ec = strchr(mp[i], 'B') - mp[i];
			}
			for(int j=0; j<M; ++j)
				if( isdigit(mp[i][j]) )
					sum += mp[i][j] - '0';
		}
		dijkstra(sr, sc, dA);
		dijkstra(er, ec, dB);
		int minPath = INF;
		for(int i=0; i<N; ++i)
			for(int j=0; j<M; ++j)
				if( mp[i][j]>='1' && mp[i][j]<='9' )
				minPath = min(minPath, 
						dA[label(i, j)]+dB[label(i, j)]-2*(mp[i][j]-'0') );
		printf("Case #%d: ", NOWCASE);
		if( minPath>100000000 ) puts("0");
		else printf("%d\n", sum - minPath);
	}
	return 0;
}
