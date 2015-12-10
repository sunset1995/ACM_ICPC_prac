#include <cstdio>
using namespace std;

bool ok(int *dig,int v) {
	if( v==0 ) return dig[0];
	int need[10] = {};
	while( v ) {
		++need[v%10];
		v /= 10;
	}
	for(int i=0 ; i<10 ; ++i)
		if( need[i]>dig[i] ) return false;
	return true;
}

int main() {
	int n;
	scanf("%d",&n);
	while( n-- ) {
		int a[10]={}, b[10]={};
		for(int i=0,v ; i<6 ; ++i) {
			scanf("%d",&v);
			++a[v];
		}
		for(int i=0,v ; i<6 ; ++i) {
			scanf("%d",&v);
			++b[v];
		}
		int apoint = 0, bpoint = 0;
		for(int i=0 ; i<1000000 ; ++i) {
			bool aok = ok(a,i), bok = ok(b,i);
			if( aok && !bok ) ++apoint;
			if( !aok && bok ) ++bpoint;
		}
		printf("%d %d\n",apoint,bpoint);
	}
	return 0;
}
