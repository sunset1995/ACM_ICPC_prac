#include<cstdio>
#define infinite 200000000
using namespace std;

int fireStation[100];
int dp[501][501];
int d[501];
int f,n;
int minMaxD , ansID;

void floyd(){
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if( dp[i][k] + dp[k][j] < dp[i][j] )
					dp[i][j] = dp[i][k] + dp[k][j];
}
int caculateD(){
	minMaxD = -1;
	for(int i=1;i<=n;++i){
		for(int j=0 , w=fireStation[j]; j<f; ++j,w=fireStation[j])
			if( dp[i][w] < d[i] )
				d[i] = dp[i][w];	
		if( d[i] > minMaxD )
			minMaxD = d[i];
	}
}
int caculateD(int k){
	int tmpMax = -1;
	for(int i=1;i<=n;++i){
		int tmp = ( dp[i][k]<d[i] )? dp[i][k] : d[i];
		if( tmp > tmpMax )
			tmpMax = tmp;
	}
	if( tmpMax<minMaxD )
		minMaxD = tmpMax , ansID = k;
}

int main(){
	int CASE;
	scanf(" %d",&CASE);
	while( CASE-- ){
		scanf(" %d%d",&f,&n);
		for(int i=0;i<f;++i)
			scanf(" %d",&fireStation[i]);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j)
				dp[i][j] = infinite;
			dp[i][i] = 0;
			d[i] = infinite;
		}

		char str[20];
		gets(str);
		while( gets(str)!=NULL && str[0]!='\0' && str[0]!='\n' ){
			int a,b,d;
			if( sscanf( str , " %d%d%d" , &a , &b , &d )==EOF )
				break;
			dp[a][b] = d,
			dp[b][a] = d;
		}

		floyd();

		ansID = 1;
		caculateD();
		for(int i=1;i<=n;++i){
			caculateD(i);
		}
		printf("%d\n",ansID);
		if( CASE )
			printf("\n");
	}
}