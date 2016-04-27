#include<cstdio>
using namespace std;

int num[5];
bool used[5];
int total;
bool operation(int);

int main(){
	while( scanf(" %d%d%d%d%d",&num[0],&num[1],&num[2],&num[3],&num[4])!=EOF && num[0]>0 ){
		for(int i=0;i<5;++i) used[i] = false;
		bool possible = false;
		for(int i=0;i<5;++i){
			total = num[i];
			used[i] = true;
			if( operation(0) ){
				possible = true;
				break;
			}
			used[i] = false;
		}
		if(possible) printf("Possible\n");
		else printf("Impossible\n");
	}
}

bool operation(int now){
	if( now==4 ){
		if( total==23 ) return true;
		return false;
	}
	for(int i=0;i<5;++i){
		if( used[i]==false ){
			total += num[i];
			used[i] = true;
			if( operation(now+1) ) return true;
			used[i] = false;
			total -= num[i];
		}
	}
	for(int i=0;i<5;++i){
		if( used[i]==false ){
			total -= num[i];
			used[i] = true;
			if( operation(now+1) ) return true;
			used[i] = false;
			total += num[i];
		}
	}
	for(int i=0;i<5;++i){
		if( used[i]==false ){
			total *= num[i];
			used[i] = true;
			if( operation(now+1) ) return true;
			used[i] = false;
			total /= num[i];
		}
	}
	return false;
}
