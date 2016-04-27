#include<cstdio>
using namespace std;
int main(){
	unsigned long long num;
	unsigned long long mask[9] = {
	  100 , 10 , 100 , 100 , 100 , 10 , 100 , 100 , 10
	};
	char name[9][10] = {
	  "" , "shata" , "hajar" , "lakh" , "kuti" , "shata" , "hajar" , "lakh" , "kuti" 
	}; 
	int id = 1;
	while( scanf(" %llu",&num)!=EOF ){
		printf("%4d.",id);
		if( num==0 ){
			printf(" 0\n");
			++id;
			continue;
		}
		
		long long bangla[9];
		int top = -1;
		while( num ){
			++top;
			bangla[top] = num % mask[top];
			num /= mask[top];
		}
		while( top>0 ){
			if( bangla[top] )
				printf(" %llu %s",bangla[top],name[top]);
			else if( top==4 && bangla[top]==0 )
				printf(" %s",name[top]);
			--top;
		}
		if( bangla[0] ) printf(" %llu",bangla[0]);
		printf("\n");
		++id;
	}
}
