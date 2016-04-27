#include<cstdio>
#include<cstring>
using namespace std;
	char map[10][10];
	int x,y,n;
	bool insert;
void task();
void write(char output){
	if( !insert ){
		map[x][y] = output;
	}
	else{
		for(int i=9;i>y;--i) map[x][i] = map[x][i-1];
		map[x][y] = output;
	}
	if( y<9 ) ++y;
	return;
};
int main(){
	int Case = 1;
	while( scanf(" %d",&n)!=EOF && n ){
		x=0,y=0;
		memset(map,' ',sizeof(map));
		insert = false;
		getchar();
		while( n-- ){
			int input;
			while( (input=getchar())!=-1 && input!='\n' ){
				if( input=='^' ){
					task();
				}
				else{
					write(input);
				}
			}
		}
		printf("Case %d\n+----------+\n",Case++);
		for(int i=0;i<10;++i){
			putchar('|');
			for(int j=0;j<10;++j) putchar(map[i][j]);
			putchar('|');
			putchar('\n');
		}
		printf("+----------+\n");
	}
}
void task(){
	int input = getchar();

	if( input>='0' && input<='9' ){
		x=input-'0';
		input=getchar();
		y=input-'0';
	}
	else if( input=='b' ){
		y=0;
	}
	else if( input=='c' ){
		memset(map,' ',sizeof(map));
	}
	else if( input=='d' ){
		if( x<9 ) ++x;
	}
	else if( input=='e' ){
		for(int i=y;i<10;++i) map[x][y] = ' ';
	}
	else if( input=='h' ){
		x=0,y=0;
	}
	else if( input=='i' ){
		insert = true;
	}
	else if( input=='l' ){
		if( y>0 ) --y;
	}
	else if( input=='o' ){
		insert = false;
	}
	else if( input=='r' ){
		if( y<9 ) ++y;
	}
	else if( input=='u' ){
		if( x>0 ) --x;
	}
	else if( input=='^' ){
		write('^');
	}
}
