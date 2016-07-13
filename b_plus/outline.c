
//B+ TREE INSERTION 
//--------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//--------------------------------------------------------

struct node
{
	struct node *ptr[100],*pptr,*rsptr;
	int key[100],disp;
};
typedef struct node *NODE;

//--------------------------------------------------------

static int gName=0;
int disp =0;

//--------------------------------------------------------

NODE insert(NODE head, int info,int n);
NODE insertfix(NODE t,int info,int m);
NODE insertparent(NODE t,int key,NODE n1,int m);

//--------------------------------------------------------

int flag=0,flg=0;

//-------------------------------------------------------


NODE createleaf(int info,int n)
{
}

//--------------------------------------------------------

NODE search(NODE root,int info,int n)
{
}

//--------------------------------------------------------

NODE insertleaf(NODE t,int info)
{
}	

//--------------------------------------------------------

NODE insertfix(NODE t,int info,int m)	// m-1 ->max no of keys a node can have
{
}			

//--------------------------------------------------------

NODE insertparent(NODE t,int key,NODE n1,int m)
{
}

//--------------------------------------------------------




NODE insert(NODE head, int info,int n)
{
	NODE *temp=(struct node*)malloc(sizeof(struct node *));
	if(head == NULL)
	{
		head=temp;
		temp->key[disp++]=info;	
                
		head->ptr[0]=newnode;
		head=newnode;
		return newnode;
	}
	
}
	
//--------------------------------------------------------

void preorderDotDump (NODE root, FILE* outputFile)
{
	int i;	
	if (root != NULL) 
	{
		fprintf (outputFile, "node%d[label=\"<f0>%d",root->disp,root->key[0]);
			i=1;
			while( root->key[i]!='\0' )
			{			
				fprintf (outputFile, "|<f%d>%d",\
					i,root->key[i]);
				i++;			
			}
			fprintf (outputFile,"\"];\n");	
			i=0;
				while(root->ptr[i]!=NULL)
				{			
					fprintf (outputFile, "\"node%d\":f%d -> \"node%d\":f%d;\n", root->disp,0, root->ptr[i]->disp,0);
					i++;			
				}
			i=0;
        		while(root->ptr[i]!=NULL)
			{			
				preorderDotDump (root->ptr[i], outputFile);
				i++;			
			}
    	}
}

//--------------------------------------------------------

void dotDump(NODE root, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph tree{\n node [shape = record];\n",gName);
	if(flg==1)
		preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}
FILE *outputFile;

//--------------------------------------------------------

int main()
{
	int choice,key,m;	
	NODE head=NULL,new=NULL,root=NULL,p=NULL;
	int i;
	FILE *pipe; 
	printf("Read n\n"); 
	scanf("%d",&m);
	if(m<=1)
	{
		printf("\nEnter value greater than one\n\n");
		exit(0);
	}	
	while(1)
	{
		printf("1.Insert 2.Display\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:	
					printf("Read element\n");
					scanf("%d",&key);
					new=insert(head,key,m);
					root=head->ptr[0];
					outputFile = fopen("b+tree.dot", "a");
					dotDump (root,outputFile);
					fclose (outputFile);
					pipe=popen("dot -Tps b+tree.dot -o b+tree.ps","w");
					pclose(pipe);	
					break;			
				
			case 2:		if(flg==0)
					{
						root=head->ptr[0];
						outputFile = fopen("b+tree.dot", "a");
						dotDump (root,outputFile);
						fclose (outputFile);
						pipe=popen("dot -Tps b+tree.dot -o b+tree.ps","w");
						pclose(pipe);
					}	
					pipe=popen("evince b+tree.ps","r"); 
					pclose(pipe);
					break;
				
			default:exit(0);
		}
	}
return 0;
}
