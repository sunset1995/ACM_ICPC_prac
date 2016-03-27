#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
	int x,y;
	Point(){}
	Point(int x, int y): x(x), y(y) {}
	Point operator - (const Point &rth) const {
		return Point(x-rth.x, y-rth.y);
	}
	bool operator < (const Point &rth) const {
		return x < rth.x
			|| x == rth.x && y < rth.y;
	}
	bool operator == (const Point &rth) const {
		return x==rth.x && y==rth.x;
	}
};
typedef Point Vector;

inline bool turnLeft(const Vector &v1, const Vector &v2) {
	return (long long)v1.x * v2.y
			- (long long)v1.y * v2.x > 0LL;
}
inline long long area(const Point &p1,const Point &p2,const Point &p3) {
	Vector v1 = p2-p1, v2 = p3-p1;
	long long a = (long long)v1.x * v2.y
				- (long long)v1.y * v2.x;
	return (a<0LL)? -a : a;
}

vector<Point> convexHull(vector<Point> &ps) {
	sort(ps.begin(), ps.end());
	vector<Point> up;
	for(int i=0; i<ps.size(); ++i) {
		while( up.size()>1
			&& !turnLeft(up.back()-up[up.size()-2],
				ps[i]-up.back()) )
			up.pop_back();
		up.emplace_back(ps[i]);
	}
	vector<Point> btn;
	for(int i=ps.size()-1; i>=0; --i) {
		while( btn.size()>1
			&& !turnLeft(btn.back()-btn[btn.size()-2],
				ps[i]-btn.back()) )
			btn.pop_back();
		btn.emplace_back(ps[i]);
	}
	vector<Point> res(up);
	res.insert(res.end(), btn.begin()+1, btn.end());
	res.pop_back();
	return res;
}

long long findAnsx2(const vector<Point> &ps) {
	long long res = area(ps[0], ps[1], ps[2])
				+ area(ps[0], ps[2], ps[3]);
	for(int p1=0; p1<ps.size()-3; ++p1) {
		int p2 = p1+1, p4 = p1+3;
		for(int p3=p1+2; p3<ps.size()-1; ++p3) {
			while( p2<p3-1
				&& area(ps[p1], ps[p2+1], ps[p3])
				>  area(ps[p1], ps[p2], ps[p3]) )
				++p2;
			while( p4<ps.size()-1
				&& area(ps[p1], ps[p3], ps[p4+1])
				>  area(ps[p1], ps[p3], ps[p4]) )
				++p4;
			res = max(res, 
				area(ps[p1], ps[p2], ps[p3])
				+area(ps[p1], ps[p3], ps[p4]));
		}
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int n;
		scanf("%d", &n);
		vector<Point> ps;
		for(int i=0,x,y; i<n; ++i) {
			scanf("%d%d", &x, &y);
			ps.emplace_back(Point(x, y));
		}
		ps = convexHull(ps);
		printf("%.1f\n", findAnsx2(ps)/2.0);
	}
	return 0;
}
