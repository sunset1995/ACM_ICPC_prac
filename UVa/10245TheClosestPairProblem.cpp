#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int fdif(const double &lf) {
	if( fabs(lf)<1e-9 ) return 0;
	return lf<0? -1 : 1;
}

struct Point {
	double x, y;
};

double len(const Point &l, const Point &r) {
	double difx = l.x - r.x;
	double dify = l.y - r.y;
	return sqrt(difx*difx + dify*dify);
}

double cloestDis(vector<Point> &ps, int l, int r) {
	if( r-l <= 0 ) return 1e10;
	int m  = (l+r) / 2;
	int mX = ps[m].x;
	double lAns = cloestDis(ps, l, m);
	double rAns = cloestDis(ps, m+1, r);
	double ret  = min(lAns, rAns);
	vector<Point> tmp(r-l+1);
	merge(
		ps.begin()+l, ps.begin()+m+1,
		ps.begin()+m+1, ps.begin()+r+1, tmp.begin(),
		[](const Point &l, const Point &r) {
			return l.y < r.y;
		});
	copy(tmp.begin(), tmp.end(), ps.begin()+l);
	int id = -1;
	for(int i=l; i<=r; ++i)
		if( fdif(fabs(ps[i].x-mX) - ret) <= 0 )
			tmp[++id] = ps[i];
	for(int i=0; i<=id; ++i)
	for(int j=1; j<=8 && i+j<=id; ++j)
		ret = min(ret, len(tmp[i], tmp[i+j]));
	return ret;
}
double cloestDis(vector<Point> &ps) {
	sort(ps.begin(), ps.end(), [](const Point &l, const Point &r) {
		return l.x < r.x;
	});
	return cloestDis(ps, 0, ps.size()-1);
}

int main() {
	int N;
	while( scanf("%d", &N)!=EOF && N ) {
		vector<Point> ps;
		for(int i=0; i<N; ++i) {
			double x, y;
			scanf("%lf%lf", &x, &y);
			ps.push_back({x,y});
		}
		double ans = cloestDis(ps);
		if( fdif(ans-10000.0)<0 )
			printf("%.4f\n", ans);
		else puts("INFINITY");
	}
	return 0;
}
