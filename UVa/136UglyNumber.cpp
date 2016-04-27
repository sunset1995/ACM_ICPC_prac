#include<cstdio>
#include<algorithm>
#define MAX 1000000000LL
using namespace std;

int ugly[1600] , top=-1;
bool myCmp(int a,int b){
	if( a<b ) return true;
	return false;
}
void insert(int num){
	if( top+1<1500 )
		ugly[++top] = num;
	else{
		ugly[1500] = num;
		sort( ugly , ugly+1501 );
	}
}

int main(){
	long long sum = 1LL;
	while( sum<MAX ){
		long long tmp1 = sum;
		while( sum<MAX ){
			long long tmp2 = sum;
			while( sum<MAX ){
				insert((int)sum);
				sum *= 5LL;
			}
			sum = tmp2 * 3LL;
		}
		sum = tmp1 * 2LL;
	}
	printf("The 1500'th ugly number is %d.\n",ugly[1499]);
}