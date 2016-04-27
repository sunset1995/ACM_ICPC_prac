#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

	typedef struct {
		int count;
		char country[100];
	} person;
	person beauty[2000];
int main(){
	int n;
	scanf(" %d",&n);
	int top=-1;
	while( n-- !=0 ){
		char nowCountry[100];
		scanf(" %s",nowCountry);
		char del[100];
		gets(del);
		int compareId = 0;
		for( ;compareId<=top && strcmp(nowCountry,beauty[ compareId ].country)!=0; ++compareId) ;
		
		if( compareId>top ){
			++top;
			strcat( beauty[ top ].country,nowCountry );
			beauty[ top ].count = 1;
		}
		else
			++beauty[ compareId ].count;
	}
	for(int i=0;i<=top;++i){
		for(int j=i+1;j<=top;++j){
			if( strcmp(beauty[i].country,beauty[j].country) > 0 ){
				person temp;
				temp = beauty[i];
				beauty[i] = beauty[j];
				beauty[j] = temp;
			}
		}
	}
	for(int i=0;i<=top;++i){
		printf("%s %d\n",beauty[i].country,beauty[i].count);
	}
	return 0;
}
