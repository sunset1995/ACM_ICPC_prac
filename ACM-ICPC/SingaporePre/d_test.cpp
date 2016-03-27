#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;
struct Point{
    int x,y,id;
    Point(const int &_x,const int &_y,const int &_id)
    :x(_x) , y(_y) , id(_id){}
};
int dis(const Point &l,const Point &r){
    return abs(l.x - r.x) + abs(l.y - r.y);
}

struct Edge{
    int u , v , len;
    Edge(const int &_u,const int &_v)
    :u(_u) , v(_v){}
    bool operator < (const Edge &rth) const{
        return len < rth.len;
    }
};

vector< Point > V;
vector< Edge > E;
bool grid[1004][1004];

void buildEdge(){
    for(int i=0 ; i<V.size() ; ++i)
        for(int j=i+1 ; j<V.size() ; ++j){
            E.push_back( Edge(V[i].id , V[j].id) );
            E.back().len = dis(V[i] , V[j]);
        }
}

int root[100004];
int findRoot(int from){
    if( root[from]==from ) return from;
    return root[from] = findRoot( root[from] );
}
long long kruskal(){
    for(int i=0 ; i<100004 ; ++i)
        root[i] = i;
    long long sumDis = 0LL;
    sort(E.begin() , E.end());
    for(auto &e : E){
        //printf("%d\n",dis(V[e.u] , V[e.v]));
        //printf("(%d,%d) - (%d,%d)\n",V[e.u].x,V[e.u].y , V[e.v].x , V[e.v].y);
        int a = findRoot(e.u);
        int b = findRoot(e.v);
        if( a==b ) continue;
        sumDis = sumDis + e.len;
        if( V[e.u].x > V[e.v].x ) swap(e.u , e.v);
        //printf("(%d,%d) - (%d,%d) : %d\n",V[e.u].x,V[e.u].y , V[e.v].x , V[e.v].y , dis(V[e.u] , V[e.v]));
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
            V.push_back( Point(x , y , V.size()) );
            grid[x][y] = true;
        }
    }
    buildEdge();
    printf("%lld\n",kruskal());
    return 0;
}