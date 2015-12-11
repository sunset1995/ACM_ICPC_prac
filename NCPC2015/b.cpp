#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
#define vv first
#define data second

struct node {
	char op;
	int lf, le, lv;
	int rf, re, rv;
	node(){}
	node(const char &op,
		  const int &lf,const int &le,const int &lv,
		  const int &rf,const int &re,const int &rv)
	:op(op),
	 lf(lf), le(le), lv(lv),
	 rf(rf), re(re), rv(rv){}
};

typedef map<int,node> mp;
typedef map<int,node>::iterator mit;
int p, a[20], res;
char op[20];
mp dp[20][20];

void mul(mp &a, mp &b, mp &c) {
	for(mit it1=a.begin() ; it1!=a.end() ; ++it1)
		for(mit it2=b.begin() ; it2!=b.end() ; ++it2) 
			c[ it1->vv * it2->vv %p ] = 
				node('*',
					it1->data.lf, it1->data.re, it1->vv,
					it2->data.lf, it2->data.re, it2->vv);
}
void del(mp &a, mp &b, mp &c) {
	for(mit it1=a.begin() ; it1!=a.end() ; ++it1)
		for(mit it2=b.begin() ; it2!=b.end() ; ++it2)
			c[ (it1->vv - it2->vv +p) %p ] = 
				node('-',
					it1->data.lf, it1->data.re, it1->vv,
					it2->data.lf, it2->data.re, it2->vv);
}
void add(mp &a, mp &b, mp &c) {
	for(mit it1=a.begin() ; it1!=a.end() ; ++it1)
		for(mit it2=b.begin() ; it2!=b.end() ; ++it2)
			c[ (it1->vv + it2->vv) %p ] = 
				node('+',
					it1->data.lf, it1->data.re, it1->vv,
					it2->data.lf, it2->data.re, it2->vv);
}
void dfs(const node &nowAt) {
	if( nowAt.op == '~' ) {
		printf("%d",a[nowAt.lf]);
		return;
	}
	putchar('(');
	dfs(dp[nowAt.lf][nowAt.le][nowAt.lv]);
	putchar(nowAt.op);
	dfs(dp[nowAt.rf][nowAt.re][nowAt.rv]);
	putchar(')');
}

int main() {
	int n;
	scanf("%d%d",&n,&p);
	while( n-- ) {
		for(int i=0 ; i<16 ; ++i)
			for(int j=0 ; j<16 ; ++j)
				dp[i][j].clear();
		int id=0;
		while( scanf("%d",&a[id])!=EOF ) {
			scanf(" %c",&op[id]);
			if( op[id]=='=' ) {
				scanf("%d",&res);
				break;
			}
			++id;
		}
		for(int i=0 ; i<=id ; ++i)
			dp[i][i][ a[i]%p ] = node('~',i,i,i,i,i,i);
		for(int len=1 ; len<=id ; ++len) {
			for(int i=0 ; i+len<=id ; ++i) {
				int j = i+len;
				for(int k=i ; k<j ; ++k) {
					switch(op[k]) {
						case '+':
							add(dp[i][k],dp[k+1][j],dp[i][j]);
							break;
						case '-':
							del(dp[i][k],dp[k+1][j],dp[i][j]);
							break;
						default:
							mul(dp[i][k],dp[k+1][j],dp[i][j]);
					}
				}
			}
		}
		if( dp[0][id].find(res) != dp[0][id].end() ) {
			dfs(dp[0][id][res]);
			printf("=%d\n",res);
		}
		else puts("0");
	}
	return 0;
}
