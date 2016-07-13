#include<stdio.h>
#include<stdlib.h>

struct node
{
	struct node *left,*right,*parent;
	char color;
	int data;
}node;

void rbinsert(int x)
{
	struct node *p,*q;
	struct node *temp=(struct node*)malloc(sizeof(struct node*));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
	temp->color='R';
	p=root;


	if(root==NULL)
	{
		root=temp;
		root->color='B';
		return;
	}

	while(p!=NULL)
	{
		q=p;
		if(temp->data < p->data)
			p=p->left;
		
		else
			p=p->right;
	}
	temp->parent=q;
	if(q==NULL)
	{
		


int main()
{
	int i,x,ch;
	struct node *root=NULL;
	while(1)
	{
		printf("1.Insert 2.Exit\n");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				printf("Enter the node value\n");
				scanf("%d",&x);
				rbinsert(root,x);
				break;
			
			case 2: exit(0);
		}
	}

}



