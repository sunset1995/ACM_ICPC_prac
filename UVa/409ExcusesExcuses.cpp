#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char keyWord[30][100] , str[30][100];
	int K,E,__time = 0;
	while( scanf(" %d%d",&K,&E)!=EOF ){
		printf("Excuse Set #%d\n",++__time);
		getchar();
		for(int i=0,tmptop=-1,cc;i<K;++i,tmptop=-1){
			while( (cc=getchar()) && cc!='\n' ){
				keyWord[i][++tmptop] = cc;
			}
			keyWord[i][++tmptop] = '\0';
		}
		int max = 0 , err[30];
		for(int i=0;i<E;++i){
			err[i] = 0;
			int index = -1;
			char nowProc[100] , top = -1;
			while( 1 ){
				str[i][++index]=getchar();
				if( str[i][index]>='A' && str[i][index]<='Z' )
					nowProc[++top] = str[i][index]-'A'+'a';
				else if( str[i][index]>='a' && str[i][index]<='z' )
					nowProc[++top] = str[i][index];
				else if( top!=-1 ){
					nowProc[++top] = '\0';
					for(int j=0;j<K;++j)
						if( strcmp(nowProc,keyWord[j])==0 ){
							++err[i];
							break;
						}
					top = -1;
				}
				if( str[i][index]=='\n' ) break;
			}
			str[i][++index] = '\0';
			if( err[i]>max ) max = err[i];
		}
		if( max )
			for(int i=0;i<E;++i){
				if( err[i]==max ) printf("%s",str[i]);
			}
		printf("\n");
	}
	return 0;
}
