#include<cstdio>
using namespace std;
float rec[10][4];
int main(){
	while(1){
		char isR;
		int n=0;
		while( scanf(" %c",&isR)!=EOF && isR=='r' && scanf(" %f%f%f%f",&rec[n][0],&rec[n][3],&rec[n][1],&rec[n][2]) ){
			++n;
		}
		if(n==0) break;
		int nowPoint = 1;
		float x,y;
		while( scanf(" %f%f",&x,&y)!=EOF ){
			if(x==(float)9999.9 && y==(float)9999.9) break;
			bool haveIn = false;
			for(int i=0;i<n;++i)
				if(x>rec[i][0] && x<rec[i][1] && y>rec[i][2] && y<rec[i][3]){
					printf("Point %d is contained in figure %d\n",nowPoint,i+1);
					haveIn = true;
				}
			if(!haveIn)
				printf("Point %d is not contained in any figure\n",nowPoint);
			++nowPoint;
		}
	}
}
