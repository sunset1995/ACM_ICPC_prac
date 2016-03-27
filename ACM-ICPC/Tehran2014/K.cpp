#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double eps = 0.001;
int fdif(double lf) {
	if( fabs(lf)<1e-8 ) return 0;
	return lf < 0.0 ? -1 : 1;
}

struct Sample {
	double x;
	vector<double> y, p;
	Sample(double x, int m)
	:x(x), y(m), p(m) {}
};
struct Line {
	double x, y, m;
	Line(double x1, double y1) {
		x = x1;
		y = y1;
	}
	double f(double xi) {
		return y + m * (x - xi);
	}
};

double Perr(const Sample &sm, double y) {
	double err = 0.0;
	for(int i=0; i<sm.y.size(); ++i)
		err += fabs(sm.p[i]*(y-sm.y[i]));
	return err;
}

double Lerr(const vector<Sample> &sm, Line &l, double m) {
	l.m = m;
	double res = 0;
	for(int i=0; i<sm.size(); ++i)
		res = max(res, Perr(sm[i], l.f(sm[i].x)));
	return res;
}
double Aerr(const vector<Sample> &sm, double x, double y) {
	Line line = Line(x, y);
	double ml = -2e9, mr = 2e9;
	while( fdif(mr-ml-eps) > 0 ) {
		double mL = ml+(mr-ml)/3.0;
		double mR = ml+(mr-ml)*2.0/3.0;
		if( Lerr(sm, line, mL) > Lerr(sm, line, mR) )
			ml = mL;
		else mr = mR;
	}
	return Lerr(sm, line, (ml+mr)/2.0);
}

int main() {
	int n;
	while( scanf("%d", &n)!=EOF && n ) {
		vector<Sample> samples;
		for(int i=0; i<n; ++i) {
			double x;
			int m;
			scanf("%lf%d", &x, &m);
			samples.push_back(Sample(x, m));
			Sample &now = samples.back();
			for(int j=0; j<m; ++j)
				scanf("%lf", &now.y[j]);
			for(int j=0,pi; j<m; ++j) {
				scanf("%lf", &now.p[j]);
				now.p[j] /= 100.0;
			}
		}
		Sample sm0 = samples[0];
		double yl=-2e9, yr=2e9;
		while( fdif(yr-yl-eps) > 0 ) {
			double yL = yl + (yr-yl)/3.0;
			double yR = yl + (yr-yl)*2.0/3.0;
			double eL = Aerr(samples, sm0.x, yL);
			double eR = Aerr(samples, sm0.x, yR);
			if( eL > eR )
				yl = yL;
			else yr = yR;
		}
		printf("%.1f\n", Aerr(samples, sm0.x, (yl+yr)/2.0));
	}
	return 0;
}
