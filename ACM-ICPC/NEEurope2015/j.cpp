#include <cstdio>
#include <vector>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

int n;
char str[1504];
int same[1504];

inline void flip(int id) {
	if( str[id]=='1' ) str[id]='0';
	else str[id] = '1';
}
inline bool start(int v) {
	for(int i=0; i<n; ++i) {
		if( v==1 )
			flip(i);
		if( !same[i] )
			v = (v+1)%2;
	}
}
inline void half_test(int last) {
	if( last<1 ) return;
	int res;
	for(int i=1; i<n; ++i) {
		flip(i-1);
		flip(i);

		if( last==0 ) return;
		puts(str); --last;
		fflush(stdout);
		scanf("%d", &res);
		if( res==n )
			return;
		else if( res==0 )
			same[i-1] = 1;
		else
			same[i-1] = 0;

		flip(i-1);
		flip(i);
	}
	start(0);
	if( last==0 ) return;
	puts(str); --last;
	fflush(stdout);
	start(0);
	scanf("%d", &res);
	if( res==n ) return;
	start(1);
	if( last==0 ) return;
	puts(str);
	fflush(stdout);
}

int main() {
	srand(time(NULL));
	scanf("%d", &n);
	str[n] = '\0';
	int last = n+500;
	int res;
	while( last>0 ) {
		for(int i=0; i<n; ++i)
			str[i] = (rand()&1) + '0';
		puts(str); --last;
		fflush(stdout);
		scanf("%d", &res);
		if( res==n ) break;
		if( res==0 ) {
			// no!! let random try again
		}
		else {
			half_test(last);
			break;
		}
	}
	return 0;
}
