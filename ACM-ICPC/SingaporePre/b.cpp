#include <cstdio>
#include <cstring>
using namespace std;

int ori[4][4];
int tmp[4][4];

void rotate(){
	for(int i=0 ; i<4 ; ++i)
		for(int j=0 ; j<4 ; ++j)
			tmp[i][j] = ori[3-j][i];
	for(int i=0 ; i<4 ; ++i)
		for(int j=0 ; j<4 ; ++j)
			ori[i][j] = tmp[i][j];
}

void up(){
	for(int i=0 ; i<4 ; ++i)
		for(int j=0 ; j<4 ; ++j){
			if( ori[i][j]==0 ) continue;
			for(int k=1 ; i+k<4 ; ++k)
				if( ori[i+k][j]!=0 ){
					if( ori[i+k][j] == ori[i][j] )
						ori[i+k][j] = 0 , ori[i][j] <<= 1;
					break;
				}
		}
	for(int i=0 ; i<4 ; ++i)
		for(int j=0 ; j<4 ; ++j){
			int b = 0;
			for(int k=0 ; i+k<4 ; ++k)
				if( ori[i+k][j] ){
					b = ori[i+k][j];
					ori[i+k][j] = 0;
					break;
				}
			ori[i][j] = b;
		}
}

void left(){
	rotate(); up(); rotate(); rotate(); rotate();
}
void right(){
	rotate(); rotate(); rotate(); up(); rotate();
}
void down(){
	rotate(); rotate(); up(); rotate(); rotate();
}

int main(){
	for(int i=0 ; i<4 ; ++i)
		for(int j=0 ; j<4 ; ++j)
			scanf("%d",&ori[i][j]);

	int way;
	scanf("%d",&way);
	if( way==0 ) left();
	else if( way==1 ) up();
	else if( way==2 ) right();
	else down();

	for(int i=0 ; i<4 ; ++i){
		for(int j=0 ; j<4 ; ++j)
			printf("%d ",ori[i][j]);
		printf("\n");
	}
	return 0;
}