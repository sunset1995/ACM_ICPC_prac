#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int maxNum = 204;
const int infinite = 0x3FFFFFFF;

char word[maxNum][14] , buffer[50];
int top;
int sP[maxNum][maxNum];
vector<int> g[maxNum];

void init(){
	for(int i=0;i<maxNum;++i){
		g[i].clear();
		for(int j=0;j<maxNum;++j)
			sP[i][j] = infinite;
	}
	top = -1;
}
bool difOne(char *a,char *b){
	int id = 0 , dif = 0;
	while( a[id]!='\0' && b[id]!='\0' && dif<2 ){
		if( a[id]!=b[id] )
			++dif;
		++id;
	}
	return ( a[id]=='\0' && b[id]=='\0' && dif==1 );
}
void makeG(){
	for(int i=0;i<top;++i)
		if( difOne( word[i] , word[top] ) ){
			g[i].push_back( top );
			g[top].push_back( i );
		}
}
void shortestPath(){
	// top was '*'
	for(int i=0;i<top;++i){
		queue<int> myQ;
		myQ.push(i);
		sP[i][i] = 0;
		while( ! myQ.empty() ){
			int nowAt = myQ.front();
			myQ.pop();
			for(vector<int>::iterator it=g[nowAt].begin() ; it!=g[nowAt].end() ; ++it)
				if( sP[i][ (*it) ]==infinite ){
					sP[i][ (*it) ] = sP[i][nowAt] + 1;
					myQ.push( (*it) );
				}
		}
	}
}
int findWordId(char *toFind){
	for(int i=0;i<top;++i)
		if( strcmp( toFind , word[i] )==0 )
			return i;
	return top;
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	fgets( buffer , 40 , stdin );
	fgets( buffer , 40 , stdin );
	while( NCASE-- ){
		init();
		while( true ){
			fgets( word[++top] , 14 , stdin );
			word[top][ strlen(word[top])-1 ] = '\0';
			if( findWordId( word[top] )!=top ){
				--top;
				continue;
			}
			if( word[top][0]=='*' )
				break;
			makeG();
		}

		shortestPath();

		while( true ){
			if( fgets( buffer , 50 , stdin )==NULL || buffer[0]=='\n' )
				break;
			char word1[14] , word2[14];
			sscanf(buffer," %s%s",word1,word2);
			int ans = sP[ findWordId(word1) ][ findWordId(word2) ];
			if( ans==infinite )
				printf("%s %s -1\n",word1,word2);
			else
				printf("%s %s %d\n",word1,word2,ans);
		}
		if( NCASE )
			printf("\n");
	}
}