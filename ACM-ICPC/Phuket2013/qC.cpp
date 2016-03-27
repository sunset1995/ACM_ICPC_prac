#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	long long n,m;
	while( scanf("%lld%lld",&n,&m)!=EOF ){
		if( n==0 && m==0 ) break;
		long long x = min(n , m);
		if( x%2==0 )
			x /= 2 ;
		else
			x = (x+1)/2 ;
		long long a , b , c , d;
		a = x * (-m*n-2*m-2*n-4 ) ;
		b = (x+1)*x/2 * (2*n*m+6*m+6*n+16) ;
		c = x*(x+1)*(2*x+1)/6 * (-4*m-4*n-20) ;
		d = ((x+1)*x/2)*((x+1)*x/2) * 8 ;
		printf("%lld\n",a+b+c+d) ;
	}
	return 0;
}
