#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct node{
	node(){
		cntOne = cntAll = 0;
		toggle = allOne = false;
		lb = rb = 0;
		l = r = NULL;
	}
	node(int ith){
		cntOne = 0;
		cntAll = 0;
		toggle = allOne = false;
		lb = ith*64;
		rb = lb+63;
		l = r = NULL;
	}
	node(node &lC,node &rC){
		cntOne = lC.cntOne + rC.cntOne;
		cntAll = lC.cntAll + rC.cntAll;
		toggle = allOne = false;
		lb = lC.lb;
		rb = (rC.rb)? rC.rb : lC.rb;
		l = &lC;
		r = &rC;
	}
	int cntOne , cntAll;
	bool toggle , allOne;
	int lb,rb;
	node *l , *r;
};

vector<long long> pirates;
vector<node> seg;
node *Root;

int cntLLOne(const long long &rth);
int getCntOne(const node &rth);

char buffer[100];
void readData();

void makeSegTree();

void opOne(int,int,node&);
void opZero(int,int,node&);
void opToggle(int,int,node&);

void passOp(node *from,node *to);
void push(node *now);

void pull(node *now);

int deepth;
void goSegTree(node *now,int from,int to,void (*proc)(int,int,node&));

int qq(node *now,int from,int to);

int main(){
	int T,NCASE=0;
	scanf(" %d",&T);
	while( T-- ){
		seg.clear();
		pirates.clear();
		readData();
		makeSegTree();

		int Q;
		scanf(" %d",&Q);
		printf("Case %d:\n",++NCASE);
		int NQ = 0;
		while( Q-- ){
			char c;
			int a,b;
			scanf(" %c%d%d",&c,&a,&b);
			if( a>b ) a^=b , b^=a , a^=b;
			deepth = 0;
			switch( c ){
				case 'F':
					goSegTree(Root,a,b,opOne);
					break;
				case 'E':
					goSegTree(Root,a,b,opZero);
					break;
				case 'I':
					goSegTree(Root,a,b,opToggle);
					break;
				case 'S':
					printf("Q%d: ",++NQ);
					int ans = qq(Root,a,b);
					printf("%d\n",ans);
					break;
			}
		}
	}
}


int cntLLOne(const long long &rth){
	long long mask = 1LL;
	int cnt = 0;
	while( mask ){
		if( rth & mask )
			++cnt;
		mask <<= 1;
	}
	return cnt;
}
int getCntOne(const node &rth){
	if( rth.allOne && rth.toggle )
		return 0;
	if( rth.allOne )
		return rth.cntAll;
	if( rth.toggle )
		return rth.cntAll - rth.cntOne;
	return rth.cntOne;
}
void readData(){
	pirates.clear();
	seg.clear();
	int M;
	scanf(" %d",&M);
	int cnt = 64;
	while( M-- ){
		int T;
		scanf(" %d%s",&T,buffer);
		int len = strlen(buffer);
		while( T-- ){
			for(int i=0;i<len;++i,++cnt){
				if( cnt==64 ){
					pirates.push_back( 0LL );
					seg.push_back( node(seg.size()) );
					cnt = 0;
				}
				pirates.back() <<= 1;
				seg.back().cntAll += 1;
				if( buffer[i]=='1' ){
					pirates.back() |= 1LL;
					seg.back().cntOne += 1;	
				}
			}
		}
	}
}

void makeSegTree(){
	int id = 0 , nowNum = seg.size();
	while( nowNum>1 ){
		if( nowNum&1 )
			seg.push_back( node() );
		int nextNum = 0;
		for(int i=0 ; i<nowNum ; i+=2 , id+=2 ,++nextNum)
			seg.push_back( node(seg[id],seg[id+1]) );
		nowNum = nextNum;
	}
	Root = &(seg.back());
}

