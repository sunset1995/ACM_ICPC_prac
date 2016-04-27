#include <cstdio>
#include <cmath>
using namespace std;

struct point{
	double x,y;
	void rotate(double rad){
		double xn = x*cos(rad) - y*sin(rad);
		double yn = x*sin(rad) + y*cos(rad);
		x = xn;
		y = yn;
	}
};

int main(){
	int n , NCASE = 0;
	while( scanf(" %d",&n) && n ){
		double x1 , y1 , x2 , y2 , x3 , y3;
		scanf(" %lf%lf", &x1 , &y1);
		scanf(" %lf%lf", &x2 , &y2);
		scanf(" %lf%lf", &x3 , &y3);
		double a1 = (-2*x1 + 2*x2);
		double b1 = (-2*y1 + 2*y2);
		double c1 = (x2*x2 + y2*y2 - x1*x1 - y1*y1);
		double a2 = (-2*x1 + 2*x3);
		double b2 = (-2*y1 + 2*y3);
		double c2 = (x3*x3 + y3*y3 - x1*x1 - y1*y1);
		point center;
		center.x = (c1*b2-c2*b1) / (a1*b2-a2*b1);
		center.y = (a1*c2-a2*c1) / (a1*b2-a2*b1);
		point fP;
		fP.x = x1 - center.x;
		fP.y = y1 - center.y;

		double lm = fP.x ,
				 rm = fP.x ,
				 um = fP.y ,
				 bm = fP.y ;
		double rad = 2*acos(-1L)/n;
		for(int i=1;i<n;++i){
			fP.rotate( rad );
			if( fP.x < lm )
				lm = fP.x;
			else if( fP.x > rm )
				rm = fP.x;
			if( fP.y < bm )
				bm = fP.y;
			else if( fP.y > um )
				um = fP.y;
		}
		double recA = (rm-lm) * (um-bm);
		printf("Polygon %d: %.3lf\n",++NCASE,recA);
	}
}