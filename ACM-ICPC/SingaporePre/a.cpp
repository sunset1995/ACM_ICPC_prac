#include <cstdio>
#include <cmath>
using namespace std;

int main(){
	long long m , n;
	int t;
	scanf("%lld%lld%d",&m,&n,&t);
	long long cnt = 1LL;
	switch(t){
		case 1:
			while( n && cnt<=m ){
				cnt = cnt*n;
				--n;
			}
			break;
		case 2:
			while( n && cnt<=m ){
				cnt <<= 1;
				--n;
			}
			break;
		case 3:
			for(int i=0 ; i<4 && cnt<=m ; ++i)
				cnt = cnt*n;
			break;
		case 4:
			for(int i=0 ; i<3 && cnt<=m ; ++i)
				cnt = cnt*n;
			break;
		case 5:
			cnt = n*n;
			break;
		case 6:
			cnt = ceil(n*log2(n));
			break;
		default:
			cnt = n;
			break;
	}
	if( cnt<=m ) printf("AC");
	else printf("TLE");
	return 0;
}