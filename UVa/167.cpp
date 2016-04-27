#include <cstdio>
using namespace std;

int table[8][8] , max , tmp;
int row[8];
bool check(int judgeRow,int judgeCol){
	for(int i=0,dis=judgeRow ; i<judgeRow ; ++i,--dis){
		if( row[i]==judgeCol ) return false;
		if( row[i]+dis==judgeCol ) return false;
		if( row[i]-dis==judgeCol ) return false;
	}
	return true;
}
void dfs(int);

int main(){
	int k;
	scanf(" %d",&k);
	while( k-- ){
		for(int i=0;i<8;++i)
			for(int j=0;j<8;++j)
				scanf(" %d",&table[i][j]);
		
		max = 0 , tmp = 0;
		dfs(0);
		printf("%5d\n",max);
	}
}

void dfs(int nowRow){
	if( nowRow==8 ){
		if( tmp>max )
			max = tmp;
		return;
	}
	for(int i=0;i<8;++i)
		if( check(nowRow,i) ){
			row[nowRow] = i;
			tmp += table[nowRow][i];
			dfs(nowRow+1);
			tmp -= table[nowRow][i];
		}
}
