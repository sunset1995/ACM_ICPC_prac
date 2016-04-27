#include<cstdio>
#include<cstring>
using namespace std;
int abs( int a ){
	if( a<0 ) return -1*a;
	return a;
}
int main(){
	int n;
	bool in[3000];
	while( scanf(" %d",&n)!=EOF ){
		memset( in , false , sizeof(in) );
		int last;
		scanf(" %d",&last);
		bool jolly = true;
		for(int i=1;i<n;++i){
			int now;
			scanf(" %d",&now);
			if( !jolly ) continue;
			int which = abs( now-last );
			if( in[which] || which>=n ) jolly = false;
			else in[which] = true;
			last = now;
		}
		if( jolly ) printf("Jolly\n");
		else printf("Not jolly\n");
	}
}
