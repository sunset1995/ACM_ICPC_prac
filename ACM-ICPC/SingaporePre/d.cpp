#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Point{
	int x,y,id;
	int vX,vY,lb2rt;
	Point(const int &_x,const int &_y,const int &_id)
	:x(_x) , y(_y) , id(_id) , vX(_x) , vY(_y) , lb2rt(_x-_y){}
};
void rotate(Point &v){
	int tmpx = v.vX , tmpy = v.vY;
	v.vX = tmpx + tmpy;
	v.vY = -tmpx + tmpy;
	v.lb2rt = v.vX - v.vY;
}
int dis(const Point &l,const Point &r){
	return abs(l.x - r.x) + abs(l.y - r.y);
}
vector< Point > V;

struct Edge{
	int u , v , len;
	Edge(const int &_u,const int &_v)
	:u(_u) , v(_v){
		len = dis(V[_u] , V[_v]);
	}
	bool operator < (const Edge &rth) const{
		return len < rth.len;
	}
};

vector< Edge > E;
bool grid[1004][1004];

vector< int > ids;
bool myCmp(const int &l,const int &r){
	return V[l].lb2rt < V[r].lb2rt || 
		(V[l].lb2rt==V[r].lb2rt && V[l].vX<V[r].vX);
}

void scan(){
	sort( ids.begin() , ids.end() , myCmp );

	map<int,int> line;
	for(auto &id : ids){
		int nowLine = V[id].vX + V[id].vY;
		int minId = -1;
		for(auto &l : line){
			if( l.first >= nowLine ) break;
			if( V[l.second].vY > V[id].vY ) continue;
			if( minId==-1 || dis(V[l.second] , V[id]) < dis(V[minId] , V[id]) )
				minId = l.second;
		}
		if( minId != -1 )
			E.push_back( Edge(minId , id) );
		line[nowLine] = id;
	}
}
void rotateAll(){
	for(auto &v : V) rotate(v);
}
void buildEdge(){
	for(int i=0 ; i<V.size() ; ++i)
		ids.emplace_back( i );
	for(int i=0 ; i<4 ; ++i){
		scan();
		rotateAll();
	}
}

int root[100004];
int findRoot(int from){
	if( root[from]==from ) return from;
	return root[from] = findRoot( root[from] );
}
int kruskal(){
	for(int i=0 ; i<100004 ; ++i)
		root[i] = i;
	int sumDis = 0;

	sort(E.begin() , E.end());
	for(auto &e : E){
		int a = findRoot(e.u);
		int b = findRoot(e.v);
		if( a==b ) continue;
		sumDis = sumDis + e.len;
		root[b] = a;
	}
	return sumDis;
}

int main(){
	int N;
	scanf("%d",&N);
	for(int i=0 ,x,y ; i<N ; ++i){
		scanf("%d%d",&x,&y);
		if( !grid[x][y] ){
			V.emplace_back( Point(x , y , V.size()) );
			grid[x][y] = true;
		}
	}
	buildEdge();
	printf("%d\n",kruskal());
	return 0;
}