#include <cstdio>
#include <cmath>
using namespace std;

#define DIFF 1e-8

inline void clearOtherRow(double m[10][10], int pR, int pC, int k) {
	for(int r=0; r<k; ++r) {
		if( r==pR || fabs(m[r][pC])<DIFF ) continue;
		double x = m[r][pC] / m[pR][pC];
		for(int c=0; c<k; ++c)
			m[r][c] -= x * m[pR][c];
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int NOWCASE=1; NOWCASE<=n; ++NOWCASE) {
		int k;
		scanf("%d", &k);
		double matrix[10][10];
		bool used[10] = {0};
		for(int r=0; r<k; ++r)
			for(int c=0; c<k; ++c)
				scanf("%lf", &matrix[r][c]);
		for(int i=0; i<k; ++i)
			matrix[i][i] -= 1.0;
		double det = 1.0;
		for(int r=0; r<k; ++r) {
			int pivot = 0;
			while( pivot<k && fabs(matrix[r][pivot])<DIFF )
				++pivot;
			if( pivot==k ) {
				det = 0.0;
				break;
			}
			det *= matrix[r][pivot];
			clearOtherRow(matrix, r, pivot, k);
		}
		if( fabs(det)<DIFF ) putchar('1');
		else putchar('0');
		if( NOWCASE%5==0 ) putchar('\n');
		else putchar(' ');
	}
	return 0;
}
