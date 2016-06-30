#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//---------------------------------------------------------------------------------------------
struct node
{
	int temptype;		// '0' is cold blooded and '1' is warm blooded
	int birth;			// '0' is no birth '1' is birth
}animal;
//---------------------------------------------------------------------------------------------
struct characteristic
{
	struct characteristic *left;
	struct characteristic *right;
	char name[20];	
}newnode;
//---------------------------------------------------------------------------------------------
struct characteristic* getnode()
{
	struct characteristic *new= (struct characteristic*) malloc (sizeof(struct characteristic));
	new->left=NULL;
	new->right=NULL;
	return new;
}
//---------------------------------------------------------------------------------------------
void decision(int temptype, int birth)
{
	struct characteristic *temp=getnode();
	strcpy(temp->name,"temperature");
	if(temptype==0)		//cold
	{
		struct characteristic *rchild=getnode();
		temp->left=NULL;
		strcpy(rchild->name,"Non Mammal\n");
		printf("%s\n",rchild->name);
	}
	else if(temptype==1)		//cold
	{
		struct characteristic *lchild=getnode();
		temp->right=NULL;
		strcpy(lchild->name,"Gives Birth");
		temp->left=lchild;
		
		if(birth==1)
		{
			struct characteristic *leftchild=getnode();
			strcpy(leftchild->name,"Mammal");
			lchild->left=leftchild;
			lchild->right=NULL;
			printf("%s\n",leftchild->name);
		}
		else
		{
			struct characteristic *rrchild=getnode();
			strcpy(rrchild->name,"Non Mammal");
			lchild->right=rrchild;
			lchild->left=NULL;
			printf("%s\n",rrchild->name);
		}
		
				

    }
 }
//---------------------------------------------------------------------------------------------
int main()
{
	int i;
	printf("Enter the characteristics\n");
	printf("I. Temperature\n0-> Cold 1-> Warm\n");
	scanf("%d",&animal.temptype);
	printf("II. Gives Birth\n0-> No 1-> Yes\n");
	scanf("%d",&animal.birth);
	decision(animal.temptype,animal.birth);
	return 0;
}
//---------------------------------------------------------------------------------------------
