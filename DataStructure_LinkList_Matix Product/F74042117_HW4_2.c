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
void transpose(listnode amatrix){
	int i,j,m,n,numhead,count=-1,temprow,tempcol;
	listnode first,head=amatrix->right,temp;
	temprow = amatrix->u.entry.row;
	tempcol = amatrix->u.entry.col;
	
	for(i=0;i<amatrix->u.entry.col;i++){
		for(temp=head->down;temp!=head;temp=temp->down){
			for(j=count;j<temp->u.entry.row-1;j++)printf("0 ");
			printf("%d ",temp->u.entry.value);
			count = temp->u.entry.row;
		}
		for(j=count;j<temprow-1;j++)printf("0 ");
		count = -1;
		printf("\n");
		head = head->u.next;
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
	listnode ahdnode[maxsize],get;
	get = mread(ahdnode);
	printf("\n");
	transpose(get);
	merase(&get);
	return 0;
}
