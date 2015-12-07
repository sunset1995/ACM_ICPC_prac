#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const char *_one = "HUKWIVBCNOFPSY";
const char *_two[4] = {"HeLiBeNeNaMgAlSiClArCaScTi",
"CrMnFeCoNiCuZnGaGeAsSeBrKrRbSrZrNbMoTcRuRhPd",
"AgCdInSnSbTeXeCsBaHfTaReOsIrPtAuHgTlPbBiPoAtRnFrRaRfDbSgBhHsMtDsRgCnFl",
"LvLaCePrNdPmSmEuGdTbDyHoErTmYbLuAcThPaNpPuAmCmBkCfEsFmMdNoLr"};

char str[50004];
bool dp[50004];

int main(){
	vector<char> one , two;
	for(int i=0 ; _one[i]!='\0' ; ++i)
		one.push_back( tolower(_one[i]) );
	for(int i=0 ; i<4 ; ++i){
		for(int j=0 ; _two[i][j]!='\0' ; ++j)
			two.push_back( tolower(_two[i][j]) );
	}

	int T;
	scanf("%d",&T);
	while( T-- ){
		memset( dp , 0 , sizeof(dp) );
		scanf("%s",str);
		int len = strlen(str);
		for(int i=0 ; i<len ; ++i){
			for(int j=0 ; j<one.size() && !dp[i] ; ++j)
				if( str[i]==one[j] && (i==0 || dp[i-1]) )
					dp[i] = true;
			if( i==0 ) continue;
			for(int j=1 ; j<two.size() && !dp[i] ; j+=2){
				if( str[i-1]==two[j-1] && str[i]==two[j] ){
					if( i==1 || dp[i-2] ) dp[i] = true;
				}
			}
		}
		if( dp[len-1] ) puts("YES");
		else puts("NO");
	}
}