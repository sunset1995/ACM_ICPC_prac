#include <cstdio>
#include <cstring>
using namespace std;

int student[20];
int id;
int candy[60];

bool findCandy(int nowAge){
	--id;
	while( id>0 && candy[id]<student[nowAge] )
		--id;
	if( id>0 && candy[id]>=student[nowAge] ) return true;
	else return false;
}

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int N,M;
		scanf(" %d%d",&N,&M);
		memset(student , 0 , sizeof(student));
		memset(candy , 0 , sizeof(candy));
		for(int i=0,age;i<N;++i){
			scanf(" %d",&age);
			++student[age];
		}
		for(int i=0,num;i<M;++i){
			scanf(" %d",&num);
			++candy[num];
		}
		id = 55;
		bool ok = true;
		for(int i=15;i>=5 && ok;--i)
			if( student[i] )
				ok = findCandy(i);
		if( ok )
			printf("YES\n");
		else
			printf("NO\n");
	}
}