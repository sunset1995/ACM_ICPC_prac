#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
	int x,y;
	Point(int x, int y)
	:x(x), y(y) {}
	Point operator - (const Point &rth) const {
		return Point(x-rth.x, y-rth.y);
	}
	bool operator < (const Point &rth) const {
		return x<rth.x || x==rth.x && y<rth.y;
	}
};
typedef Point Vector;

int crossSign(const Vector &l, const Vector &r) {
	int val = l.x*r.y - l.y*r.x;
	if( val<0 ) return -1;
	if( val>0 ) return 1;
	return 0;
}
int dot(const Vector &l, const Vector &r) {
	return l.x*r.x + l.y*r.y;
}

vector<Point> convexHull(vector<Point> &ps) {
	sort(ps.begin(), ps.end());
	vector<Point> btn, up;
	for(int i=0; i<ps.size(); ++i) {
		while( btn.size()>1
			&& crossSign(btn.back()-btn[btn.size()-2]
					,ps[i]-btn.back())<=0 )
			btn.pop_back();
		btn.emplace_back(ps[i]);
	}
	for(int i=ps.size()-1; i>=0; --i) {
		while( up.size()>1
			&& crossSign(up.back()-up[up.size()-2]
					,ps[i]-up.back())<=0 )
			up.pop_back();
		up.emplace_back(ps[i]);
	}
	vector<Point> cv = move(btn);
	for(int i=1; i<up.size()-1; ++i)
		cv.emplace_back(up[i]);
	return cv;
}
int lenSq(const Vector &v) {
	return v.x*v.x + v.y*v.y;
}
bool pointOnSeg(const Point &p, const Point &a1, const Point &a2) {
	return crossSign(p-a1, a2-a1)==0
			&& dot(p-a1, a2-a1)>=0
			&& lenSq(p-a1)<=lenSq(a2-a1);
}
bool segIntersect(const Point &a1, const Point &a2, const Point &b1, const Point &b2) {
	if( pointOnSeg(a1, b1, b2)
		|| pointOnSeg(a2, b1, b2)
		|| pointOnSeg(b1, a1, a2)
		|| pointOnSeg(b2, a1, a2) )
		return true;
	return crossSign(a2-a1, b1-a1)*crossSign(a2-a1, b2-a1)<0
		&& crossSign(b2-b1, a1-b1)*crossSign(b2-b1, a2-b1)<0;
}
double angle(const Vector &v, const Vector &u) {
	return acos(1.0*dot(v,u) / (sqrt(lenSq(v))*sqrt(lenSq(u))));
}
bool pointInPoly(const Point &p, const vector<Point> &poly) {
	static const double PI = 2.0*acos(-1.0);
	double sum = 0.0;
	for(int i=0; i<poly.size(); ++i)
		sum += angle(poly[i], poly[(i+1)%poly.size()]);
	return fabs(sum-PI) < 1e-9;
}
bool polyIntersect(const vector<Point> &a, const vector<Point> &b) {
	for(int i=0; i<a.size(); ++i)
		for(int j=0; j<b.size(); ++j)
			if( segIntersect(a[i], a[(i+1)%a.size()], b[j], b[(j+1)%b.size()]) )
				return true;
	return pointInPoly(a[0], b) || pointInPoly(b[0], a);
}

int main() {
	int K;
	scanf("%d", &K);
	while( K-- ) {
		int N;
		scanf("%d", &N);
		vector<Point> oo, xx;
		for(int i=0,x,y,type; i<N; ++i) {
			scanf("%d%d%d", &x, &y, &type);
			if( type==0 )
				oo.emplace_back(Point(x,y));
			else
				xx.emplace_back(Point(x,y));
		}
		oo = convexHull(oo);
		xx = convexHull(xx);
		if( polyIntersect(oo, xx) )
			puts("0");
		else
			puts("1");
	}
	return 0;
}
