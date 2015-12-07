#include <iostream>
#include <cmath>
#include <cstdio>	
using namespace std;	
int main () {
	int t ;
	scanf("%d",&t) ;
	while(t--) {
		int n , i , ans=0 , p ;
		double x , y , d , s ;
		scanf("%d",&n) ;
		for(i=0 ; i<n ; i++) {
			scanf("%lf%lf",&x,&y) ;
			d = sqrt(x*x + y*y)/20. ;
			p = d ;
			s = p ;
			if(!(fabs(d-s)<1e-6))
				p ++ ;
			if(p==0) p++ ;
			//printf("%d\n",11-p) ;
			ans += max(11-p,0) ;
		}
		printf("%d\n",ans) ;
	}
}