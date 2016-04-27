#include<cstdio>
using namespace std;
int main(){
	char input;
	int j4000 , j3 , j11;
	bool odd;
	bool first = true;
	while( (input=getchar()) && input!=EOF ){
		j4000 = input-'0',
		j3 = j4000,
		j11 = j4000,
		odd = false;
		while( (input=getchar()) && input!='\n' ){
			int val = input - '0';
			j4000 = (j4000*10 + val)%10000;
			j3 = j3+val;
			if( odd ){
				j11 += val;
			} 
			else{
				j11 -= val;
			}
			odd = !odd;
		}
		if( first )
			first = false;
		else 
			printf("\n");
		bool leap = false , ordinary = true;
		if( j4000%4==0 && j4000%100!=0 || j4000%400==0 ){
			leap = true;
			printf("This is leap year.\n");
			ordinary = false;
		}
		if( j3%3==0 && j4000%5==0 ){
			printf("This is huluculu festival year.\n");
			ordinary = false;
		}
		if( leap && j4000%5==0 && j11%11==0 ){
			printf("This is bulukulu festival year.\n");
			ordinary = false;
		}
		if( ordinary ){
			printf("This is an ordinary year.\n");
		}
	}
}
