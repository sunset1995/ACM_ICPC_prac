/* it would be TLE */
#include<stdio.h>

int min(int a,int b){
	return (a<b)? a:b;
}
int DandC(long long from){
	if( from==1LL )
		return 1;
	if( (from&1LL)==0 )
		return DandC(from>>1) +1;
	
	return min( DandC(from+1LL), DandC(from-1LL) )+1;
}
int main(){
	long long S;
	while( scanf(" %lld",&S)!=EOF ){
		int operation = DandC(S);
		printf("%d\n",operation);
	}
}
