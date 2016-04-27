#include <cstdio>
#include <cmath>
using namespace std;

int myStack[50000] , top;
void myStackInit(){
	top = -1;
}
void push_back(int val){
	myStack[++top] = val;
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	for(int NOWCASE=1;NOWCASE<=NCASE;++NOWCASE){
		int C,R;
		scanf(" %d%d",&C,&R);
		printf("Case #%d:",NOWCASE);
		if( C==R ){
			printf(" 0\n");
			continue;
		}
		int total = C-R;
		int findUntil = sqrt(total);
		myStackInit();
		for(int nowNum=1;nowNum<=findUntil;++nowNum){
			if( (total%nowNum)!=0 )
				continue;
			int tmp = total/nowNum;
			if( tmp<=R )
				break;
			if( tmp!=nowNum )
				push_back( tmp );
			if( nowNum>R )
				printf(" %d",nowNum);
		}
		for(int index=top;index>=0;--index)
			printf(" %d",myStack[index]);
		printf("\n");
	}
}