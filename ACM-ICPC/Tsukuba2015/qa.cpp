#include <cstdio>
using namespace std;

int a[400];

int main(){
	int m,nmin,nmax;
	while( scanf(" %d%d%d",&m,&nmin,&nmax)!=EOF ){
		if( m==0 && nmin==0 && nmax==0 )
			break;
		for(int i=1;i<=m;++i)
			scanf(" %d",&a[i]);
		int maxGap = nmin;
		for(int i=nmin+1;i<=nmax ;++i)
			if( a[i]!=a[i+1] && a[i]-a[i+1] >= a[maxGap]-a[maxGap+1] )
				maxGap = i;
		printf("%d\n",maxGap);
	}
}