#include <cstdio>
#include <cstring>
using namespace std;

char str[100];
int len[100];

int condi[5];

bool phase(int i,int which){
	if( which==5 )
		return true;
	int sum = len[i];
	while( sum<condi[which] ){
		++i;
		sum += len[i];
	}
	if( sum!=condi[which]) return false;
	return phase(i+1,which+1);
}

int main(){
	condi[0] = condi[2] = 5;
	condi[1] = condi[3] = condi[4] = 7;
	int n;
	while( scanf(" %d",&n)!=EOF && n ){
		for(int i=1;i<=n;++i){
			scanf(" %s",str);
			len[i] = strlen(str);
		}
		for(int i=1;i<=n;++i)
			if( phase(i,0) ){
				printf("%d\n",i);
				break;
			}
	}
}