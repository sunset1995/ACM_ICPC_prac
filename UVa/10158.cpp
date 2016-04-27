#include <stdio.h>

const int maxNum = 10005;
class relationTree{
	public:
		bool setFriend(int,int);
		bool setEnemy(int,int);
		int areFrined(int,int);
		int areEnemy(int,int);
		relationTree(int n){
			for(int i=0;i<n;++i)
				root[i] = i , len[i] = 0;
		}
	private:
		void findRoot(int);
		int num[maxNum];
		int root[maxNum];
		bool len[maxNum];
};
void relationTree::findRoot(int who){
	if( root[who]!=who ){
		int oriRoot = root[who];
		findRoot( oriRoot );
		root[who] = root[ oriRoot ];
		len[who] ^= len[ oriRoot ];
	}
}
bool relationTree::setFriend(int a,int b){
	findRoot(a);
	findRoot(b);
	if( root[a]==root[b] ){
		if( areFrined(a,b)==0 )
			return false;
		return true;
	}
	if( num[b]>num[a] )
		a^=b , b^=a , a^=b;

	int aRoot = root[a] , bRoot = root[b];
	root[ bRoot ] = aRoot;
	num[ aRoot ] += num[ bRoot ];
	if( len[a]^len[b] )
		len[ bRoot ] = 1;
	else
		len[ bRoot ] = 0;
	findRoot(a);
	findRoot(b);
	return true;
}
bool relationTree::setEnemy(int a,int b){
	findRoot(a);
	findRoot(b);
	if( root[a]==root[b] ){
		if( areEnemy(a,b)==0 )
			return false;
		return true;
	}
	if( num[b]>num[a] )
		a^=b , b^=a , a^=b;

	int aRoot = root[a] , bRoot = root[b];
	root[ bRoot ] = aRoot;
	num[ aRoot ] += num[ bRoot ];
	if( len[a]^len[b] )
		len[ bRoot ] = 0;
	else
		len[ bRoot ] = 1;
	findRoot(a);
	findRoot(b);
	return true;
}
int relationTree::areFrined(int a,int b){
	findRoot(a);
	findRoot(b);
	if( root[a]!=root[b] )
		return -1;
	if( len[a]^len[b] )
		return 0;
	else
		return 1;
}
int relationTree::areEnemy(int a,int b){
	findRoot(a);
	findRoot(b);
	if( root[a]!=root[b] )
		return -1;
	if( len[a]^len[b] )
		return 1;
	else
		return 0;
}


int main(){
	int n;
	scanf(" %d",&n);

	relationTree party(n);
	int c,x,y;
	while( scanf(" %d%d%d",&c,&x,&y)!=EOF && ( c || x || y ) ){
		switch(c){
			case 1:
				if( !party.setFriend(x,y) ) printf("-1\n");

				break;
			case 2:
				if( !party.setEnemy(x,y) ) printf("-1\n");

				break;
			case 3:
				if( party.areFrined(x,y)==1 ) printf("1\n");
				else printf("0\n");

				break;
			case 4:
				if( party.areEnemy(x,y)==1 ) printf("1\n");
				else printf("0\n");

				break;
		}
	}
}