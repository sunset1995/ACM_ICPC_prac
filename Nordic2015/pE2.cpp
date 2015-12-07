#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct tt {
	int s, e;
	bool operator < (const tt &rth) const {
		return e < rth.e || 
			   e == rth.e && s < rth.s;
	}
};

struct node {
	node *l, *r;
	int key, pri, sz;
	node(){}
	node(int k) {
		l = r = NULL;
		key = k;
		pri = rand();
		sz = 1;
	}
};
int sz(node *nd) {
	return nd? nd->sz : 0;
}
void pull(node *nd) {
	if( !nd ) return;
	nd->sz = sz(nd->l) + sz(nd->r) + 1;
}
node* merge(node *a,node *b) {
	if( !a || !b ) return a? a: b;
	if( a->pri > b->pri ) {
		a->r = merge(a->r, b);
		pull(a);
		return a;
	}
	else {
		b->l = merge(a, b->l);
		pull(b);
		return b;
	}
}
void split(node *t,int k,node *&a,node *&b) {
	if( !t ) {
		a = b = NULL;
		return;
	}
	if( t->key <= k ) {
		a = t;
		split(t->r, k, a->r, b);
		pull(a);
	}
	else {
		b = t;
		split(t->l, k, a, b->l);
		pull(b);
	}
}

node mempool[400004], *memtop = mempool, *root = NULL;
void insert(int k) {
	node *now = memtop;
	++memtop;
	*now = node(k);
	node *a, *b;
	split(root, k, a, b);
	root = merge( merge(a,now), b );
}
int querySz(int k) {
	node *a, *b;
	split(root, k, a, b);
	int res = sz(b);
	root = merge(a, b);
	return res;
}

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	vector<tt> es;
	for(int i=0,s,e ; i<n ; ++i) {
		scanf("%d%d",&s,&e);
		es.push_back({s,e});
	}
	sort(es.begin(), es.end());
	int ans = 0;
	for(int i=0 ; i<es.size() ; ++i) {
		if( es[i].e == 94 )
			printf("%d %d %d\n",es[i].s,es[i].e,querySz(es[i].s));
		if( querySz(es[i].s) <= k-1 ) {
			++ans;
			insert(es[i].e);

			printf("%4d %4d",es[i].s,es[i].e);
			printf(" Y");
			puts("");
		}
	}
	printf("%d\n",ans);
	return 0;
}
