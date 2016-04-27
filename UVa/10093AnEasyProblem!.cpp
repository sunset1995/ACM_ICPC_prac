#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char number[1000];
	while( scanf(" %s",&number)!=EOF ){
		int len = strlen(number);
		int r=2;
		int total = 0;
		for(int i=0;i<len;++i){
			if( number[i]=='0' ) continue;
			else if( number[i]>='1' && number[i]<='9' ){
				if( number[i]-'1'+2>r ) r = number[i]-'1'+2;
				total += number[i]-'1'+1;
			}
			else if( number[i]>='A' && number[i]<='Z' ){
				if( number[i]-'A'+11>r ) r = number[i]-'A'+11;
				total += number[i]-'A'+10;
			}
			else if( number[i]>='a' && number[i]<='z' ){
				if( number[i]-'a'+37>r ) r = number[i]-'a'+37;
				total += number[i]-'a'+36;
			}
		}
		while( r<=62 && (total%(r-1))!=0 )
			++r;
		if( r>62 )
			printf("such number is impossible!\n");
		else
			printf("%d\n",r);
	}
}
