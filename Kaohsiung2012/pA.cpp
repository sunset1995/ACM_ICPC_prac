#include <cstdio>
#include <cstring>
using namespace std;

char ori[150];
int a[600];

inline int div2(int &len) {
	int r = 0;
	for(int i=0 ; i<len ; ++i) {
		int now = r*10 + ori[i];
		ori[i] =  now / 2;
		r = now % 2;
	}
	if( ori[0] == 0 ) {
		for(int i=0 ; i<len ; ++i)
			ori[i] = ori[i+1];
		--len;
	}
	return r;
}

int main() {
	while( scanf("%s",ori)!=EOF ) {
		if( ori[0]=='0' && ori[1]=='\0' ) break;
		int len = strlen(ori);
		for(int i=0 ; i<len ; ++i)
			ori[i] -= '0';

		int top = -1;
		while( len!=0 )
			a[++top] = div2(len);
		int anum = 0;
		for(int i=0 ; i<=top ; ++i)
			if( a[i]!=0 ) ++anum;

		for(int i=0 ; i<top ; ++i) {
			if( a[i]!=0 && a[i+1]!=0 ) {
				int j = i+1;
				while( j<=top && a[j]!=0 ) {
					a[j] = 0;
					++j;
				}
				a[j] = 1;
				if( j>top ) top = j;
			}
		}
		int bnum = 0;
		for(int i=0 ; i<=top ; ++i)
			if( a[i]!=0 ) ++bnum;

		printf("%d %d\n",anum,bnum);
	}
	return 0;
}
