#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 500 
typedef enum{
	head,entry
}tagfield;
typedef struct{
	int row;
	int col;
	int value;
}entrynode;
struct node{
	struct node *down;
	struct node *right;
	tagfield tag;
	union{
		struct node *next;
		entrynode entry;
	}u;
};
typedef struct node *listnode;
listnode mread(listnode ahdnode[]){
	int **matrix;
	int i,j,k,m,n,p,row,col,value,currentrow,numrow,numcol,numterm,numhead,count=0;
	listnode first,temp,last;
	scanf("%d%d",&m,&n);
	matrix = (int **)calloc(m,sizeof(int *));
	for(i=0;i<m;i++)
		matrix[i] = (int *)calloc(n,sizeof(int));
		
	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			scanf("%d",&matrix[i][j]);
			if(matrix[i][j]!=0)count++;
		}
	
	numhead = (m>n)?m:n;
	
	first = (listnode)malloc(sizeof(struct node));
	first->tag = entry;
	first->u.entry.row = m;
	first->u.entry.col = n;
	first->u.entry.value = count;
	if(!numhead)first->right = first;
	else{
		for(i=0;i<numhead;i++){
			ahdnode[i] = (listnode)malloc(sizeof(struct node));
			ahdnode[i]->tag = head;
			ahdnode[i]->right = ahdnode[i];
			ahdnode[i]->u.next = ahdnode[i];					//hdnode initialize
		}
		currentrow = 0;
		last = ahdnode[0];
	
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				if(matrix[i][j]!=0){								//read
					row = i;
					col = j;
					value = matrix[i][j];
					if(row>currentrow){
						last -> right = ahdnode[currentrow];
						currentrow = row;
						last = ahdnode[row];
					}
					temp = (listnode)calloc(1,sizeof(struct node));
					temp -> tag = entry;
					temp -> u.entry.row = row;
					temp -> u.entry.col = col;
					temp -> u.entry.value = value;
					last -> right = temp;
					last = temp;
					ahdnode[col] -> u.next -> down = temp;
					ahdnode[col] -> u.next = temp; 
				}
			}
		}
		last->right = ahdnode[currentrow];
		for(k=0;k<numhead;k++)
			ahdnode[k]->u.next->down=ahdnode[k];
		for(k=0;k<numhead-1;k++)
			ahdnode[k]->u.next=ahdnode[k+1];
		ahdnode[numhead-1]->u.next=first;
		first->right=ahdnode[0];
	}
		
	for(i=0;i<m;i++)
			free(matrix[i]);
	free(matrix);
	
	return first;
}
listnode mmult(listnode amatrix,listnode bmatrix){
	int i,j,count=0;
	listnode ahead = amatrix->right;
	listnode bhead = bmatrix->right;
	listnode atemp=ahead->right,btemp;
	for(i=0;i<amatrix->u.entry.row;i++){
		for(j=0;j<bmatrix->u.entry.col;j++){
			for(atemp=ahead->right;atemp!=ahead;atemp=atemp->right){
				for(btemp=bhead->down;btemp!=bhead;btemp=btemp->down){
					if(atemp->u.entry.col==btemp->u.entry.row){
						count += (atemp->u.entry.value)*(btemp->u.entry.value);
					}
				}
			}
			printf("%d ",count);
			bhead = bhead->u.next;
			count = 0;
		}
		printf("\n");
		bhead = bmatrix->right;				//必須要重製 因為bhead->u.next為first 要在first->right才為head的第一個 
		ahead = ahead->u.next;
	}
}
void merase(listnode *temp){
	listnode x,y,head = (*temp)->right;
	int i;
	for(i=0;i<(*temp)->u.entry.row;i++){
		y = head->right;
		while(y!=head){
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}
	y = head;
	while(y!=(*temp)){
		x = y;
		y = y->u.next;
		free(x);
	}
	free(*temp);
	*temp = NULL;
}
int main(){
	listnode ahdnode[maxsize],bhdnode[maxsize],get,get2;
	get = mread(ahdnode);
	get2 = mread(bhdnode);
	if(get->u.entry.col!=get2->u.entry.row){
		printf("error!!\n");
		return 0;
	}
	printf("\n");
	mmult(get,get2);
	merase(&get);
	merase(&get2);
	return 0;
}
