#include<cstdio>
using namespace std;
int stack[50];
int total , t , count;
void recursive(int);
int gcd(int,int);

int main(){
	int n;
	scanf(" %d",&n);
	int Case = 0;
	while( ++Case<=n ){
		scanf(" %d%d",&total,&t);
		printf("Case %d:\n",Case);
		count = 0;
		recursive(0);
	}
}

int gcd(int a,int b){
	if( b%a==0 ) return a;
	return gcd( b%a , a );
}
void recursive(int id){
	if( id==t-1 ){
		stack[id] = total-count;
		if( id && stack[id]<stack[id-1] ) return;
		bool pp = true;
		for(int j=0;j<id;++j)
			if( gcd(stack[j],stack[id])!=1 ){
				pp = false;
				break;
			}
		if( !pp ) return;
		
		for(int i=0;i<t-1;++i) printf("%d ",stack[i]);
		printf("%d\n",stack[t-1]);
		return;
	}
	int until = total / (t-id);
	for(int i=(id==0)?1:(stack[id-1]);i<=until && (i*(t-id-1)+count)<=total;++i){
		bool pp = true;
		for(int j=0;j<id;++j)
			if( gcd(stack[j],i)!=1 ){
				pp = false;
				break;
			}
		if( !pp ) continue;
		stack[id] = i;
		count += i;
		recursive(id+1);
		count -= i;
	} 
}
