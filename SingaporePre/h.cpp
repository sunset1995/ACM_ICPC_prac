#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <queue>
using namespace std;

inline long long strToLL(const char *str){
	long long re = 0LL;
	for(int i=0 ; str[i]!='\0' ; ++i){
		re *= 10LL;
		re += str[i]-'0';
	}
	return re;
}

struct node{
	long long id;
	int score;
	vector<int> next;
	int inE = 0;
	node(){}
	node(const int &_id):id(_id){}
};
vector<node> g;

int main(){
	int N,M,D;
	scanf("%d%d%d",&N,&M,&D);

	map< long long , int > hs;
	char tmp[15];
	for(int i=0 ; i<M ; ++i){
		long long aid , bid;
		scanf("%s",tmp); aid = strToLL(tmp);
		scanf("%s",tmp); bid = strToLL(tmp);

		if( hs.find(aid)==hs.end() ){
			g.emplace_back( node(aid) );
			hs[aid] = g.size() - 1;
		}
		if( hs.find(bid)==hs.end() ){
			g.emplace_back( node(bid) );
			hs[bid] = g.size() - 1;
		}

		int ra = hs[aid] , rb = hs[bid];
		g[ra].next.emplace_back( rb );
		++g[rb].inE;
	}

	queue<int> myQ;
	for(int i=0 ; i<g.size() ; ++i)
		if( g[i].inE == 0 ){
			myQ.push( i );
			break;
		}
	int nowScore = 0;
	while( !myQ.empty() ){
		int nowAt = myQ.front();
		myQ.pop();
		g[nowAt].score = ++nowScore;
		for(auto &nid : g[nowAt].next)
			if( --g[nid].inE == 0 )
				myQ.push( nid );
	}

	vector<int> len;
	for(int i=0 ; i<N ; ++i){
		scanf("%s",tmp);
		long long nowID = strToLL(tmp);
		if( hs.find(nowID)==hs.end() ) continue;

		int nowRank = g[ hs[nowID] ].score;
		auto it = lower_bound(len.begin() , len.end() , nowRank);
		if( it==len.end()  ) len.emplace_back( nowRank );
		else *it = min(*it , nowRank);
	}
	int tlen = len.size();
	printf("%d\n",(N-tlen)*2);
	return 0;
}