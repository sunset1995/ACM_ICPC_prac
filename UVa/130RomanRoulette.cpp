#include <cstdio>
using namespace std;

struct Roman{
	int id , next ,pre;
} people[105];

int left , nowAt;
int n,k;
int count(int from){
	int step = (k-1)%left;
	for(int i=0;i<step;++i)
		from = people[from].next;
	return from;
}

int main(){
	while( scanf(" %d%d",&n,&k)!=EOF && n && k ){
		for(int i=0;i<n;++i){
			people[i].id = i;
			people[i].next = i+1;
			people[i].pre = i-1;
		}
		people[n-1].next = 0;
		people[0].pre = n-1;

		left = n , nowAt = 0;
		while( left>1 ){
			//for(int i=0,j=nowAt;i<left;++i,j = people[j].next)
			//	printf("%d ",j);
			//printf("\n");
			int killed = count( nowAt );
			--left;
			int bury = count( people[killed].next );
			//printf("kill %d\nbury%d\n",killed,bury);

			people[ people[bury].pre ].next = people[ bury ].next;
			people[ people[bury].next ].pre = people[ bury ].pre;

			if( people[killed].pre!=bury || left==1 ){
				people[ people[killed].pre ].next = bury;
				people[ bury ].pre = people[killed].pre;
			}
			if( people[killed].next!=bury || left==1 ){
				people[ people[killed].next ].pre = bury;
				people[ bury ].next = people[killed].next;
			}
			nowAt = people[bury].next;
			//for(int i=0,j=nowAt;i<left;++i,j = people[j].next)
			//	printf("%d ",j);
			//printf("\n\n");
		}
		int ans = 1+((n-nowAt)%n);
		printf("%d\n",ans);
	}
}