#include<cstdio>
using namespace std;
int main(){
	int __time , JOB[100];
	scanf(" %d",&__time);
	do{
		int n,m;
		scanf(" %d%d",&n,&m);
		for(int i=0;i<n;++i) scanf(" %d",&JOB[i]);
		
		int myJobPriority = JOB[m] , nowAt = 0 , timeConsuming = 0 , count = 0;
		for(int i=9;i>myJobPriority;--i){
			int start = nowAt;
			for(int j=start;j<n;++j)
				if( JOB[j]==i ) ++count , nowAt = j;
			for(int j=0;j<start;++j)
				if( JOB[j]==i ) ++count , nowAt = j;
		}
		while( nowAt!=m ){
			if( JOB[nowAt]==myJobPriority ) ++count;
			if( ++nowAt==n ) nowAt = 0;
		}
		printf("%d\n",count+1);
	}while( --__time );
} 
