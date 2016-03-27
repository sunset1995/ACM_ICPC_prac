#include <cstdio>
#include <cstring>
#define N 50
using namespace std;

long long A[N+4][N+4] ;

struct matrix{
	double a[N+4][N+4];
	int sz;
	matrix(){
		memset(a , 0 , sizeof(a));
		sz = 0;
	}
	void del(int from,int to,double ba){
		for(int i=0 ; i<sz ; ++i)
			a[to][i] -= a[from][i] * ba;
	}
};
double determine(matrix &m){
	for(int i=0 ; i<m.sz ; ++i)
		for(int j=i+1 ; j<m.sz ; ++j)
			if( m.a[j][i]!=0 )
				m.del(i , j , m.a[j][i] / m.a[i][i]);
	double det = 1.0;
	for(int i=0 ; i<m.sz ; ++i)
		det *= m.a[i][i];
	return det;
}

int main () {
	int t ;
	scanf("%d",&t) ;
	while(t--) {
		int n , u , v , di[8]={0,-1,-1,-1,0,1,1,1} , dj[8]={-1,-1,0,1,1,1,0,-1} ;
		scanf("%d",&n) ;
		memset(A,0,sizeof(A)) ;
		for(int i=0 ; i<n ; i++)
			for(int j=0 ; j<n ; j++) {
				u = i*n+j ;
				for(int k=0 ; k<8 ; k++) {
					int i2 = i+di[k] ;
					int j2 = j+dj[k] ;
					if(0<=i2 && i2<n && 0<=j2 && j2<n) {
						v = i2*n+j2 ;
						A[u][v] = A[v][u] = -1 ;
						A[u][u] ++ ;
					}
				}
			}
		matrix M;
		for(int i=0 ; i<N ; ++i)
			for(int j=0 ; j<N ; ++j)
				M.a[i][j] = (double)A[i+1][j+1];
		M.sz = n*n-1;
		printf("%.0f\n",determine(M));
	}
}
