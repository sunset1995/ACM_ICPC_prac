#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	Point(int x, int y)
	:x(x), y(y) {}
};
struct Rect {
	int u, r, b, l;
	Rect(int u, int r, int b, int l)
	:u(u), r(r), b(b), l(l) {}
};
struct Event {
	int id, t, outT, type;
	Event(int id, int t, int outT, int type)
	:id(id), t(t), outT(outT), type(type) {}
};

typedef vector<Point> Points;
typedef vector<Rect>  Rects;
typedef vector<Event> Events;

bool pointInRect(const Point &p, const Rect &rect) {
	return p.x<=rect.r && p.x>=rect.l
		&& p.y<=rect.u && p.y>=rect.b;
}

vector<int> findTag(const Points &route, const Rect &rect) {
	vector<int> tag;
	int recU = rect.u;
	int recR = rect.r;
	int recB = rect.b;
	int recL = rect.l;
	int t = 0;
	if( pointInRect(route[0], rect) )
		tag.emplace_back(0);
	for(int j=1; j<route.size(); ++j) {
		int lastX = route[j-1].x;
		int lastY = route[j-1].y;
		int nowX  = route[j].x;
		int nowY  = route[j].y;
		bool inX  = (nowX >= recL && nowX <= recR);
		bool inY  = (nowY <= recU && nowY >= recB);
		if( nowX > lastX ) {
			// go right
			if( inY && 
				lastX < recL &&
				nowX >= recL ) // goin
				tag.emplace_back(t+recL-lastX);
			if( inY &&
				lastX <= recR &&
				nowX  >  recR ) // goout
				tag.emplace_back(t+recR-lastX);
			t += nowX - lastX;
		}
		else if( nowX < lastX ) {
			// left
			if( inY	&&
				lastX > recR &&
				nowX <= recR ) // goin
				tag.emplace_back(t+lastX-recR);
			if( inY &&
				lastX >= recL &&
				nowX  <  recL ) // goout
				tag.emplace_back(t+lastX-recL);
			t += lastX - nowX;
		}
		else if( nowY > lastY ) {
			// up
			if( inX &&
				lastY < recB &&
				nowY >= recB ) // goin
				tag.emplace_back(t+recB-lastY);
			if( inX &&
				lastY <= recU &&
				nowY  >  recU )
				tag.emplace_back(t+recU-lastY);
			t += nowY - lastY;
		}
		else {
			// down
			if( inX &&
				lastY > recU &&
				nowY <= recU ) // goin
				tag.emplace_back(t+lastY-recU);
			if( inX &&
				lastY >= recB &&
				nowY  <  recB )
				tag.emplace_back(t+lastY-recB);
			t += lastY - nowY;
		}
	}
	if( tag.size()%2 == 1 )
		tag.emplace_back(t);
	return tag;
}

Events buildEvent(const Rects &recs, const Points &route) {
	Events es;
	for(int i=0; i<recs.size(); ++i) {
		vector<int> tag = findTag(route, recs[i]);
		for(int j=1; j<tag.size(); j+=2) {
			es.emplace_back(Event(i,tag[j-1],tag[j],1));
			es.emplace_back(Event(i,tag[j]  ,tag[j],0));
		}
	}
	sort(es.begin(), es.end(), [](const Event &l, const Event &r) {
		return l.t < r.t ||
			l.t == r.t && l.type >  r.type ||
			l.t == r.t && l.type == r.type && l.outT > r.outT;
	});
	return es;
}

int main() {
	int n, m;
	while( scanf("%d%d", &n, &m)!=EOF ) {
		if( !n && !m ) break;
		vector<Rect> territory;
		for(int i=0,x,y,k; i<n; ++i) {
			scanf("%d%d%d", &x, &y, &k);
			territory.emplace_back(Rect(y+k,x+k,y,x));
		}
		vector<Point> route;
		for(int i=0,x,y; i<m; ++i) {
			scanf("%d%d", &x, &y);
			route.emplace_back(Point(x,y));
		}
		vector<Event> es = buildEvent(territory, route);
		int ans=0;
		int nowId=-1, nowoutT=-1;
		int maxId=-1, maxoutT=-1;
		for(const auto &e : es) {
			if( e.type == 1 ) {
				if( e.outT > maxoutT ) {
					maxId   = e.id;
					maxoutT = e.outT;
				}
				if( e.t > nowoutT ) {
					++ans;
					nowId   = maxId;
					nowoutT = maxoutT;
				}
			}
			else {
				if( e.id == nowId && maxoutT > nowoutT ) {
					++ans;
					nowId   = maxId;
					nowoutT = maxoutT;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
