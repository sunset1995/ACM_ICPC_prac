#include <cstdio>
using namespace std;

bool strstr(const char *a,const char *b){
	while( *a != '\0' ){
		if( *a != *b )
			return false;
		++a , ++b;	
	}
	return true;
}

char str[2][104];
char *last , *now;
int main(){
	int n;
	scanf(" %d",&n);
	while( n-- ){
		int k,w;
		scanf(" %d%d",&k,&w);
		int ans = k*w;
		scanf(" %s",str[w&1]);
		last = str[w&1];
		while( --w ){
			scanf(" %s",str[w&1]);
			now = str[w&1];
			for(int i=0;last[i]!='\0';++i){
				if( strstr( &last[i] , now ) ){
					ans -= k-i;
					break;
				}
			}
			last = now;
		}
		printf("%d\n",ans);
	}
}