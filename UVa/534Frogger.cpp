#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

const int infinite = 0x3FFFFFFF;
int pos[204][2];
int dis[204][204];
int minJump[204];

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
		queue<int> relaxQ;
		relaxQ.push(0);
		bool inQ[204];
		for(int i=0;i<n;++i)
			inQ[i] = false;
		minJump[0] = 0;
		inQ[0] = true;
		relaxQ.push(0);
		while( ! relaxQ.empty() ){
			int nowAt = relaxQ.front();
			relaxQ.pop();
			inQ[nowAt] = false;
			for(int i=0;i<n;++i){
				int tmp = (minJump[nowAt] > dis[nowAt][i])? minJump[nowAt] : dis[nowAt][i];
				if( minJump[i] > tmp ){
					minJump[i] = tmp;
					if( ! inQ[i] )
						inQ[i] = true;
						relaxQ.push(i);
				}
			}
		}
		printf("Scenario #%d\n",++NCASE);
		printf("Frog Distance = %.3f\n\n",sqrt(minJump[1]));
	}
}