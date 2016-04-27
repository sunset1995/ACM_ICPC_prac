#include <cstdio>
using namespace std;

const int maxSize = 100004;
int N,K;
int zero[maxSize],pos[maxSize];

int qZero(int id){
	int num = 0;
	while( id>0 ){
		num += zero[id];
		id -= (-id) & id;
	}
	return num;
}
int qPos(int id){
	int num = 0;
	while( id>0 ){
		num += pos[id];
		id -= (-id) & id;
	}
	return num;
}
void uZero(int id,int amount){
	if( amount==0 ) return;
	while( id<=N ){
		zero[id] += amount;
		id += (-id) & id;
	}
}
void uPos(int id,int amount){
	if( amount==0 ) return;
	while( id<=N ){
		pos[id] += amount;
		id += (-id) & id;
	}
}
void update(int id,int val){
	int nowZero = qZero(id) - qZero(id-1);
	int nowPos = qPos(id) - qPos(id-1);
	int valZero = (val==0)? 1 : 0;
	int valPos = (val>0)? 1 : 0;
	
	uZero(id,valZero-nowZero);
	uPos(id,valPos-nowPos);
	
}
void query(int i,int j){
	if( qZero(j) - qZero(i-1) ){
		putchar('0');
		return;
	}
	int posNum = qPos(j) - qPos(i-1);
	if( (j-i+1-posNum)%2==0 )
		putchar('+');
	else
		putchar('-');
}


int main(){
	while( scanf(" %d%d",&N,&K)!=EOF ){
		for(int i=0;i<=N;++i)
			zero[i] = pos[i] = 0;
		for(int i=1,v;i<=N;++i){
			scanf(" %d",&v);
			update(i,v);
		}
		char command;
		int I,J;
		for(int i=0;i<K;++i){
			scanf(" %c%d%d",&command,&I,&J);
			if( command=='C' )
				update( I , J );
			else
				query( I , J );
		}
		putchar('\n');
	}
} 
