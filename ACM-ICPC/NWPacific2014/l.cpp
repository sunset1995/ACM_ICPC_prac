#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
using namespace std;

int p , w , q;
struct data{
	char name[70];
	int x,y,z;
};
data planet[70];

double enLen(data &l,data &r){
	double disX = 0.0+l.x-r.x;
	double disY = 0.0+l.y-r.y;
	double disZ = 0.0+l.z-r.z;
	return sqrt( disX*disX + disY*disY + disZ*disZ );
}
int findId(const char *str){
	for(int i=0 ; i<p ; ++i)
		if( strcmp(str , planet[i].name)==0 )
			return i;
	return p;
}

double dis[70][70];
double minD[70][70];

void floyd(){
	for(int k=0 ; k<p ; ++k)
		for(int i=0 ; i<p ; ++i)
			for(int j=0 ; j<p ; ++j)
				if( minD[i][k] + minD[k][j] < minD[i][j] )
					minD[i][j] = minD[i][k] + minD[k][j];
}

int main(){
	int NCASE = 0;
	int T;
	scanf("%d",&T);
	while( T-- ){
		scanf("%d",&p);
		for(int i=0 ; i<p ; ++i)
			scanf("%s%d%d%d",planet[i].name , &planet[i].x , &planet[i].y , &planet[i].z);
		for(int i=0 ; i<p ; ++i)
			for(int j=0 ; j<p ; ++j)
				minD[i][j] = dis[i][j] = enLen(planet[i] , planet[j]);

		scanf("%d",&w);
		char tmp1[70] , tmp2[70];
		for(int i=0 ; i<w ; ++i){
			scanf("%s%s",tmp1,tmp2);
			int id1 = findId(tmp1);
			int id2 = findId(tmp2);
			minD[id1][id2] = dis[id1][id2] = 0.0;
		}
		floyd();

		printf("Case %d:\n",++NCASE);
		scanf("%d",&q);
		for(int i=0 ; i<q ; ++i){
			scanf("%s%s",tmp1,tmp2);
			int id1 = findId(tmp1);
			int id2 = findId(tmp2);
			printf("The distance from %s to %s is %lld parsecs.\n",planet[id1].name , planet[id2].name , (long long)round(minD[id1][id2]));
		}
	}
}