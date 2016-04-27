#include<cstdio>
#define MAX 1000000
using namespace std;
char str[MAX];
int suffix[MAX+1];
int main(){
	int N,__time=1;
	while( scanf(" %d",&N)!=EOF && N ){
		getchar();
		printf("Test case #%d\n",__time);
		
		str[0] = getchar();
		int id = 0;
		suffix[0] = -1;
		for(int i=1;i<N;++i){
			str[i] = getchar();
			if( str[i]==str[id] ) suffix[i] = suffix[id];
			else{
				while( id>-1 && str[id]!=str[i] ) id = suffix[id];
			}
			++id;
			int total = i+1 , per = i+1-id;
			if( id && total%per==0 ) printf("%d %d\n",total,total/per);
		}
		printf("\n");
		++__time;
	}
}
