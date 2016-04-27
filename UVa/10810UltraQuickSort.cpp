#include<cstdio>
#define SWAP(a,b){ int tmp=a;a=b,b=tmp; }
using namespace std;
int *num;
long long ans;
void merge(int,int);

int main(){
	int n;
	while( scanf(" %d",&n)!=EOF && n ){
		num = new int[n];
		for(int i=0;i<n;++i) scanf(" %d",&num[i]);
		ans = 0;
		merge( 0 , n );
		printf("%lld\n",ans);
		delete [] num;
	}	
}
void merge(int from , int length){
	if( length<=1 ) return;
	if( length==2 ){
		if( num[from]>num[from+1] ){
			SWAP(num[from],num[from+1]);
			++ans;
		}
		return;
	}
	int len1 = length/2 , len2 = length - len1;
	int from1 = from , from2 = from1 + len1;
	merge(from1,len1);
	merge(from2,len2);
	int *tmparray = new int[length];
	for(int i=0;i<length;++i) tmparray[i] = num[from+i];
	from1-=from , from2-=from;
	int end1 = len1-1 , end2 = length-1 , now=from;
	while( from1<=end1 && from2<=end2 ){
		if( tmparray[from1]<tmparray[from2] )
			num[now] = tmparray[from1] , ++from1;
		else
			num[now] = tmparray[from2] , ans += len1-from1 , ++from2;
		++now;
	}
	while( from1<=end1 ) num[now] = tmparray[from1] , ++now , ++from1;
	while( from2<=end2 ) num[now] = tmparray[from2] , ++now , ++from2; 
}
