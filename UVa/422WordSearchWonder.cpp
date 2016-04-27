#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n;
char puzzle[104][104];
char word[704][104];
int sr[704] , sc[704];
int wayr[704] , wayc[704];
int wtop;

void makeWord(int r,int c,int nr,int nc){
	++wtop;
	sr[wtop] = r;
	sc[wtop] = c;
	wayr[wtop] = nr;
	wayc[wtop] = nc;
	int top = -1;
	while( r<n && c<n && r>=0 && c>=0 ){
		word[wtop][++top] = puzzle[r][c];
		r += nr , c += nc;	
	}
	word[wtop][++top] = '\0';	
}

int main(){
	scanf(" %d",&n);
	wtop = -1;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			scanf(" %c",&puzzle[i][j]);
	for(int i=0;i<n;++i){
		makeWord(0,i,1,0);
		makeWord(i,0,0,1);
		makeWord(i,n-1,0,-1);
		makeWord(0,i,1,1);
		makeWord(0,i,1,-1);
		makeWord(n-1,i,-1,1);
		makeWord(n-1,i,-1,-1);
	}
	char found[104];
	while( scanf(" %s",found)!=EOF && found[0]!='0' ){
		char *from = NULL;
		int i=0;
		while( i<=wtop ){
			from = strstr(word[i] , found);
			if( from!=NULL ) break;
			++i;	
		}
		if( from==NULL ) printf("Not found\n");
		else{
			int sdif = from - word[i];
			int edif = strlen(found) - 1 + sdif;
			int r1 = sr[i] + wayr[i]*sdif + 1;
			int c1 = sc[i] + wayc[i]*sdif + 1;
			int r2 = sr[i] + wayr[i]*edif + 1;
			int c2 = sc[i] + wayc[i]*edif + 1;
			printf("%d,%d %d,%d\n",r1,c1,r2,c2);
		}
	}
}