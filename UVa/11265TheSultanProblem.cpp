#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


struct point{
	double x,y;
	double m;
	int type;
	point(const double &_x,const double &_y,const double &_m,const int &_type)
	:x(_x) , y(_y) , m(_m) , type(_type){}
	point(const double &_x,const double &_y)
	:x(_x) , y(_y) , m(0.0L) , type(0){}
	point operator-(const point& rth) const{
		return point(x-rth.x , y-rth.y);
	}
};
struct event{
	int x,y,type;
};
vector<point> btn , btnAll;
vector<point> up , upAll;
vector<event> e;

bool myCmp(const point &l,const point &r){
	return (l.x < r.x) || (l.x == r.x && l.y < r.y);
}
void init(){
	btn.clear(); btn.reserve(512);
	btnAll.clear(); btnAll.reserve(512);
	up.clear(); up.reserve(512);
	upAll.clear(); upAll.reserve(512);
	e.clear(); e.reserve(1024);
}

bool ccw(const point &p1,const point &p2,const point &p3){
	point v1 = p2-p1;
	point v2 = p3-p2;
	return (v1.x*v2.y - v1.y*v2.x)>0.0L;
}
point xx(const point &p1,const point &p2){
	double x = (p1.y - p2.y)/(p1.x - p2.x);
	double y = p1.x * x - p1.y;
	return point( x , y );
}
void findBtnChain(){
	sort( btnAll.begin() , btnAll.end() , myCmp );
	for(int i=0 ; i<btnAll.size() ; ++i){
		if( !btn.empty() && btn.back().x == btnAll[i].x )
			continue;
		while( btn.size()>1u &&
					!ccw( btn[btn.size()-1] , btn[btn.size()-2] , btnAll[i] ) )
			btn.pop_back();
		btn.push_back( btnAll[i] );
	}
}
void findUpChain(){
	sort( upAll.begin() , upAll.end() , myCmp );
	for(int i=upAll.size()-1 ; i>=0 ; --i){
		if( !up.empty() && up.back().x==upAll[i].x )
			continue;
		while( up.size()>1u &&
					!ccw( btn[btn.size()-1] , btn[btn.size()-2] , upAll[i] ) )
			up.pop_back();
		up.push_back( upAll[i] );
	}
}
bool eCmp(const event &l,const event &r){
	return (l.x < r.x) || (l.x == r.x && l.y < r.y); 
}
void collectEvent(vector<point> &seg,int type){
	for(int i=1;i<seg.size();++i){
		point tmp = xx(seg[i-1],seg[i]);
		e.push_back( (event){tmp.x , tmp.y , type} );
	}
}

int main(){
	int N,W,H,x,y , CASECNT = 0;
	while( scanf(" %d%d%d%d%d",&N,&W,&H,&x,&y)!=EOF ){
		init();
		int lB = 0 , rB = W;
		for(int i=0,x1,x2,y1,y2;i<N;++i){
			scanf(" %d%d%d%d",&x1,&y1,&x2,&y2);
			if( x1==x2 ){
				if( x1<x ) lB = x1;
				else rB = x1;
				continue;
			}
			double a = (y2-y1) / (x2-x1);
			double b = a*x1 - y1;
			if( a*x-b > y )
				btnAll.push_back( point(a,b) );
			else
				upAll.push_back( point(a,b) );
		}
		findBtnChain();
		findUpChain();
		collectEvent(btn,0);
		collectEvent(up,1);
		e.push_back( (event){lB , 0 , 3} );
		e.push_back( (event){rB , 0 , 3} );
		sort(e.begin() , e.end() , eCmp);
		sort(btn.begin() , btn.end() , myCmp);
		sort(up.begin() , up.end() , myCmp);

		int eid = 0 , upid = 0 , btnid = 0;
		double btnH = 0.0L , upH = 0.0L;
		double ans = 0.0L;
		double lastX = 0.0L;
		point tmpxx = xx(up[0],btn[0]);
		while( eid<e.size() ){
			if( e[eid].type==3 ){
				double y1 = up[upid].x * e[eid].x - up[upid].y;
				double y2 = btn[btnid].x * e[eid].x - btn[btnid].y;
				btnH = upH = (y1>y2)? y1-y2 : y2-y1;
				lastX = e[eid].x;
				++eid;
				continue;
			}
			if( tmpxx.x>lastX && tmpxx.x<e[eid].x ){
				upH = btnH = 0.0L;
				lastX = tmpxx.x;
			}
			if( e[eid].type==0 ){
				btnH = e[eid].y - (up[upid].x * e[eid].x - up[upid].y);
				if( btnH<0.0L ) btnH = 0.0L;
				++btnid;
			}
			else{
				upH = (btn[btnid].x * e[eid].x - btn[btnid].y) - e[eid].y;
				if( upH<0.0L ) upH = 0.0L;
				++upid;
			}
			tmpxx = xx(up[upid] , btn[btnid]);
			printf("%lf %lf\n",upH,btnH);
			ans += (upH + btnH) * (e[eid].x - lastX) / 2;
			lastX = e[eid].x;
			++eid;
		}
		printf("Case #%d: %.3lf\n" , ++CASECNT , ans);
	}
}