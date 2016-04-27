#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[25] , top , sum , target;
char str[1000];

void getData(){
	fgets( str , 1000 , stdin );
	char *ptr = strtok( str , " \n" );
	top = -1 , sum = 0;
	do{
		int getval;
		sscanf( ptr , "%d" , &getval ); 
		a[++top] = getval;
		sum += getval;
		ptr = strtok( NULL , " \n" );
	}while( ptr!=NULL );
}

int main(){
	int m;
	scanf(" %d",&m);
	fgets( str , 10 , stdin );
	while( m-- ){
	  	getData();
	  	target = sum/2;
	  	sort( a , a+top+1 );
	  	int sum1 = a[top] , sum2 = a[top-1];
	  	for(int i=top-2;i>=0;--i){
	  		if( sum1>sum2 ) sum2 += a[i];
	  		else sum1 += a[i];
		}
		if( sum1==sum2 ) printf("YES\n");
		else printf("NO\n");
	}
}
