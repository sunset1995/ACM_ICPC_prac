#include<cstdio>
#include<algorithm>
using namespace std;
struct shose {
  double cp;
  int id;
};
shose work[1005];
bool cmp(shose sh1,shose sh2){
	return sh1.cp > sh2.cp;
}

int main(){
  int T;
  int N;
  scanf(" %d",&T);
  while( T-- ){
  	scanf(" %d",&N);
  	for(int i=0;i<N;++i){
  	  int takeDay , fine;
  	  scanf(" %d%d",&takeDay,&fine);
  	  work[i].id = i+1;
  	  work[i].cp = 1000.00F * fine / takeDay;
  	}
  	sort( work , work+N , cmp );
  	--N;
  	for(int i=0;i<N;++i)
  	  printf("%d ",work[i].id);
  	printf("%d\n",work[N].id);
  	if( T )
  	  printf("\n");
  }
} 
