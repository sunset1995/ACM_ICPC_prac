#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct point{
	int x,y;
	bool operator == (const point &rth) const{
		return x==rth.x && y==rth.y;
	}
} p[600];
int stack[600];
int top;

bool myCmp(const point &a,const point &b){
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
int cross(int a,int b,int c,int d){
	return a*d - b*c;
}

void findBotMono(int N){
	top = -1;
	stack[++top] = 0;
	for(int i=1;i<N;++i){
		if( p[i].x == p[i-1].x )
			continue;
		while( top>=1 && cross( p[stack[top]].x - p[stack[top-1]].x , p[stack[top]].y - p[stack[top-1]].y ,
						  p[i].x - p[stack[top]].x , p[i].y - p[stack[top]].y ) <= 0 )
			--top;
		stack[++top] = i;
	}
}
void findUpMono(int N){
	top = -1;
	stack[++top] = N-1;
	for(int i=N-2;i>=0;--i){
		if( p[i].x == p[i+1].x )
			continue;
		while( top>=1 && cross( p[stack[top]].x - p[stack[top-1]].x , p[stack[top]].y - p[stack[top-1]].y ,
						  p[i].x - p[stack[top]].x , p[i].y - p[stack[top]].y ) <= 0 )
			--top;
		stack[++top] = i;
	}
}

int main(){
	int K;
	scanf(" %d",&K);
	printf("%d\n",K);
	while( K-- ){
		int N;
		scanf(" %d",&N);
		for(int i=0;i<N;++i)
			scanf(" %d%d",&p[i].x , &p[i].y);
		sort( &p[0] , &p[N] , myCmp );

		vector<point> ans;
		findBotMono(N);
		for(int i=0;i<=top;++i)
			ans.push_back( p[stack[i]] );
		
		findUpMono(N);
		if( ans[0] == p[stack[top]] )
			--top;
		for(int i=( ans.back() == p[stack[0]] )? 1 : 0
				;i<=top;++i)
			ans.push_back( p[stack[i]] );

		int minId = 0;
		for(int i=1;i<ans.size();++i)
			if( ans[i].y < ans[minId].y
				|| (ans[i].y == ans[minId].y && ans[i].x < ans[minId].x) )
				minId = i;
		printf("%d\n",(int)ans.size()+1);
		for(int i=minId;i<ans.size();++i)
			printf("%d %d\n",ans[i].x , ans[i].y);
		for(int i=0;i<minId;++i)
			printf("%d %d\n",ans[i].x , ans[i].y);
		printf("%d %d\n",ans[minId].x , ans[minId].y);
		if( K ){
			scanf("%*d");
			printf("-1\n");
		}
	}
}