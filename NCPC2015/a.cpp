#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

int f2i(double lf) {
	if( fabs(lf)<1e-6 ) return 0;
	else return (int)lf;
}

int main() {
	int K;
	scanf("%d",&K);
	while( K-- ) {
		double a,b,c;
		double x1,y1,x2,y2,x3,y3;
		scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
		double A = y1-y2;
		double B = x1*x1 - x2*x2;
		double C = x1-x2;
		double D = y2-y3;
		double E = x2*x2 - x3*x3;
		double F = x2-x3;
		
		a = (C*D - A*F) / (C*E - B*F);
		b = (A - a*B) / C;
		c = y1 - a*x1*x1 - b*x1;
		printf("%d %d %d\n",f2i(a),f2i(b),f2i(c));
	}
	return 0;
}
