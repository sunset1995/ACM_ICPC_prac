#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int fdif(double lf) {
	if( fabs(lf)<1e-9 ) return 0;
	return lf>0? 1 : -1;
}

double w;
int n;
double x[1004], y[1004];
double G[1004][1004];
bool visited[1004];
double stD[1004], enD[1004];
double len(int i, int j) {
	double xdif = x[i]-x[j];
	double ydif = y[i]-y[j];
	return sqrt(xdif*xdif + ydif*ydif);
}

struct myPair {
	int id, len;
	myPair(int id, int len)
	:id(id), len(len) {}
	bool operator < (const myPair &rth) const {
		return len > rth.len;
	}
};

void dijkstra(int s, double *d) {
	memset(visited, 0, sizeof(visited));
	d[s] = 0;
	priority_queue<myPair, vector<myPair>> myPQ;
	myPQ.push(myPair(s, 0));
	while( myPQ.size() ) {
		int nowAt = myPQ.top().id;
		myPQ.pop();
		if( visited[nowAt] ) continue;
		visited[nowAt] = true;
		for(int i=0; i<=n+1; ++i)
			if( d[i]<0 || fdif(max(d[nowAt], G[nowAt][i]) - d[i])<0 ) {
				d[i] = max(d[nowAt], G[nowAt][i]);
				myPQ.push(myPair(i, d[i]));
			}
	}
}

double ansLen;
double ansX=0.5, ansY=0.5;
void udp(int u, int v, double nLen) {
	ansLen = nLen;
	if( u==0 && v==n+1 || u==n+1 && v==0 ) {
		ansLen = w / 2.0;
		ansX = w / 2.0;
		ansY = 0;
	}
	else if( u==0 ) {
		ansX = x[v] / 2.0;
		ansY = y[v];
	}
	else if ( u==n+1 ) {
		ansX = (w-x[v]) / 2.0 + x[v];
		ansY = y[v];
	}
	else if( v==0 ) {
		ansX = x[u] / 2.0;
		ansY = y[u];
	}
	else if( v==n+1 ) {
		ansX = (w-x[u]) / 2.0 + x[u];
		ansY = y[u];
	}
	else {
		ansX = (x[u]+x[v]) / 2.0;
		ansY = (y[u]+y[v]) / 2.0;
	}
}

int main() {
	freopen("froggy.in", "r", stdin);
	freopen("froggy.out", "w", stdout);

	scanf("%lf%d", &w, &n);
	for(int i=1; i<=n; ++i)
		scanf("%lf%lf", &x[i], &y[i]);
	G[0][n+1] = w;
	G[n+1][0] = w;
	for(int i=1; i<=n; ++i) {
		G[i][0] = x[i];
		G[0][i] = x[i];
		G[i][n+1] = w-x[i];
		G[n+1][i] = w-x[i];
		for(int j=1; j<=n; ++j) {
			double nowlen = len(i, j);
			G[i][j] = nowlen;
			G[j][i] = nowlen;
		}
	}
	for(int i=0; i<1004; ++i)
		stD[i] = enD[i] = -1.0;
	dijkstra(0, stD);
	dijkstra(n+1, enD);
	ansLen = enD[0];
	for(int i=0; i<=n+1; ++i)
		for(int j=0; j<=n+1; ++j) {
			if( i==j ) continue;
			int u = i;
			int v = j;
			double len = G[i][j] / 2.0;
			double nLen1 = max(max(stD[u], enD[v]), len);
			double nLen2 = max(max(stD[v], enD[u]), len);
			double nLen = min(nLen1, nLen2);
			if( fdif(nLen-ansLen)<0 )
				udp(u, v, nLen);
		}
	if( fdif(ansX)==0 || fdif(ansX-w)==0 )
		ansX = 0.5;
	printf("%.5f %.5f\n", ansX, ansY);
	return 0;
}
