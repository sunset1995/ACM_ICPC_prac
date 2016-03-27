#include <cstdio>
using namespace std;

const long long modNum = 1000000007LL;
long long fac[504];

long long fastPow(long long x,int n){
	long long res = 1LL;
	while( n ){
		if( n&1 ) res = res*x % modNum;
		x = x*x % modNum;
		n >>= 1;
	}
	return res;
}
long long modInv(long long x){
	return fastPow(x , modNum-2);
}
long long C(int n,int m){
	return fac[n] * modInv(fac[m]) %modNum * modInv(fac[n-m]) %modNum;
}

void globalInit(){
	fac[0] = fac[1] = 1LL;
	for(int i=2 ; i<504 ; ++i)
		fac[i] = fac[i-1] * i % modNum;
}

int main(){
	globalInit();
	int T;
	scanf("%d",&T);
	for(int NCASE = 1 ; NCASE<=T ; ++NCASE){
		int N , K , p;
		scanf("%d%d%d",&N,&K,&p);
		long long ans = C(N-1 , N-K) * fac[K-1] %modNum;
		for(int i=K+1 ; i<N ; ++i){
			long long tmp = C(N-1 , i-K);
			if( p-1 >= i-K )
				tmp = (tmp+modNum- C(p-1 , i-K)) %modNum;
			ans = ans + tmp*fac[N-i+K-1] %modNum;
			ans %= modNum;
		}
		printf("Case #%d: %lld\n",NCASE , ans);
	}
}