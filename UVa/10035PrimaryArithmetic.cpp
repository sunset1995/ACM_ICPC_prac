#include<cstdio>
#include<cstring>
#define MAX 15
using namespace std;
int main(){
	char a[MAX],b[MAX];
	while( scanf(" %s%s",a,b)!=EOF ){
		if(a[0]=='0' && b[0]=='0') break;	
		int atop = strlen(a)-1 , btop = strlen(b)-1;
		int count = 0,carry=0;
		while( atop>=0 && btop>=0 ){
			if( (a[atop] + b[btop]-'0' + carry)>'9' )
				++count , carry = 1;
			else carry = 0;
			--atop , --btop;
		}
		if( carry ){
			while( atop>=0 && a[atop]=='9' )
				++count , --atop;
			while( btop>=0 && b[btop]=='9' )
				++count , --btop;
		}
		
		if(count==0) printf("No carry operation.\n");
		else if(count==1) printf("1 carry operation.\n");
		else printf("%d carry operations.\n",count);
	}
}
