#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

int fdif(const double &lf) {
	if( fabs(lf)<1e-8 ) return 0;
	return lf<0? -1 : 1;
}

struct Point {
	long long x, y;
	Point(long long x, long long y)
	:x(x), y(y) {}
	Point operator - (const Point &rth) const {
		return Point(x-rth.x, y-rth.y);
	}
};
typedef Point Vector;

long long cross(const Vector &p1, const Vector &p2) {
	return p1.x*p2.y - p1.y*p2.x;
}
long long dot(const Vector &p1, const Vector &p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

struct Circle {
	double cx, cy, R2;
	Circle() {}
	Circle(const Point &p1, const Point &p2) {
		cx = (p1.x+p2.x)/2.0;
		cy = (p1.y+p2.y)/2.0;
		R2 = dot(p1-p2, p1-p2)/4.0;
	}
	Circle(const Point &p1, const Point &p2, const Point &p3) {
		double x1 = (p1.x+p2.x)/2.0;
		double y1 = (p1.y+p2.y)/2.0;
		double x2 = (p2.x+p3.x)/2.0;
		double y2 = (p2.y+p3.y)/2.0;
		double vx = p2.x-p1.x;
		double vy = p2.y-p1.y;
		double ux = p3.x-p2.x;
		double uy = p3.y-p2.y;
		double A  = vx*x1 + vy*y1;
		double B  = ux*x2 + uy*y2;
		cx = (uy*A - vy*B) / (uy*vx - ux*vy);
		cy = (ux*A - vx*B) / (ux*vy - uy*vx);
		double dx = p1.x - cx;
		double dy = p1.y - cy;
		R2 = dx*dx + dy*dy;
	}
	bool contain(const Point &p) const {
		double dx = cx - p.x;
		double dy = cy - p.y;
		return fdif(dx*dx + dy*dy - R2)<=0;
	}
};

int main() {
	random_device rd;
	mt19937 g(rd());

	int n;
	while( scanf("%d", &n)!=EOF && n) {
		vector<Point> ps;
		for(int i=0,x,y; i<n; ++i) {
			scanf("%d%d", &x, &y);
			ps.emplace_back(Point(x, y));
		}
		if( ps.size()==1 ) {
			puts("0");
			return 0;
		}
		double R;
		scanf("%lf", &R);

		shuffle(ps.begin(), ps.end(), g);
		Circle D(ps[0], ps[1]);
		for(int i=2; i<ps.size(); ++i) {
			if( D.contain(ps[i]) )
				continue;
			D = Circle(ps[i], ps[0]);
			for(int j=1; j<i; ++j) {
				if( D.contain(ps[j]) )
					continue;
				D = Circle(ps[i], ps[j]);
				for(int k=0; k<j; ++k) {
					if( D.contain(ps[k]) )
						continue;
					D = Circle(ps[i], ps[j], ps[k]);
				}
			}
		}
		if( fdif(sqrt(D.R2)-R)<=0 )
			puts("The polygon can be packed in the circle.");
		else
			puts("There is no way of packing that polygon.");
	}
	return 0;
}
