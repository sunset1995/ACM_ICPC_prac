#include <cstdio>
#include <cstring>
using namespace std;

char str[100004];
int fail[100004];
char strrev[100004];

int main(){
	while( scanf(" %s",str)!=EOF ){
		int len = strlen(str);
		for(int i=len-1,j=0;i>=0;--i,++j)
			strrev[j] = str[i];
		strrev[len] = '\0';
		fail[0] = -1;
		for(int i=0,j=1;j<len;++i,++j){
			if(str[i]==str[j]) fail[j] = fail[i];
			else fail[j] = i;
			while( i>=0 && str[i]!=str[j] )
				i = fail[i];
		}
		int idstr = 0 , idrev = 0;
		while( strrev[idrev]!='\0' ){
			while( idstr!=-1 && str[idstr]!=strrev[idrev] )
				idstr = fail[idstr];
			++idstr , ++idrev;
		}
		str[idstr] = '\0';
		printf("%s%s\n",strrev,str);
	}
}