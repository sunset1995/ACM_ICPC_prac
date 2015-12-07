#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#define N 20010
using namespace std;
struct option {
	char c ;
	int u , v ;
	option(char c_,int a,int b):c(c_),u(a),v(b){}
} ;
int father[N] , f[N] ;
int use[N] , st[N] ;
int find(int u) {
	if(u==f[u]) return u ;
	return f[u] = find(f[u]) ;
}
void Union(int u,int v) {
	int fu=find(u) , fv=find(v) ;
	if(fu!=fv)
		f[fu] = fv ;
}
int main () {
	int t , kase=1 ;
	scanf("%d",&t) ;
	while(t--) {
		int n , q , i , v , u ;
		vector<option> op ;
		scanf("%d%d",&n,&q) ;
		memset(use,-1,sizeof(use)) ;
		memset(st,-1,sizeof(st)) ;
		f[0] = 0;
		for(i=1 ; i<=n ; i++) {
			scanf("%d",&father[i]) ;
			f[i] = i ;
		}
		char s[5] ;
		for(i=0 ; i<q ; i++) {
			//puts("FFFFF") ;
			scanf(" %s",s) ;
			if(s[0]=='C') {
				scanf("%d",&v) ;
				if(st[v]==-1) {
					use[v] = 0 ;
					op.push_back(option{'C',v,father[v]}) ;
					st[v] = 0 ;
				}
			} else {
				scanf("%d%d",&u,&v) ;
				op.push_back(option{'Q',u,v}) ;
			}
		}
		//puts("AAAAA") ;
		//fflush(stdout);
		for(i=1 ; i<=n ; i++)
			if(use[i]==-1 && father[i]!=0)
				Union(i,father[i]) ;
		//puts("AAAAA") ;
		//fflush(stdout);
		vector<int> ans ;
		for(i=op.size()-1 ; i>=0 ; i--) {
			if(op[i].c=='C') {
				if(op[i].u!=0 && op[i].v!=0)
					Union(op[i].u,op[i].v) ;
			} else
				ans.push_back(find(op[i].u)==find(op[i].v)) ;
		}
		//puts("AAAAA") ;
		//fflush(stdout);
		printf("Case #%d:\n",kase++) ;
		for(i=ans.size()-1 ; i>=0 ; i--)
			puts(ans[i] ? "YES" : "NO") ;
	}
}