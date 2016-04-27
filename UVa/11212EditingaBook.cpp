#include <cstdio>
#include <queue>
#include <set>
using namespace std;

const long long allOne = ~(0L);
struct stateDetail{
	long long state;
	int from;
};

void bitCut(long long &source,long long &cutted,const int &from,const int &len){
	cutted = ((allOne<<from) & source) >> from;
	long long tmp = ((allOne<<len) & cutted) >> len;
	cutted = ~(allOne<<len) & cutted;
	source = ~(allOne<<from) & source;
	source = (tmp<<from) | source;
}
void bitInsert(long long &source,long long &beInserted,const int &from,const int &len){
	long long tmp = ((allOne<<from) & source) << len;
	source = ~(allOne<<from) & source;
	source = tmp | source;
	source = (beInserted<<from) | source;
}
long long makeNewState(long long result,int cutFrom,int cutLen,int insertTo){
	long long tmp = 0L;
	bitCut( result , tmp , cutFrom , cutLen );
	if( cutFrom < insertTo )
		bitInsert( result , tmp , insertTo-cutLen , cutLen );
	else
		bitInsert( result , tmp , insertTo , cutLen );
	return result;
}

int main(){
	int n , NOWCASE = 0;
	while( scanf(" %d",&n)!=EOF && n ){
		long long nowState = 0L;
		long long ansState = 0L;
		for(int i=0,tmp;i<n;++i){
			scanf(" %d",&tmp);
			nowState <<= 4;
			nowState |= (long long)tmp;
			ansState <<= 4;
			ansState |= (long long)i+1;
		}
		int len[2] = { 0 , 0 };
		set<long long> s[2];
		queue<stateDetail> myQ;
		s[0].insert( nowState );
		s[1].insert( ansState );
		myQ.push( (stateDetail){ nowState , 0 } );
		myQ.push( (stateDetail){ ansState , 1 } );
		int nowFrom = 0;
		bool ansFound = (nowState==ansState);
		while( !ansFound ){
			stateDetail tmp = myQ.front();
			myQ.pop();
			if( nowFrom != tmp.from ){
				nowFrom = tmp.from;
				++len[nowFrom^1];
			}
			for(int i=0 ; i<n && !ansFound ; ++i)
				for(int j=1 ; i+j-1<n && !ansFound ; ++j)
					for(int k=i+j+1 ; k<=n && !ansFound ; ++k){
							long long nState = makeNewState( tmp.state , i*4 , j*4 , k*4 );
							if( s[ nowFrom^1 ].find( nState ) != s[ nowFrom^1 ].end() ){
								++len[nowFrom];
								ansFound = true;
							}
							if( s[ nowFrom ].find( nState )==s[nowFrom].end() ){
								myQ.push( (stateDetail){ nState , nowFrom } );
								s[ nowFrom ].insert( nState );
							}
						}
		}
		printf("Case %d: %d\n",++NOWCASE,len[0]+len[1]);
	}
}
