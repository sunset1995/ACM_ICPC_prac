#include<cstdio>
using namespace std;
int main(){
	unsigned int n;
	while( scanf(" %u",&n)!=EOF && n ){
		int ans = n;
		do{
			n = ans;
			ans = 0;
			while( n!=0 ){
				ans += n%10;
				n/=10;
			} 
		}while( ans>9 );
		printf("%d\n",ans);
	}
}
