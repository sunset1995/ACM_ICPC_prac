#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,long long> PIL;

struct event{
	int x , top , btn , diff;
	event(int _x , int _top , int _btn , int _diff)
	:x(_x) , top(_top) , btn(_btn) , diff(_diff) {}
	bool operator < (const event &rth) const{
		return x < rth.x || (x == rth.x && diff < rth.diff);
	}
};

struct node{
	node *l = nullptr , *r = nullptr;
	int lb , rb;
	bool tag = false;
	int diff = 0 , lastX;
	int maxS = 0 , maxN;
	long long sumX = 0LL;
	node(){}
	node(const int &_lb,const int &_rb)
	:lb(_lb) , rb(_rb){
		maxN = _rb - _lb + 1;
	}
};

inline void push(node *nd){
	if( !nd->tag ) return;
	nd->maxS += nd->diff;
	nd->sumX = 1LL * nd->maxN * nd->lastX;
	if( nd->l ){
		nd->l->diff += nd->diff;
		nd->l->lastX = nd->lastX;
		nd->l->tag = true;
		nd->r->diff += nd->diff;
		nd->r->lastX = nd->lastX;
		nd->r->tag = true;
	}
	nd->diff = 0;
	nd->tag = false;
}
inline void pull(node *nd){
	if( !nd->l ) return;
	push(nd->l);
	push(nd->r);
	nd->maxS = max( nd->l->maxS , nd->r->maxS );
	nd->maxN = nd->sumX = 0LL;
	if( nd->l->maxS == nd->maxS )
		nd->maxN += nd->l->maxN , nd->sumX += nd->l->sumX;
	if( nd->r->maxS == nd->maxS )
		nd->maxN += nd->r->maxN , nd->sumX += nd->r->sumX;
}

PIL query(node *nd,int tl,int tr , int X){
	push(nd);
	if( tl==nd->lb && tr==nd->rb ){
		return {nd->maxS , 1LL* nd->maxN*X - nd->sumX};
	}
	int mid = (nd->lb + nd->rb)>>1;
	if( tr<=mid )
		return query(nd->l , tl,tr , X);
	if( tl >mid )
		return query(nd->r , tl,tr , X);
	PIL tmp1 = query(nd->l , tl,mid , X);
	PIL tmp2 = query(nd->r , mid+1,tr , X);
	if( tmp1.first > tmp2.first ) return tmp1;
	if( tmp2.first > tmp1.first ) return tmp2;
	return {tmp1.first , tmp1.second + tmp2.second};
}
void rangeOP(node *nd,int tl,int tr , int diff , int X){
	push(nd);
	if( tl==nd->lb && tr==nd->rb ){
		nd->diff += diff;
		nd->lastX = X;
		nd->tag = true;
		return;
	}
	int mid = (nd->lb + nd->rb)>>1;
	if( tr<=mid ){
		rangeOP(nd->l , tl,tr , diff,X);
	}
	else if( tl >mid ){
		rangeOP(nd->r , tl,tr , diff,X);
	}
	else{
		rangeOP(nd->l , tl,mid , diff,X);
		rangeOP(nd->r , mid+1,tr , diff,X);
	}
	pull(nd);
}

node mem[4100000] , *memtop;
node* build(int l,int r){
	*memtop = node(l,r);
	node *now = memtop++;
	if( l==r ) return now;
	int mid = (l+r)>>1;
	now->l = build(l , mid);
	now->r = build(mid+1 , r);
	return now;
}

inline void init(){
	node *i = mem;
	while( i!=memtop ){
		i->tag = false;
		i->maxS = i->diff = 0;
		i->maxN = i->rb - i->lb + 1;
		i->sumX = 0LL;
		++i;
	}
}

int main(){
	memtop = mem;
	build(0 , 2000004);

	int C;
	scanf("%d",&C);
	while( C-- ){
		int n;
		scanf("%d",&n);
		vector< event > es;
		for(int i=0 , x1,y1,x2,y2,s ; i<n ; ++i){
			scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&s);
			x1 += 1000000 , x2 += 1000000;
			y1 += 1000000 , y2 += 1000000;
			es.emplace_back( event(x1,y2,y1+1, s) );
			es.emplace_back( event(x2,y2,y1+1,-s) );
		}
		sort( es.begin() , es.end() );
		long long maxSig = 0LL , maxArea = 0LL;
		for(auto &v : es){
			if( v.diff > 0 )
				rangeOP(mem , v.btn,v.top , v.diff , v.x);
			else{
				PIL qq = query(mem , v.btn,v.top , v.x);
				if( qq.first == maxSig )
					maxArea += qq.second;
				else if( qq.first > maxSig ){
					maxSig = qq.first;
					maxArea = qq.second;
				}
				rangeOP(mem , v.btn,v.top , v.diff , v.x);
			}
		}
		printf("%lld %lld\n",maxSig , maxArea);

		if( C ){
			init();
		}
	}
}