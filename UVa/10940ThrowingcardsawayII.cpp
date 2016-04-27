#include<cstdio>
using namespace std;
int main(){
	int n;
	while( scanf(" %d",&n)!=EOF && n ){
		if( n==1 ){
			printf("1\n");
			continue;
		}
		int ans = 2, gap = 2;
		bool odd = n&1 , last = !odd;
		n/=2;
		odd = n&1;
		while( n>1 ){
			if( last ) ans += gap;
			gap *= 2;
			
			bool pOdd = odd , pLast = last;
			if( pOdd^pLast ) last = true;
			else last = false;
			if( pOdd & !pLast ) n = (n+1)/2;
			else n /= 2;
			odd = n&1;
		}
		printf("%d\n",ans);
	}
} 
