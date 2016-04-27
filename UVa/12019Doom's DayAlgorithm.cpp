#include<cstdio>
using namespace std;

int month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
char week[7][10] = {
	"Friday" , "Saturday" , "Sunday" , "Monday" , "Tuesday" , "Wednesday" , "Thursday"
};

int main(){
	int __time;
	scanf(" %d",&__time);
	while( __time-- ){
		int m,d;
		scanf(" %d%d",&m,&d);
		int count = 0;
		for(int i=0;i<m-1;++i) count += month[i];
		count += d;
		printf("%s\n",week[count%7]);
	}
}
