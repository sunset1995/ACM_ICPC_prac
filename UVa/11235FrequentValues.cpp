#include <cstdio>
using namespace std;

struct node{
	int lCover , rCover , value;
	node *l , *r;
} seg[200005] , *Root;
int a[100005] , leftB[100005];

int max(int a,int b){
	return (a>b)? a : b;
}
int rangeQ(const node* const nowAt,int i,int j){
	if( nowAt->lCover == i && nowAt->rCover == j )
		return nowAt->value;
	if( j <= nowAt->l->rCover )
		return rangeQ( nowAt->l , i , j );
	else if( i >= nowAt->r->lCover )
		return rangeQ( nowAt->r , i , j );

	return max( rangeQ(nowAt->l , i , nowAt->l->rCover),
					rangeQ(nowAt->r ,  nowAt->r->lCover , j) );
}


int main(){
	int n,q;
	bool first = true;
	a[0] = -100010;
	while( scanf(" %d",&n)!=EOF && n ){
		scanf(" %d",&q);
		for(int i=1;i<=n;++i)
			scanf(" %d",&a[i]);
		for(int i=1;i<=n;++i)
			leftB[i] = (a[i]==a[i-1])? leftB[i-1] : i;
		a[n+1] = 100010;
		for(int i=n;i>0;--i){
			seg[i].l = seg[i].r = NULL;
			seg[i].lCover = seg[i].rCover = i;
			seg[i].value = 1;
			if(a[i]==a[i+1])
				seg[i].value += seg[i+1].value;
		}
		int nowNum = n , nowId = 0 , top = n;
		while( true ){
			int nextNum = 0;
			while( nowNum ){
				++top;  ++nextNum;
				++nowId;  --nowNum;
				seg[top].l = &seg[nowId];
				seg[top].r = NULL;
				seg[top].value = seg[nowId].value;
				seg[top].lCover = seg[nowId].lCover;
				seg[top].rCover = seg[nowId].rCover;
				if( !nowNum )
					break;
				++nowId;  --nowNum;
				seg[top].r = &seg[nowId];
				if( seg[top].value < seg[nowId].value )
					seg[top].value = seg[nowId].value;
				seg[top].rCover = seg[nowId].rCover;
			}
			nowNum = nextNum;
			if( nowNum==1 ){
				Root = &seg[top];
				break;
			}
		}
		while( q-- ){
			int I,J;
			scanf(" %d%d",&I,&J);
			if( leftB[J]<=I ){
				printf("%d\n",J-I+1);
				continue;
			}
			int ans = J - leftB[J] + 1;
			J = leftB[J] - 1;
			int tmp = rangeQ(Root , I , J);
			if( tmp>ans ) ans = tmp;
			printf("%d\n",ans);
		}
	}
}