#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

int n;
struct Point{
	double x,y;
	Point(int _x=0,int _y=0){
		x = _x , y = _y;
	}
	Point operator - (const Point &r) const{
		return Point( x-r.x , y-r.y );
	}
} ps[24] , op[24];
typedef Point Vector;

Point operator + (const Point &p,const Vector &v){
	return Point(p.x+v.x , p.y+v.y);
}
Point operator * (const Point &p,double scale){
	return Point(p.x*scale , p.y*scale);
}
Point midPoint(const Point &l,const Point &r){
	return Vector( (l.x+r.x)/2 , (l.y+r.y)/2 );
}
Vector dot0(const Vector &v){
	return Vector( v.y , -v.x );
}
double len(const Vector &v){
	return sqrt( v.x*v.x + v.y*v.y );
}
double cross(const Vector &l,const Vector &r){
	return l.x*r.y - l.y*r.x;
}
double dot(const Vector &l,const Vector &r){
	return l.x*r.x + l.y*r.y;
}

struct Line{
	Point P0;
	Vector v;
	Line(){}
	Line(const Point &a,const Point &b){
		P0 = a;
		v = b-a;
	}
};

Point projectToLine(const Line &L,const Point &Q){
  double t = dot(Q-L.P0 , L.v) / dot(L.v , L.v);
  return L.P0 + L.v * t;
}
Point lineIntersect(const Line &L1,const Line &L2){
	Vector u = L1.P0 - L2.P0;
	double t1 = cross(L2.v , u) / cross(L1.v , L2.v);
	return L1.P0 + L1.v*t1;
}
Point mirrowPoint(const Line &L,const Point &Q){
	return Point(Q + (projectToLine(L,Q)-Q)*2.0 );
}
bool haveIntersect(const Point &a,const Point &b,const Point &c,const Point &d){
	bool diff1 = (cross(b-a , c-a)*cross(b-a , d-a)) < 0;
	bool diff2 = (cross(d-c , a-c)*cross(d-c , b-c)) < 0;
	return diff1 && diff2;
}
bool onLine(const Line &L,const Point &p){
	return fabs( cross(L.v , p-L.P0) ) < 1e-9;
}

struct ans{
	int nPoint;
	double perimeter;
	bool operator > (const ans &r) const{
		if( nPoint > r.nPoint ) return true;
		else if( nPoint < r.nPoint ) return false;
		else return perimeter > r.perimeter;
	}
};

double cntPerimeter(Point *a,int n){
	double length = len( a[0]-a[n-1] );
	for(int i=1;i<n;++i)
		length += len( a[i]-a[i-1] );
	return length;
}

struct e{
	int type;
	Point p;
};

ans fold(int aid,int bid){
	Line pivot;
	pivot.P0 = midPoint(ps[aid] , ps[bid]);
	pivot.v = dot0( ps[aid]-ps[bid] );
	vector<e> initP;
	int mirrow = 0;
	for(int i=0;i<n;++i){
		if( mirrow )
			initP.push_back( (e){1,mirrowPoint(pivot,ps[i])} );
		else
			initP.push_back( (e){1,ps[i]} );
		double judge = cross(pivot.v , ps[i]-pivot.P0) * cross(pivot.v , ps[(i+1)%n]-pivot.P0);
		if( judge < 0 ){
			initP.push_back( (e){2,lineIntersect(pivot , Line(ps[i] , ps[(i+1)%n]))} );
			mirrow = (mirrow+1)%2;	
		}
	}
	vector<e> poly;
	for(int i=0;i<initP.size();++i){
		poly.push_back( initP[i] );
		for(int j=i+2;j<initP.size();++j)
			if( haveIntersect(
				initP[i].p , initP[(i+1)%initP.size()].p ,
				initP[j].p , initP[(j+1)%initP.size()].p
			) ){
				poly.push_back( (e){3,
					lineIntersect(
						Line(initP[i].p , initP[(i+1)%initP.size()].p),
						Line(initP[j].p , initP[(j+1)%initP.size()].p)
					)
				} );
			}
		for(int j=0;j<i-1;++j)
			if( haveIntersect(
				initP[i].p , initP[(i+1)%initP.size()].p ,
				initP[j].p , initP[(j+1)%initP.size()].p
			) ){
				poly.push_back( (e){3,
					lineIntersect(
						Line(initP[i].p , initP[(i+1)%initP.size()].p),
						Line(initP[j].p , initP[(j+1)%initP.size()].p)
					)
				} );
			}
	}

	ans nowAns;
	vector<Point> pivotP;
	for(int i=0;i<poly.size();++i)
		if( onLine(pivot,poly[i].p) )
			pivotP.push_back(poly[i].p);
	for(int i=1;i<poly.size();++i)
		nowAns.perimeter += len(pivotP[i]-pivotP[i-1]);
	bool on = true;
	for(int i=0;i<poly.size();++i){
		if( poly[i].type!=1 )
			on = !on;
		if( on ){
			nowAns.perimeter += len( poly[(i+1)%poly.size()].p - poly[i].p );
			nowAns.nPoint++;
		}
	}
	return nowAns;
}

int main(){
	while( scanf(" %d",&n)!=EOF && n ){
		for(int i=0;i<n;++i)
			scanf(" %lf%lf",&ps[i].x,&ps[i].y);
		ans best;
		for(int i=0;i<n;++i)
			for(int j=i+1;j<n;++j){
				ans now = fold(i,j);
				if( now > best )
					best = now;
			}
		printf("%.6f\n",best.perimeter);
	}
}