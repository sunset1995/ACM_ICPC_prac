#include <cstdio>
using namespace std;

struct node{
	int childNum , id;
	node *l,*r;
} segNode[100004] , *Root;

void initNode(node &whom){
	whom.childNum = 0;
	whom.id = -1;
	whom.l = whom.r = NULL;
}

void makeRelation(node &parent , node &child , bool left){
	parent.childNum += child.childNum;
	if( left )
		parent.l = &child;
	else
		parent.r = &child;
}

void makeTree(const int &k){
	for(int i=1;i<=k;++i){
		initNode( segNode[i] );
		segNode[i].childNum = 1;
		segNode[i].id = i;
	}
	int now = 0 , top = k , nowNum = k;
	while( true ){
		while( nowNum ){
			++top;
			initNode( segNode[top] );
			++now, --nowNum;
			makeRelation( segNode[top] , segNode[now] , true );
			if( !nowNum )
				break;
			++now, --nowNum;
			makeRelation( segNode[top] , segNode[now] , false );
		}
		if( top-now == 1 ){
			Root = &segNode[top];
			break;
		}
		nowNum = top - now;
	}
}

void printNthLarge(int n){
	node *nowAt = Root;
	while( true ){
		--(nowAt->childNum);
		if( nowAt->id != -1 )
			break;

		if( nowAt->l->childNum >= n )
			nowAt = nowAt->l;
		else{
			n -= nowAt->l->childNum;
			nowAt = nowAt->r;
		}
	}
	printf("%d",nowAt->id);
}

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int k;
		scanf(" %d",&k);
		makeTree(k);
		for(int i=0,s;i<k;++i){
			scanf(" %d",&s);
			if( i )
				putchar(' ');
			printNthLarge(s+1);
		}
		putchar('\n');
	}
}