void passOp(node *from,node *to){
	if( to==NULL ) return;
	if( from->allOne && from->toggle )
		to->allOne = to->toggle = true;
	else if( from->toggle )
		to->toggle ^= true;
	else if( from->allOne )
		to->allOne = true , to->toggle = false;
}
void push(node *now){
	if( now->l==NULL && now->r==NULL ){
		int id = now->lb / 64;
		if( id >= pirates.size() )
			return;
		if( now->allOne && now->toggle )
			pirates[id] = 0LL;
		else if( now->toggle )
			pirates[id] ^= ~(0LL);
		else if( now->allOne )
			pirates[id] = ~(0LL);
		now->cntOne = cntLLOne(pirates[id]);
		now->toggle = now->allOne = false;
		return;
	}

	if( now->allOne && now->toggle )
		now->cntOne = 0;
	else if( now->toggle )
		now->cntOne = now->cntAll - now->cntOne;
	else if( now->allOne )
		now->cntOne = now->cntAll;
	passOp(now,now->l);
	passOp(now,now->r);
	now->toggle = now->allOne = false;
}

void pull(node *now){
	now->cntOne = getCntOne( *(now->l) ) + getCntOne( *(now->r) );
}
void goSegTree(node *now,int from,int to,void (*proc)(int,int,node&)){
	if( ++deepth>50 ) return;
	push( now );

	if( (from == now->lb && to == now->rb)
		|| (now->l==NULL && now->r==NULL) ){
		proc( from , to , *now );
		return;
	}

	if( to <= now->l->rb )
		goSegTree( now->l , from , to , proc );
	else if( from >= now->r->lb )
		goSegTree( now->r , from , to , proc );
	else{
		goSegTree( now->l , from , now->l->rb , proc );
		goSegTree( now->r , now->r->lb , to , proc );
	}

	pull( now );
}

int qq(node *now,int from,int to){
	if( ++deepth>50 ) return 0;
	push( now );

	if( from == now->lb && to == now->rb ){
		return now->cntOne;
	}
	else if( now->l==NULL && now->r==NULL ){
		from -= now->lb;
		to -= now->lb;
		int id = now->lb / 64;
		int cnt = 0;
		for(int i=from;i<=to;++i)
			if( pirates[id] & (1LL<<(now->cntAll-1-i)) )
				++cnt;
		return cnt;
	}
	if( to <= now->l->rb )
		return qq( now->l , from , to );
	else if( from >= now->r->lb )
		return qq( now->r , from , to );
	else{
		return qq( now->l , from , now->l->rb )
				+qq( now->r , now->r->lb , to );
	}
}

void opOne(int from,int to,node &who){
	if( &who==NULL )
		return;
	if( who.l==NULL && who.r==NULL ){
		from -= who.lb;
		to -= who.lb;
		int id = who.lb / 64;
		if( id>=pirates.size() )
			return;
		for(int i=from;i<=to;++i)
			pirates[ id ] |= (1LL<<(who.cntAll-1-i));
		who.cntOne = cntLLOne( pirates[id] );
	}
	else{
		who.toggle = false;
		who.allOne = true;
	}
}

void opZero(int from,int to,node &who){
	if( &who==NULL )
		return;
	if( who.l==NULL && who.r==NULL ){
		from -= who.lb;
		to -= who.lb;
		int id = who.lb / 64;
		if( id>=pirates.size() )
			return;
		for(int i=from;i<=to;++i)
			pirates[ id ] &= (~(1LL<<(who.cntAll-1-i) ));
		who.cntOne = cntLLOne( pirates[id] );
	}
	else{
		who.toggle = true;
		who.allOne = true;
	}
}

void opToggle(int from,int to,node &who){
	if( &who==NULL )
		return;
	if( who.l==NULL && who.r==NULL ){
		from -= who.lb;
		to -= who.lb;
		int id = who.lb / 64;
		if( id>=pirates.size() )
			return;
		for(int i=from;i<=to;++i)
			pirates[ id ] ^= (1LL<<(who.cntAll-1-i) );
		who.cntOne = cntLLOne( pirates[id] );
	}
	else{
		who.toggle ^= 1;
	}
}