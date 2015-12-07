#include <cstdio>
#include <cstring>
using namespace std;

char num[3][20];
char op;
bool okZero;
bool have[10];
int len(const char *str){
	return strlen(str) - (str[0]=='-'? 1:0);
}
char firstDig(const char *str){
	return str[0]=='-'? str[1] : str[0];
}
void getData(){
	for(int i=0 ; i<10 ; ++i)
		have[i] = false;
	char tmp[200];
	scanf(" %s",tmp);
	num[0][0] = num[1][0] = num[2][0] = '\0';
	int which = 0 , id = 0;
	for(int i=0 ; tmp[i]!='\0' ; ++i){
		if( tmp[i]=='-' && id==0 ){
			num[which][id] = '-';
			++id;
			continue;
		}
		if( tmp[i]=='+' || tmp[i]=='-' || tmp[i]=='*' || tmp[i]=='=' ){
			if( tmp[i]!='=' )
				op = tmp[i];
			num[which][id] = '\0';
			++which;
			id = 0;
		}
		else{
			have[tmp[i]-'0'] = true;
			num[which][id] = tmp[i];
			++id;
		}
	}
	num[which][id] = '\0';

	okZero = true;
	for(int i=0 ; i<3 ; ++i)
		if( len(num[i])==1 && firstDig(num[i])=='?' && num[i][0]=='-'  )
			okZero = false;

	for(int i=0 ; i<3 ; ++i)
		if( len(num[i])>1 && firstDig(num[i])=='?' )
			okZero = false;
}

long long convert(const char *str,long long mask){
	long long re = 0LL;
	long long neg = 1LL;
	int id = 0;
	if( str[0]=='-' )
		neg = -1LL , id = 1;
	while( str[id]!='\0' ){
		re = re * 10LL;
		if( str[id]=='?' ) re = re + mask;
		else re = re + str[id] - '0';
		++id;
	}
	return re*neg;
}

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		getData();

		int ans = -1;
		for(int i=0 ; i<=9 && ans==-1 ; ++i){
			if( have[i] ) continue;
			if( i==0 && !okZero ) continue;
			long long a = convert(num[0] , i);
			long long b = convert(num[1] , i);
			long long c = convert(num[2] , i);
			if( op=='+' ){
				if( a+b == c ) ans = i;
			}
			else if( op=='-' ){
				if( a-b == c ) ans = i;
			}
			else if( op=='*' ){
				if( a*b == c ) ans = i;
			}
		}
		printf("%d\n",ans);
	}
}