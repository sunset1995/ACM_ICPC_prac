#include <iostream>
#include <cstdio>
#define N 20
using namespace std;
int yee(int str[],int q[],int n,int m,int v,int odd,int even,int one,int zero) {
	int i , sum=0 , where=0 , j=0 ;
	if(v==1 && (even!=one || odd!=zero))
		return 1e9 ;
	if(v==0 && (even!=zero || odd!=one))
		return 1e9 ;
	for(i=0 ; i<n && j<m; i++)
		if(str[i] == v) {
			q[j]-- ;
			//printf("%d ",str[i]) ;
			sum += abs(i-where) ;
			where ++ ;
			if(q[j]==0) {
				j += 2 ;
				where += q[j-1] ;
			}
		}
	//printf("\n") ;
	if(j>=m)
		return sum ;
	else
		return 1e9 ;
}
int main () {
	int n , m ;
	while(scanf("%d%d",&n,&m)==2) {
		int str[N] , q[N] , p[N] , i , odd=0 , even=0 , one=0 , zero=0 ;
		for(i=0 ; i<n ; i++) {
			scanf("%d",&str[i]) ;
			one += str[i]==1 ;
			zero += str[i]==0 ;
		}
		for(i=0 ; i<m ; i++) {
			scanf("%d",&q[i]) ;
			if(i%2) odd += q[i] ;
			else even += q[i] ;
			p[i] = q[i] ;
		}
		printf("%d\n",min(yee(str,q,n,m,1,odd,even,one,zero),yee(str,p,n,m,0,odd,even,one,zero))) ;
	}
}
