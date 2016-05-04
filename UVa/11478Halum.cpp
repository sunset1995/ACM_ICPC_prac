#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

class System_of_DifConstrain {
private:
	static const int maxN = 504;
	static const int maxM = 3004;
	struct Edge {
		int s, t;
		long long cost;
	};
	Edge es[maxM];
	int eSize;
public:
	bool solvable;
	long long x[maxN]; // one solution
	void init() {
		eSize = -1;
	}
	void addConstrain(int xI, int xJ, long long c) {
		// add xi - xj <= c
		es[++eSize] = {xJ, xI, c};
	}
	bool solve(int n=maxN) {
		// n is max node of CC
		memset(x, 0, sizeof(x));
		for(int i=0; i<n; ++i)
		for(int j=0; j<=eSize; ++j)
			if( x[es[j].s] + es[j].cost < x[es[j].t] )
				x[es[j].t] = x[es[j].s] + es[j].cost;
		for(int j=0; j<=eSize; ++j)
			if( x[es[j].s] + es[j].cost < x[es[j].t] )
				return solvable = false;
		return solvable = true;
	}
};
System_of_DifConstrain solver;
vector<int> a, b, d;

bool ok(long long c, int n) {
	solver.init();
	for(int i=0; i<a.size(); ++i)
		solver.addConstrain(b[i], a[i], d[i]-c);
	return solver.solve(n);
}

int main() {
	int n, m;
	while( scanf("%d%d", &n, &m)!=EOF ) {
		a.clear();
		b.clear();
		d.clear();
		for(int i=0,xi,xj,c; i<m; ++i) {
			scanf("%d%d%d", &xi, &xj, &c);
			a.emplace_back(xi);
			b.emplace_back(xj);
			d.emplace_back(c);
		}
		if( !ok(1, n) ) puts("No Solution");
		else if( ok(10001, n) ) puts("Infinite");
		else {
			long long l=1, r=10000LL;
			while( l<r ) {
				long long c = (l+r+1)/2;
				if( ok(c, n) )
					l = c;
				else r = c-1;
			}
			printf("%lld\n", l);
		}
	}
	return 0;
}
