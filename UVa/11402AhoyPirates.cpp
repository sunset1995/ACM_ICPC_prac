#include <cstdio>
#include <vector>
using namespace std;

struct node{
	int cnt;
	bool toggle , allOne;
	node(){ cnt=0; toggle=allOne=false; }
	node(int num){ cnt=num; toggle=allOne=false; }
};
vector< vector<node> > seg;
vector<node> empty;


char buffer[100];
void readData(){
	seg.clear();
	seg.reserve(20);
	int M;
	scanf(" %d",&M);
	seg.push_back( empty );
	seg[0].reserve( 1<<20 );
	while( M-- ){
		int T;
		scanf(" %d%s",&T,buffer);
		while( T-- )
			for(int i=0 ; buffer[i]!='\0' ; ++i)
				seg[0].push_back( buffer[i]-'0' );
	}
}
void makeTree(){
	int id = 0;
	while( seg[id].size() > 1 ){
		if( seg[id].size() & 1 )
			seg[id].push_back( node() );
		seg.push_back( empty );
		seg[id+1].reserve( 1<<(19-id) );
		for(int i=1;i<seg[id].size();i+=2)
			seg[id+1].push_back( seg[id][i].cnt + seg[id][i-1].cnt );
		++id;
	}
}

void findBorder(const int &h,const int &s,int &lb,int &rb,int &m){
	lb = s<<h;
	rb = lb + (1<<h) - 1;
	m = (lb+rb)/2;
}
void push(const int &h,const int &s){
	node &now = seg[h][s];
	if( now.toggle && now.allOne ){
		now.cnt = 0;
		if( h>0 ){
			seg[h-1][s*2].toggle = seg[h-1][s*2+1].toggle = true;
			seg[h-1][s*2].allOne = seg[h-1][s*2+1].allOne = true;
		}
	}
	else if( now.toggle ){
		now.cnt = (1<<h) - now.cnt;
		if( h>0 ){
			seg[h-1][s*2].toggle ^= true;
			seg[h-1][s*2+1].toggle ^= true;
		}	
	}
	else if( now.allOne ){
		now.cnt = 1<<h;
		if( h>0 ){
			seg[h-1][s*2].toggle = seg[h-1][s*2+1].toggle = false;
			seg[h-1][s*2].allOne = seg[h-1][s*2+1].allOne = true;
		}	
	}
	now.toggle = now.allOne = false;
}
void pull(const int &h,const int &s){
	if( h<1 ) return;
	push(h-1,s*2);
	push(h-1,s*2+1);
	seg[h][s].cnt = seg[h-1][s*2].cnt + seg[h-1][s*2+1].cnt;
}

void setOne(const int &h,const int &s){
	seg[h][s].toggle = false;
	seg[h][s].allOne = true;
}
void setZero(const int &h,const int &s){
	seg[h][s].toggle = true;
	seg[h][s].allOne = true;
}
void setToggle(const int &h,const int &s){
	seg[h][s].toggle ^= true;
}
void setSeg(const int &h,const int &s,
				const int &from,const int &to,void (*proc)(const int&,const int&)){
	push(h,s);
	int lb,rb,m;
	findBorder( h,s,lb,rb,m );

	if( from==lb && to==rb ){
		proc(h,s);
		return;
	}

	if( to<=m )
		setSeg(h-1,s*2,from,to,proc);
	else if( from>m )
		setSeg(h-1,s*2+1,from,to,proc);
	else{
		setSeg(h-1,s*2,from,m,proc);
		setSeg(h-1,s*2+1,m+1,to,proc);
	}
	pull(h,s);
}
int query(const int &h,const int &s,const int &from,const int &to){
	push(h,s);
	int lb,rb,m;
	findBorder( h,s,lb,rb,m );

	if( from==lb && to==rb )
		return seg[h][s].cnt;

	if( to<=m )
		return query(h-1,s*2,from,to);
	else if( from>m )
		return query(h-1,s*2+1,from,to);
	else
		return query(h-1,s*2,from,m) + query(h-1,s*2+1,m+1,to);
}

int main(){
	int T,NCASE = 0;
	scanf(" %d",&T);
	while( T-- ){
		readData();
		makeTree();

		int Q;
		scanf(" %d",&Q);
		printf("Case %d:\n",++NCASE);
		int NQ = 0;
		while( Q-- ){
			char c;
			int a,b;
			scanf(" %c%d%d",&c,&a,&b);
			switch( c ){
				case 'F':
					setSeg(seg.size()-1,0,a,b,setOne);
					break;
				case 'E':
					setSeg(seg.size()-1,0,a,b,setZero);
					break;
				case 'I':
					setSeg(seg.size()-1,0,a,b,setToggle);
					break;
				case 'S':
					printf("Q%d: ",++NQ);
					int ans = query(seg.size()-1,0,a,b);
					printf("%d\n",ans);
					break;
			}
		}
	}
}