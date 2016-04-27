#include <cstdio>
#include <algorithm>
using namespace std;

int a[100004], top=-1;

int main() {
	int X;
	while( scanf("%d", &a[++top])!=EOF ) {
		for(int i=top; i>0; --i)
			if( a[i] < a[i-1] ) swap(a[i], a[i-1]);
		if( top&1 )
			printf("%d\n", ((long long)a[top>>1] + a[(top>>1)+1])>>1 );
		else
			printf("%d\n", a[top>>1]);
	}
	return 0;
}
