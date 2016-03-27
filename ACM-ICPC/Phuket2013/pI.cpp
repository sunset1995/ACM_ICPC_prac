#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

int fcmp(const double &lf){
	if( fabs(lf)<1e-5 ) return 0;
	return (lf < 0.0)? -1 : 1;
}

bool judgeWeight(const double &wei){
	return fcmp(wei-7.0) <= 0;
}
bool judge(double &len,double &wid,double &dep){
	if( fcmp(len + wid + dep - 125.0)<=0 ) return true;
	if( fcmp(len-56.0)<=0 && fcmp(wid-45.0)<=0 && fcmp(dep-25.0)<=0 )
		return true;
	return false;
}

int main(){
	int t;
	scanf("%d",&t);
	int cnt = 0;
	while( t-- ){
		double len , wid , dep , wei;
		scanf("%lf%lf%lf%lf",&len,&wid,&dep,&wei);
		if( judgeWeight(wei) && judge(len,wid,dep) ){
			++cnt;
			puts("1");
		}
		else puts("0");
	}
	printf("%d\n",cnt);
	return 0;
}
