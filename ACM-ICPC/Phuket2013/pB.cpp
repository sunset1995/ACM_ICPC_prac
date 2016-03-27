#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

bool notPrime[100004];
int from[100004];
void global_init(){
	for(int i=2; i<=100000 ; ++i){
		if( notPrime[i] ) continue;
		from[i] = i;
		for(int j=i+i ; j<=100000 ; j+=i){
			notPrime[j] = true;
			from[j] = i;
		}
	}
}

int fac[100004];

void init(){
	memset(fac , 0 , sizeof(fac));
}

int main(){
	global_init();

	int n,x;
	while( scanf("%d%d",&n,&x)!=EOF ){
		if( n==0 && x==0 ) break;
		init();
		for(int i=2 ; i<=n ; ++i){
			int j = i;
			while( j>1 ){
				++fac[ from[j] ];
				j /= from[j];
			}
		}
		for(int i=2 ; i<=100000 ; ++i)
			if( fac[i] )
				printf("%d^%d ",i,fac[i]);
		puts("");
	}
	return 0;
}
