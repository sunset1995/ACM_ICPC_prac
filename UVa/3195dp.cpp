#include<cstdio>
#include<cstring>
using namespace std;
int l1,l2,l3;
char s1[201],s2[201],s3[401];
bool dp[201][201];
int main(){
	int t;
	scanf(" %d",&t);
	for(int i=1;i<=t;++i){
		scanf(" %s%s%s",s1,s2,s3);
		l1=strlen(s1),l2=strlen(s2),l3=l1+l2;
		printf("Data set %d: ",i);
		for(int i=0;i<=l1;++i) memset(dp[i],false,sizeof(bool[l2+2]));
		dp[0][0] = true;
		for(int i=1;i<=l1;++i) if(s1[i-1]==s3[i-1]) dp[i][0] = true;
		for(int j=1;j<=l2;++j) if(s2[j-1]==s3[j-1]) dp[0][j] = true;
		for(int i=1;i<=l1;++i) for(int j=1;j<=l2;++j){
			if(s1[i-1]==s3[i+j-1] && dp[i-1][j]) dp[i][j] = true ;
			else if(s2[j-1]==s3[i+j-1] && dp[i][j-1]) dp[i][j] = true ;
		}
		if(dp[l1][l2]) printf("yes\n");
		else printf("no\n");
	}
} 

