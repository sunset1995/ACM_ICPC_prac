#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

struct treap;
struct node {
	int f=0, sz;
	treap *t;
	vector<int> next;
};
node nd[100004];

struct treap {
	int sz=1, pri;
	int node_id, inOrderId;
	treap *l=nullptr, *r=nullptr, *f=nullptr;
	treap(){}
	treap(int node_id)
	:pri(rand()), node_id(node_id){}
};
inline int sz(treap *t) {
	return t? t->sz : 0;
}
inline void updateF(treap *t,treap *f) {
	if( t ) t->f = f;
}
inline void pull(treap *t) {
	t->sz = sz(t->l) + sz(t->r) + 1;
	updateF(a->l, a);
	updateF(a->r, a);
}
treap* merge(treap *a, treap *b) {
	if( !a || !b ) return a? a : b;
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
void split(treap *t, int k, treap *&a, treap *&b) {
	if( !t ) {
		a = b = nullptr;
		return;
	}
	if( sz(t->l) < k ) {
		a = t;
		split(t->r, k-sz(t->l)-1, a->r, b);
		pull(a);
	}
	else {
		b = t;
		split(t->l, k, a, b->l);
		pull(b);
	}
}

treap mempool[100004], *memtop, *root;
void insert(int node_id) {
	*memtop = treap();
	root = merge(root, memtop);
	++memtop;
}

int findPreOrderId(treap *t) {
	int id = 1;
	while( t->f != nullptr ) {
		if( t->f->r == t ) id += 1 + sz(t->f->l);
		t = t->f;
	}
	return id;
}
void preOrderBuildTreap(int nowAt,int f) {
	nd[nowAt].f = f;
	nd[nowAt].sz = 1;
	nd[nowAt].t = memtop;
	insert(nowAt);
	for(auto &n : nd[nowAt].next) {
		preOrderBuildTreap(n);
		nd[nowAt].sz += nd[n].sz;
	}
}

void init() {
	for(int i=0 ; i<=100000 ; ++i) {
		nd[i].f = 0;
		nd[i].next.clear();
	}
	memtop = mempool;
	root = nullptr;
}

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		init();
		int N;
		scanf("%d",&N);
		for(int i=1,x,y ; i<N ; ++i) {
			scanf("%d%d",&x,&y);
			nd[x].next.emplace_back(y);
			nd[y].f = x;
		}
		preOrderBuildTreap(1);
		int Q, q, u, v;
		scanf("%d",&Q);
		while( Q-- ) {
			scanf("%d",&q);
			if( q==1 ) {
				scanf("%d%d",&u,&v);
				instructMove(u, v);
			}
			else {
				scanf("%d",&u);
				printf("%d\n",instructFind(u));
			}
		}
	}
	return 0;
}
