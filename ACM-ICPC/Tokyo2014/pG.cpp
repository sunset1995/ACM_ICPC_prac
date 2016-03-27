#include <cstdio>
#include <algorithm>
using namespace std;

char str[300004];
int postfix[300004];

struct node {
	node *l=nullptr, *r=nullptr;
	int lb, rb;
	int tag=0, minV=0;
	node(){}
	node(const int &lb,const int &rb)
	:lb(lb), rb(rb){}
};
int minV(node *nd) {
	return nd->minV + nd->tag;
}
void push(node *nd) {
	if( nd->tag==0 || !nd->l ) return;
	nd->minV += nd->tag;
	nd->l->tag += nd->tag;
	nd->r->tag += nd->tag;
	nd->tag = 0;
}
void pull(node *nd) {
	if( !nd->l ) return;
	nd->minV = min(minV(nd->l), minV(nd->r));
}
void rangeUpd(node *nd,int val,int l,int r) {
	push(nd);
	if( nd->lb==l && nd->rb==r ) {
		nd->tag += val;
		return;
	}
	int mid = (nd->lb + nd->rb)>>1;
	if( r<=mid ) rangeUpd(nd->l, val, l, r);
	else if( l>mid ) rangeUpd(nd->r, val, l, r);
	else {
		rangeUpd(nd->l, val, l, mid);
		rangeUpd(nd->r, val, mid+1, r);
	}
	pull(nd);
}
int query2(node *nd) {
	push(nd);
	if( !nd->l ) return nd->lb;
	if( minV(nd->r)<0 ) return query2(nd->r);
	return query2(nd->l);
}

node mempool[900000], *memtop = mempool, *root;
node* build(int l,int r) {
	node *now = memtop;
	++memtop;
	*now = node(l, r);
	if( l==r ) {
		now->minV = postfix[l];
		return now;
	}
	int mid = (l+r)>>1;
	now->l = build(l, mid);
	now->r = build(mid+1, r);
	pull(now);
	return now;
}

int fenwick[300004];
void add(int id,int val) {
	while( id<=300000 ) {
		fenwick[id] += val;
		id += -id & id;
	}
}
int query(int id) {
	int sum = 0;
	while( id>0 ) {
		sum += fenwick[id];
		id -= -id & id;
	}
	return sum;
}

void turnRight(int id) {
	str[id] = '(';
	add(id, -1);
	rangeUpd(root, -2, 1, id);
}
void turnLeft(int id) {
	str[id] = ')';
	add(id, 1);
	rangeUpd(root, 2, 1, id);
}

int main() {
	int N, Q;
	scanf("%d%d%s", &N, &Q, str+1);
	for(int i=1 ; i<=N ; ++i)
		if( str[i]==')' )
			add(i, 1);
	for(int i=N ; i>0 ; --i) {
		postfix[i] = postfix[i+1];
		if( str[i]==')' ) ++postfix[i];
		else --postfix[i];
	}
	root = build(1, N);

	int id;
	while( Q-- ) {
		scanf("%d", &id);
		if( str[id]==')' ) {
			turnRight(id);
			int l = query2(mempool);
			printf("%d\n", l);
			turnLeft(l);
		}
		else {
			turnLeft(id);
			int l=1 , r=N;
			while( l<r ) {
				int c = (l+r)>>1;
				if( query(c)==0 ) l = c+1;
				else r = c;
			}
			printf("%d\n", l);
			turnRight(l);
		}
	}
	return 0;
}
