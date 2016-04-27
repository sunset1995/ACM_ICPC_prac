#include<cstdio>
#include<cstring>
using namespace std;
int comT[26],totalT[26];
int main(){
	char one[2000],two[2000];
	while(gets(one)!=NULL && gets(two)!=NULL){
		int oneL = strlen(one), twoL = strlen(two);
		for(int i=0;i<26;++i)
			comT[i] = 0, totalT[i] = 0;
		for(int i=0;i<oneL;++i) ++comT[ one[i]-'a' ];
		for(int i=0;i<twoL;++i)
			if(comT[ two[i]-'a' ]>0)
				--comT[ two[i]-'a' ],
				++totalT[ two[i]-'a' ];
		for(int i=0;i<26;++i)
			while(totalT[i]>0){
				printf("%c",i+'a');
				--totalT[i];
			}
		printf("\n");
	}
}
