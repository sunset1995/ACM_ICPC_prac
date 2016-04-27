#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

const int infinite = 0x3FFFFFFF;
int pos[204][2];
int dis[204][204];
int minJump[204];
struct node{
	int id , cost;
};
struct pqCmp{
	bool operator () (const node a,const node b) const {
		return a.cost > b.cost;
	}
};

int main(){
	int n , NCASE = 0;
	while( scanf(" %d",&n)!=EOF && n ){
		for(int i=0;i<n;++i){
			scanf(" %d%d",&pos[i][0],&pos[i][1]);
			for(int j=0;j<=i;++j){
				int difX = pos[i][0] - pos[j][0],
					 difY = pos[i][1] - pos[j][1];
				dis[j][i] = dis[i][j] = difX*difX + difY*difY;
			}
			minJump[i] = infinite;
		}
		priority_queue< node , vector<node> , pqCmp > pq;
		minJump[0] = 0;
		pq.push( (node) { 0 , 0 } );
		while( !pq.empty() ){
			node nowAt = pq.top();
			pq.pop();
			if( nowAt.id==1 )
				break;
			if( nowAt.cost > minJump[ nowAt.id ] )
				continue;
			for(int i=0;i<n;++i){
				int costNeed = (nowAt.cost > dis[nowAt.id][i])? nowAt.cost : dis[nowAt.id][i];
				if( costNeed < minJump[i] ){
					minJump[i] = costNeed;
					pq.push( (node){ i , costNeed } );
				}
			}
		}
		printf("Scenario #%d\n",++NCASE);
		printf("Frog Distance = %.3f\n\n",sqrt(minJump[1]));
	}
}