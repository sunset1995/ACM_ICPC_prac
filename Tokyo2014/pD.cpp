#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

inline int fdif(const double &lf) {
	if( fabs(lf) < 1e-8 ) return 0;
	return lf < 0 ? -1 : 1;;
}

double PI;
double d;
int n, b;

struct obstacle {
	double p, h;
	obstacle(const double &p,const double &h)
	:p(p), h(h){}
};
vector<obstacle> obs;

struct line {
	double c, l2, b;
	line(double L,double m,double h) {
		c = h/(m*(m-L));
		l2 = L/2.0;
		b = h*L*L/(4.0*m*(L-m));
	}
	bool bomb(double x,double y) {
		double ly = c*(x-l2)*(x-l2)+b;
		if( fdif(y-ly)>0 ) return true;
		return false;
	}
};

bool obsInRange(const double &from,const double &L,const obstacle &ob) {
	if( fdif(ob.p-from)==-1 ) return false;
	if( fdif(ob.p-from-L)==1 ) return false;
	return true;
}
double minV(double from, double L) {
	bool have45 = false;
	for(int i=0 ; i<obs.size() ; ++i) {
		if( !obsInRange(from,L,obs[i]) ) continue;
		double m = obs[i].p - from;
		double h = obs[i].h;
		double tmp = atan( L*h/(m*(L-m)) );
		if( fdif(tmp-PI/4.0)>0 ) have45 = true;
	}
	if( !have45 ) 
		return sqrt(L/2.0) / sin(PI/4.0);

	for(int i=0 ; i<obs.size() ; ++i) {
		if( !obsInRange(from,L,obs[i]) ) continue;
		line nowLine(L, obs[i].p-from, obs[i].h);
		bool notOk = false;
		for(int j=0 ; j<obs.size() ; ++j) {
			if( i==j ) continue;
			if( !obsInRange(from,L,obs[j]) ) continue;
			if( nowLine.bomb(obs[j].p-from, obs[j].h) ) {
				notOk = true;
				break;
			}
		}
		if( !notOk ) {
			double m = obs[i].p - from;
			double theta = atan( L*obs[i].h/(m*(L-m)) );
			return sqrt(2.0*nowLine.b) / sin(theta);
		}
	}
	return 0/0;
}

int main() {
	PI = acos(-1.0);
	scanf("%lf%d%d", &d, &n, &b);
	for(int i=0 ; i<n ; ++i) {
		double p, h;
		scanf("%lf%lf", &p, &h);
		obs.emplace_back(obstacle(p,h));
	}
	double ans = -100.0;
	for(int btime=0 ; btime<=b ; ++btime) {
		double L = d / (btime+1);
		bool haveOnBound = false;
		for(int i=0 ; i<=btime ; ++i) {
			double nowP = L*i;
			for(int j=0 ; j<obs.size() ; ++j)
				if( fdif(obs[j].p-nowP)==0 )
					haveOnBound = true;
		}
		if( haveOnBound ) continue;

		double nowV = -100.0;
		for(int i=0 ; i<=btime ; ++i) {
			double tmp = minV(L*i, L);
			if( fdif(nowV)==-1 || fdif(nowV-tmp)==-1 )
				nowV = tmp;
		}
		if( fdif(ans)==-1 || fdif(nowV-ans)==-1 )
			ans = nowV;
	}
	printf("%.5lf\n",ans);
	return 0;
}
