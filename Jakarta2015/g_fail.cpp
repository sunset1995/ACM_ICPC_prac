#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 1023456789

struct Grid {
	int r, c, minD, maxC;
	bool operator < (const Grid &rth) const {
		return minD-maxC > rth.minD-rth.maxC;
	}
};

int N, M;
Grid grid[104][104];
char buffer[104];
int puzzle[104][104];
bool visited[104][104];

const int dR[4] = {0,0,1,-1};
const int dC[4] = {1,-1,0,0};
void initDijkstra() {
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<104; ++i)
		for(int j=0; j<104; ++j)
			grid[i][j] = (Grid) {
				.r = i,
				.c = j,
				.minD = INF,
				.maxC = 0
			};
}
bool ok(int r, int c) {
	return r>=0 && r<N && c>=0 && c<M && puzzle[r][c]!=-1;
}
bool relaxable(int fR, int fC, int tR, int tC) {
	if( !ok(fR, fC) || !ok(tR, tC) ) return false;
	if( grid[fR][fC].minD + puzzle[tR][tC] - max(grid[fR][fC].maxC, puzzle[tR][tC])
		< grid[tR][tC].minD - grid[tR][tC].maxC )
		return true;
	return false;
}
void dijkstra(int sr, int sc) {
	grid[sr][sc].minD = 0;
	priority_queue<Grid, vector<Grid>> myPQ;
	myPQ.push(grid[sr][sc]);
	while( myPQ.size() ) {
		int nowR = myPQ.top().r;
		int nowC = myPQ.top().c;
		int nowLen = myPQ.top().minD;
		int nowMax = myPQ.top().maxC;
		//printf("nowAt %d %d len %d maxC %d\n", nowR, nowC, nowLen, nowMax);
		myPQ.pop();
		for(int i=0; i<4; ++i) {
			int nextR = nowR + dR[i];
			int nextC = nowC + dC[i];
			if( relaxable(nowR, nowC, nextR, nextC) ) {
				grid[nextR][nextC].minD = grid[nowR][nowC].minD + puzzle[nextR][nextC];
				grid[nextR][nextC].maxC = max(grid[nowR][nowC].maxC, puzzle[nextR][nextC]);
				myPQ.push(grid[nextR][nextC]);
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int NOWCASE=1; NOWCASE<=T; ++NOWCASE) {
		scanf("%d%d", &N, &M);
		int sr, sc, er, ec;
		int sum = 0;
		for(int i=0; i<N; ++i) {
			scanf("%s", buffer);
			for(int j=0; j<M; ++j) {
				if( buffer[j]=='A' )
					sr = i, sc = j, puzzle[i][j] = 0;
				else if( buffer[j]=='B' )
					er = i, ec = j, puzzle[i][j] = 0;
				else if( buffer[j]=='0' )
					puzzle[i][j] = -1;
				else {
					puzzle[i][j] = buffer[j] - '0';
					sum += puzzle[i][j];
				}
			}
		}
		/*
		for(int i=0; i<N; ++i, puts(""))
			for(int j=0; j<M; ++j)
				printf("%2d ", puzzle[i][j]);
		*/
		initDijkstra();
		dijkstra(sr, sc);
		
		printf("Case #%d: ", NOWCASE);
		if( grid[er][ec].minD==INF ) puts("0");
		else printf("%d\n", sum-grid[er][ec].minD+grid[er][ec].maxC);
	}
	return 0;
}
