#include<stdio.h>
#include<string.h>
#define MAX 30
struct r{
	int val;
	struct r *prev , *next;
} robot[MAX] , *iter , *tmp;

int main(){
	int n;
	while(scanf(" %d",&n)!=EOF){
	for(int i=0;i<n;++i) robot[i].val = i , robot[i].prev = NULL , robot[i].next = NULL;
	char work1[10] , work2[10];
	int from , to;
	while( scanf(" %s",work1)!=EOF && strcmp(work1,"quit")!=0 ){
		scanf(" %d%s%d",&from,work2,&to);
		bool variable = true;
		iter = &robot[from];
		while( iter!=NULL ){
			if( iter->val==robot[to].val ){
				variable = false;
				break;
			}
			iter = iter->prev;
		}
		if( !variable ) continue;
		iter = &robot[from];
		while( iter!=NULL ){
			if( iter->val==robot[to].val ){
				variable = false;
				break;
			}
			iter = iter->next;
		}
		if( !variable ) continue;
		iter = robot[from].prev;
		if( iter!=NULL ){
			iter->next = NULL;
		}
		if( strcmp(work1,"move")==0 ){
			iter = &robot[from];
			while( iter!=NULL ){
				tmp = iter->next;
				iter->next = NULL , iter->prev = NULL;
				iter = tmp;
			}
		}
		if( strcmp(work2,"onto")==0 ){
			iter = robot[to].next;
			robot[to].next = NULL;
			while( iter!=NULL ){
				tmp = iter->next;
				iter->next = NULL , iter->prev = NULL;
				iter = tmp;
			}
		}
		iter = &robot[to];
		while( iter->next!=NULL ) iter = iter->next;
		iter->next = &robot[from];
		robot[from].prev = iter;
	}
	for(int i=0;i<n;++i){
		printf("%d:",i);
		if( robot[i].prev==NULL ){
			iter = &robot[i];
			while( iter!=NULL ){
				printf(" %d",iter->val);
				iter = iter->next;
			}
		}
		putchar('\n');
	}
	}
} 
