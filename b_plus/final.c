
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key[2],count;
	struct node *ptr[3],*rsptr,*pptr;
};

typedef struct node * NODE;

NODE root;
static int gName=0;
FILE *outFile;
NODE  getnode()
{
    int i;
    struct node* new;
    new=(struct node*)malloc(sizeof(struct node));
    for (i = 0; i < 2; i++)
    {
        new->key[i]=0;
    }
    new->count = 0;
    for (i = 0; i < 3; i++)
    {
        new->ptr[i] = NULL;
    }
    return new;
}
//to create a node
struct node* createnode()
{
	struct node *temp;
	temp= getnode();
	temp->pptr=NULL;
	temp->ptr[0]=NULL;
	temp->ptr[1]=NULL;
	temp->ptr[2]=NULL;
	temp->count=0;
	temp->rsptr=NULL;
	return temp;
}

//To find the node where the insertion is supposed to take place
NODE find(int d)
{
	int i , n;
	NODE c = root;

	while(c->ptr[0] != NULL)
	{	
		n = c->count;
		for(i = 0; i<n; i++)
		{
			if(c->key[i] > d)
			{
				c = c->ptr[i];
				return c;
			}
		}
		c = c->ptr[c->count];
		
	}
	return c;
}

//The function to add a value to an existing node in the tree
NODE addinto(NODE n,int v, NODE p)
{
	if(n->count==1)
	{
		if(n->key[0]>v)
		{
			n->key[1]=n->key[0];
			n->key[0]=v;
			n->ptr[2]=n->ptr[1];
			n->ptr[1]=p;
			n->count=n->count+1;
			return n;
		}
		else
		{
			n->key[1]=v;
			n->ptr[2]=p;
			n->count=n->count+1;
			return n;
		}
	}
	else if(n->count==0)
	{
		n->key[0]=v;
		n->ptr[1]=p;
		n->count=n->count+1;
		return n;
	}
}

//Funtion to insert a new key to the tree
NODE insert_entry(NODE l,int v,NODE p)
{
	if(l->count<2)
	{
		l=addinto(l,v,p);
	}
	else
	{
		NODE l1;
		l1=getnode();
		int v1,m;
		v1=l->key[1];
		m=2;
		if(l->ptr[0]==NULL)
		{
			l1 = addinto(l1,l->key[1],l->ptr[1]);
			l->key[1]=0;
			l->count--;
			if(v<v1)
			{
				l=addinto(l,v,p);
			}
			else
			{
				l1 = addinto(l1,v,p);
			}
		}
		else
		{
			l1=addinto(l1,v,p);
			l1->ptr[0]=l->ptr[2];
			l->ptr[2]->pptr=l1;
			l->key[1]=0;
			l->count--;

		}
		if(l!=root)
		{
			root=insert_entry(root,v1,l1);
		}
		else
		{
			NODE nroot;
			nroot=getnode();
			nroot = addinto(nroot,v1,l->ptr[1]);
			nroot->ptr[0]=l;
			nroot->ptr[1]=l1;
			l->pptr=nroot;
			l1->pptr=nroot;
			root=nroot;
		}
		if(l->ptr[0]==NULL)
		{
			l->ptr[2]=l1;
			l1->rsptr = l->rsptr;
			l->rsptr = l1;
		}

	}
	return root;

}


struct node* insert(int v,struct node *p)
{
	struct node *l;
	l=find(v);
	root=insert_entry(l,v,p);
	return root;
}

//function to traverse the B+ tree
void traverse(struct node * R)
{
	int i;	
	while(R != NULL) {
		i=0;
		while(i < R->count) {
			printf("%d\t",R->key[i]);
			i++;
		}
		R=R->ptr[2];
	}
}

//to print the tree
void count(struct node *  R) 
{
	while(R->ptr[0] != NULL)
		R=R->ptr[0];
	traverse(R);
	return;
}
void preorderDotDump(NODE root,FILE *outFile)
{
	int i;
	if(root!=NULL)
	{
		fprintf(outFile,"node%d[label=\"<f0>%d",root->count,root->key[0]);
		i=1;
		while(root->key[i]!=0)
		{
			fprintf(outFile,"|<f%d>%d",i,root->key[i]);
			i++;
		}
		fprintf(outFile,"\"];\n");
		i=0;
		while(root->ptr[i]!=NULL && i<2)
		{
			fprintf(outFile,"\"node%d\":f%d->\"node%d\":f%d;\n",root->count,0,root->ptr[i]->count,0);
			i++;
		}
		i=0;
		while(root->ptr[i]!=NULL && i<2)
		{
			preorderDotDump(root->ptr[i],outFile);
			i++;
		}
	}
}
void dotDump(NODE root,FILE *outFile)
{
	gName++;
	fprintf(outFile,"digraph tree{\nnode[shape=record];\n",gName);
	preorderDotDump(root,outFile);
	fprintf(outFile,"}\n");
}
FILE *outFile;
void main()
{
	FILE *pipe;
	int ch,val;
	root=getnode();
	
	while(1)
	{
		printf("Enter your choice \n 1.insert \n 2.display \n 3.return\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("Enter the value you want to insert\n");
				scanf("%d",&val);
				root=insert(val,root);
				outFile=fopen("bplus.dot","w");
	fclose(outFile);
	outFile=fopen("bplus.dot","a");
	if(outFile!=NULL)
		dotDump(root,outFile);
	fclose(outFile);
				break;
			case 2:	//display(root);

				pipe=popen("dot -Tps bplus.dot -o bplus.ps","w");
	pclose(pipe);
	pipe=popen("evince bplus.ps","r");
	pclose(pipe);
				break;
			case 3: return;
		}
	}
	
}
