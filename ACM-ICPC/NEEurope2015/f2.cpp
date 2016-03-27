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

struct edge {
	int to;
	double len;
};

double w;
int n;
double x[1004], y[1004];
vector<edge> G[1004];
bool inQ[1004];
double stD[1004], enD[1004];
double len(int i, int j) {
	double xdif = x[i]-x[j];
	double ydif = y[i]-y[j];
	return sqrt(xdif*xdif + ydif*ydif);
}

void SPFA(int s, double *d) {
	memset(inQ, 0, sizeof(inQ));
	inQ[s] = true;
	d[s] = 0;
	queue<int> myQ;
	myQ.push(s);
	while( myQ.size() ) {
		int nowAt = myQ.front();
		myQ.pop();
		inQ[nowAt] = false;
		for(int i=0; i<G[nowAt].size(); ++i) {
			const edge &nowEdge = G[nowAt][i];
			if( d[nowEdge.to]<0
				||fdif(
					max(d[nowAt], nowEdge.len) - d[nowEdge.to])<0 ) {
				d[nowEdge.to] = max(d[nowAt], nowEdge.len);
				if( !inQ[nowEdge.to] ) {
					myQ.push(nowEdge.to);
					inQ[nowEdge.to] = true;
				}
			}
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
	G[0].push_back({n+1, w});
	G[n+1].push_back({0, w});
	for(int i=1; i<=n; ++i) {
		G[i].push_back({0, x[i]});
		G[0].push_back({i, x[i]});
		G[i].push_back({n+1, w-x[i]});
		G[n+1].push_back({i, w-x[i]});
		for(int j=1; j<=n; ++j) {
			double nowlen = len(i, j);
			G[i].push_back({j, nowlen});
			G[j].push_back({i, nowlen});
		}
	}
	for(int i=0; i<1004; ++i)
		stD[i] = enD[i] = -1.0;
	SPFA(0, stD);
	SPFA(n+1, enD);
	ansLen = enD[0];
	for(int i=0; i<=n+1; ++i)
		for(int j=0; j<G[i].size(); ++j) {
			int u = i;
			int v = G[i][j].to;
			double len = G[i][j].len / 2.0;
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
