#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int r,s[500];
	scanf(" %d",&r);
	do{
		int n;
		scanf(" %d",&n);
		for(int i=0;i<n;++i) scanf(" %d",&s[i]);
		sort( s , s+n );
		
		int my = n/2 , total = 0;
		for(int i=0;i<my;++i)
			total += s[my] - s[i];
		for(int i=my+1;i<n;++i)
			total += s[i] - s[my];
		
		printf("%d\n",total);
	}while( --r );
} 
