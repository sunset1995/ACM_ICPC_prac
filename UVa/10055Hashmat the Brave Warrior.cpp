#include<cstdio>
using namespace std;
int main(){
	long long a,b,ans;
	while( scanf(" %lld%lld",&a,&b)!=EOF ){
		ans = ( a>b )? a-b : b-a;
		printf("%lld\n",ans);
	}
}
