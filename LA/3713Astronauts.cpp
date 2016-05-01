#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

int fdif(const double &lf) {
	if( fabs(lf)<1e-9 ) return 0;
	return lf<0? -1 : 1;
}

class TwoSAT {
private:
	static const int maxN = 100004;
	static const int size = 2*maxN + 4;
	bool        pick[size];
	vector<int> G   [size];

	int id(int i, int T) { return (i<<1) + T; }
	int alter(int i) { return i^1; }
	bool dfsTry(int nowAt, vector<int> &stk) {
		if( pick[alter(nowAt)] )
			return false;
		stk.emplace_back(nowAt);
		pick[nowAt] = true;
		for(auto v : G[nowAt]) {
			if( !pick[v] && !dfsTry(v, stk) )
				return false;
		}
		return true;
	}
public:
	void init() {
		memset(pick, 0, sizeof(pick));
		for(int i=0; i<size; ++i)
			G[i].clear();
	}
	void addClause(bool TA, int A, bool TB, int B) {
		// add clause (TA + TB)
		// while TA not true, TB must true. vise versa.
		G[id(A, !TA)].emplace_back(id(B, TB));
		G[id(B, !TB)].emplace_back(id(A, TA));
	}
	bool solve() {
		memset(pick, 0, sizeof(pick));
		for(int i=0; i<maxN; ++i) {
			if( pick[id(i, 0)] || pick[id(i, 1)] )
				continue;
			vector<int> stk;
			if( dfsTry(id(i, 0), stk) )
				continue;
			for(auto v : stk)
				pick[v] = false;
			if( !dfsTry(id(i, 1), stk) )
				return false;
		}
		return true;
	}
	bool T(int i) {
		// should solve() first
		return pick[id(i, 1)];
	}
};

int main() {
	TwoSAT solver;
	int n, m;
	while( scanf("%d%d", &n, &m)!=EOF ) {
		if( n==0 && m==0 ) break;
		solver.init();
		vector<double> ages(n + 4);
		double ageSum = 0.0;
		for(int i=1; i<=n; ++i) {
			scanf("%lf", &ages[i]);
			ageSum += ages[i];
		}
		double ageAvg = ageSum / n;
		vector<int> old(n + 4);
		for(int i=1; i<=n; ++i)
			old[i] = fdif(ages[i]-ageAvg)>=0;
		for(int i=0,u,v; i<m; ++i) {
			scanf("%d%d", &u, &v);
			if( u==v ) continue;
			solver.addClause(0, u, 0, v);
			if( !(old[u] ^ old[v]) )
				solver.addClause(1, u, 1, v);
		}
		if( !solver.solve() )
			puts("No solution.");
		else {
			for(int i=1; i<=n; ++i)  {
				if( solver.T(i) ) puts("C");
				else puts(old[i]? "A" : "B");
			}
		}
	}
	return 0;
}
