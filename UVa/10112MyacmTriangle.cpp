#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

struct point{
	char name;
	int x,y;
	point operator-(const point &rth) const{
		point np;
		np.x = x-rth.x , np.y = y-rth.y;
		return np;
	}
} p[20];

double areaTriangle(point &p1,point &p2,point &p3){
	point v1 = p2-p1 , v2 = p3-p1;
	return fabs( (double)v1.x*v2.y - v1.y*v2.x )/2;
}
bool inTriangle(point &p1,point &p2,point &p3,point &pp){
	double Atri = areaTriangle( p1,p2,p3 );
	double A1 = areaTriangle( p1,p2,pp );
	double A2 = areaTriangle( p1,p3,pp );
	double A3 = areaTriangle( p2,p3,pp );
	return ( A1+A2+A3-Atri ) < 1e-9L;
}

int main(){
	int n;
	while( scanf(" %d",&n)!=EOF && n ){
		for(int i=0;i<n;++i)
			scanf(" %c%d%d",&p[i].name , &p[i].x , &p[i].y);
		double maxArea = 0L;
		int a=0,b=0,c=0;
		for(int i=n-1;i>1;--i)
			for(int j=i-1;j>0;--j)
				for(int k=j-1;k>=0;--k){
					double nowArea = areaTriangle(p[i],p[j],p[k]);
					if( nowArea < maxArea )
						continue;
					bool insideOk = true;
					for(int g=0;g<n && insideOk;++g){
						if( g==i || g==j || g==k ) continue;
						if( inTriangle(p[i],p[j],p[k],p[g]) )
							insideOk = false;
					}
					if( !insideOk )
						continue;
					a = k , b = j , c = i;
					maxArea = nowArea;
				}
		printf("%c%c%c\n",p[a].name , p[b].name , p[c].name);
	}
}