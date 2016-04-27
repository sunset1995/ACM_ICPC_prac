#include<cstdio>
#include<algorithm>
#define SWAP(a,b){ (a)^=(b) , (b)^=(a) , (a)^=(b); }
using namespace std;

int binaryTree[5001],end;
void insertion(int);
int extractMin();

int main(){
  int N;
  while( scanf(" %d",&N)!=EOF && N!=0 ){
  	end = 0;
  	for(int i=0;i<N;++i){
  		int tmp;
  		scanf(" %d",&tmp);
  		insertion(tmp);
  	}
    
    int cost = 0;
    while(end!=1){
    	int thisTimeCost = extractMin();
    	thisTimeCost += extractMin();
    	cost += thisTimeCost;
    	insertion( thisTimeCost );
    }
    printf("%d\n",cost);
  }
}

void insertion(int val){
  binaryTree[ ++end ] = val;
  int nowAt = end;
  while( nowAt!=1 && binaryTree[ nowAt ]<binaryTree[ nowAt/2 ] ){
	SWAP( binaryTree[ nowAt ],binaryTree[ nowAt/2 ] );
	nowAt/=2;
  }
}
int extractMin(){
  int output = binaryTree[1];
  binaryTree[1] = binaryTree[ end-- ];
  int nowAt = 1;
  while( 2*nowAt<=end ){
	int smaller = 2*nowAt; //left
	if( smaller+1<=end && binaryTree[ smaller+1 ]<binaryTree[ smaller ] )
		++smaller;
	if( binaryTree[ nowAt ] > binaryTree[ smaller ] ){
		SWAP( binaryTree[ smaller ],binaryTree[ nowAt ] );
		nowAt = smaller;
	}
	else break;
  }
  return output;
}
