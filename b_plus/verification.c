#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct node
{
	int info[4];
	struct node *links[5],*parent,*next;
};
typedef struct node* NODE;
NODE insert(NODE,int,int);
int g=0;
NODE getNode()
{
	NODE a=(NODE)malloc(sizeof(struct node));
	int i;
	for(i=0;i<4;i++){
		a->links[i]=NULL;
		a->info[i]=-1;
		}
		a->parent=NULL;
	a->next=NULL;
		return a;
}


void sort(int a[])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=i+1;j<4;j++)
			if(a[i]>a[j])
			{
				int temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
}

NODE search(NODE root,int key)
{
	int count=0,count1=0,i;
	for(i=0;i<5;i++)
	{
		if(root->links[i]!=NULL)
			count++;
	}
	if(count==0||count==1)
		return root;
	if(count==2)
	{
		if(key<root->info[3])
		{
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					search(root->links[i],key);
					break;
				}
			}
		}
		else
		{
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					count1++;
					if(count1==2)
					{
						search(root->links[i],key);
						break;
					}
				}
			}
		}	
	}
	if(count==3)
	{
		if(key<root->info[2])
		{
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					search(root->links[i],key);
					break;
				}
			}
		}
		else if(key<root->info[3])
		{
			count1=0;
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					count1++;
					if(count1==2)
					{
						search(root->links[i],key);
						break;
					}
				}
			}
		}
		else
		{
			count1=0;
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					count1++;
					if(count1==3)
					{
						search(root->links[i],key);
						break;
					}
				}
			}

		}	
	}
	if(count==4)
	{
		if(key<root->info[1])
		{
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					search(root->links[i],key);
					break;
				}
			}
		}
		
		else if(key<root->info[2])
		{
			count1=0;
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					count1++;
					if(count1==2)
					{
						search(root->links[i],key);
						break;
					}
				}
			}
		}
		
		else if(key<root->info[3])
		{
			count1=0;
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					count1++;
					if(count1==3)
					{
						search(root->links[i],key);
						break;
					}
				}
			}
		}
		
		else
		{
			count1=0;
			for(i=0;i<5;i++)
			{
				if(root->links[i]!=NULL)
				{
					count1++;
					if(count1==4)
					{
						search(root->links[i],key);
						break;
					}
				}
			}
	
		}
	}
		
}

NODE split(NODE temp)
{
	NODE temp1,temp2,temp3,temp5;
	int count=0,count1=0,i,j,var,up,low,var1;
	for(i=0;i<4;i++)
		if(temp->info[i]!=-1)
			count++;
	if(count==4)
	{
			temp1=getNode();
			temp2=getNode();
			temp1->info[0]=temp->info[0];
			temp1->links[0]=temp->links[0];
			temp1->links[1]=temp->links[1];
			if(temp->links[0]==NULL&&temp->links[1]==NULL&&temp->links[2]==NULL&&temp->links[3]==NULL&&temp->links[4]==NULL)
			{
				temp2->info[0]=temp->info[1];
			}
			temp2->info[1]=temp->info[2];
			temp2->info[2]=temp->info[3];
			temp2->links[0]=temp->links[2];
			temp2->links[1]=temp->links[3];
			temp2->links[2]=temp->links[4];
			temp1->parent=temp->parent;
			temp2->parent=temp->parent;
			temp1->next=temp2;
			for(i=0;i<5;i++)
			{
				if(temp->links[i]!=NULL&&i<2)
					temp->links[i]->parent=temp1;
				else if(temp->links[i]!=NULL&&i>=2)
					temp->links[i]->parent=temp2;
			}
			sort(temp1->info);
			sort(temp2->info);

		if(temp->parent==NULL)
		{
			NODE temp3=getNode();
			temp3->info[0]=temp->info[1];
			temp3->links[0]=temp1;
			temp3->links[1]=temp2;
			temp1->parent=temp3;
			temp2->parent=temp3;
			return temp3;
		}
		else
		{
			for(i=0;i<5;i++)
			{
				if(temp->parent->links[i]==temp)
				{	var=i;
					break;
				}
			}
			for(i=0;i<5;i++)
			{
				if(temp->parent->links[i]==NULL)
				{
					var1=i;
					break;
				}
			}
			if(var1>var)
			{
				for(i=var1;i>var;i--)
				{
					temp->parent->links[i]=temp->parent->links[i-1];
				}
				temp->parent->links[var+1]=NULL;
			}
			else
			{
				for(i=var1;i<var;i++)
				{
					temp->parent->links[i]=temp->parent->links[i+1];
				}
				temp->parent->links[var-1]=NULL;
			}		
			for(i=0;i<5;i++)
				if(temp->parent->links[i]==temp)
					temp->parent->links[i]=NULL;
			for(i=0;i<5;i++)
				if(temp->parent->links[i]==NULL)
				{
					temp->parent->links[i]=temp1;
					break;
				}
			for(i=0;i<5;i++)
				if(temp->parent->links[i]==NULL)
				{
					temp->parent->links[i]=temp2;
					break;
				}
			
			temp5=insert(temp->parent,temp->info[1],0);	
			return temp5;
			while(temp5->parent!=NULL)
				temp5=temp5->parent;
		}
	
	}
	while(temp->parent!=NULL)
		temp=temp->parent;
	return temp;
}



NODE insert(NODE root,int key,int f)
{
	NODE temp,temp1;
	int i,count=0;
	if(f)
		temp=search(root,key);
	else 
		temp=root;
	for(i=0;i<4;i++)
		if(temp->info[i]==-1)
		{
			temp->info[i]=key;
			sort(temp->info);
			break;
		}
	for(i=0;i<4;i++)
	{
		if(temp->info[i]!=-1)
			count++;
	}
	if(count==4)
	{
		if(temp->parent==NULL)
		{
			root=split(temp);
			sort(root->info);
			while(root->parent!=NULL)
				root=root->parent;

			return root;
		}
		else
		{
			temp1=split(temp);
			sort(temp1->info);
			while(temp1->parent!=NULL)
				temp1=temp1->parent;
			return temp1;
		}
	}
	while(root->parent!=NULL)
		root=root->parent;
	return root;
}


void preorder(NODE root)
{
	int i,flag=0;
	if(root->links[0]==NULL&&root->links[1]==NULL&&root->links[2]==NULL&&root->links[3]==NULL&&root->links[4]==NULL)
	{
		for(i=0;i<4;i++)
			if(root->info[i]!=-1)
				printf("%d ",root->info[i]);
			printf("\n");
	}
		for(i=0;i<5;i++)
			if(root->links[i]!=NULL)
				preorder(root->links[i]);
}

int maxi(int a,int b)
{
	if(a>b)return a;
	else return b;
}

int height(NODE root)
{
	if(root==NULL)
		return -1;
	int i,ht;
	ht=maxi(1+height(root->links[0]),1+height(root->links[1]));
	ht=maxi(ht,1+height(root->links[2]));
	ht=maxi(ht,1+height(root->links[3]));
	ht=maxi(ht,1+height(root->links[4]));
	return ht;
}


int verify(NODE root)
{
	int key_count=0,child_count=0;
	int i,j,flag=1,count=0;
	for(i=0;i<4;i++)
		if(root->info[i]!=-1)
			key_count++;
	for(i=0;i<4;i++)
	{
		if(height(root->links[i])!=height(root->links[i+1]))
			return -1;
	}
	for(i=0;i<5;i++)
	{
		if(root->links[i]!=NULL)
		{
			flag=verify(root->links[i]);
			if(flag==-1)
			{
				printf("NOT GOOD");
				exit(0);
			}
		}
	}

	for(i=0;i<5;i++)
	{
		if(root->links[i]!=NULL)
		{
			count++;
			for(j=0;j<4;j++)
				if(root->links[i]->info[j]!=-1)
					child_count++;
			if(key_count==1&&child_count==1)
			{
				if(count==1)
				{
					if(root->info[3]>=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[3]<=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}
			}
			else if(key_count==1&&child_count==2)
			{
				if(count==1)
				{
					if(root->info[3]>=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[3]<=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}
			}
			else if(key_count==1&&child_count==3)
			{
				if(count==1)
				{
					if(root->info[3]>=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[3]<=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}

			}
			else if(key_count==2&&child_count==1)
			{
				if(count==1)
				{
					if(root->info[2]>=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[2]<=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}
				if(count==3)
				{
					if(root->info[3]<=root->links[i]->info[3])
						return 1;
					else 
						return -1;
				}
			}
			else if(key_count==2&&child_count==2)
			{
				if(count==1)
				{
					if(root->info[2]>=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[2]<=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}
				if(count==3)
				{
					if(root->info[3]<=root->links[i]->info[2])
						return 1;
					else 
						return -1;
				}

			}
			else if(key_count==2&&child_count==3)
			{
				if(count==1)
				{
					if(root->info[2]>=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[2]<=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}
				if(count==3)
				{
					if(root->info[3]<=root->links[i]->info[1])
						return 1;
					else 
						return -1;
				}

			}
			else if(key_count==3&&child_count==1)
			{
				if(count==1)
				{
					if(root->info[1]>=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[1]<=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}
				if(count==3)
				{
					if(root->info[1]<=root->links[i]->info[3])
						return 1;
					else 
						return -1;
				}
				if(count==4)
				{
					if(root->info[1]<=root->links[i]->info[3])
						return 1;
					else
						return -1;
				}

			}
			else if(key_count==3&&child_count==2)
			{
				if(count==1)
				{
					if(root->info[1]>=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[1]<=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}
				if(count==3)
				{
					if(root->info[1]<=root->links[i]->info[2])
						return 1;
					else 
						return -1;
				}
				if(count==4)
				{
					if(root->info[1]<=root->links[i]->info[2])
						return 1;
					else
						return -1;
				}

			}
			else if(key_count==3&&child_count==3)
			{
				if(count==1)
				{
					if(root->info[1]>=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}
				if(count==2)
				{
					if(root->info[1]<=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}
				if(count==3)
				{
					if(root->info[1]<=root->links[i]->info[1])
						return 1;
					else 
						return -1;
				}
				if(count==4)
				{
					if(root->info[1]<=root->links[i]->info[1])
						return 1;
					else
						return -1;
				}

			}
		}
	}
	return 1;
}

/*void preorderDotDump (NODE root, FILE* outputFile)
{
	int i;	
	if (root != NULL) 
	{
		
			
		fprintf (outputFile, "node%d[label=\"<f0>%d",root->disp,root->info[0]);
			
			i=1;
			while(root->key[i]!='\0')
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

void dotDump(NODE root, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph tree{\n node [shape = record];\n",gName);
	if(flg==1)
		preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}*/

FILE *outputFile;
int main(int argc, char** argv)
{                                      
		NODE root,temp;
		FILE *pipe;
		int ch,i,item,val;
		int x;
		root=getNode();
		if (argc != 2)
		{
			printf(" need one argument  \n");
			exit(0);
		}

		outputFile = fopen ("bst.dot", "w");
 //   		fclose (outputFile);
		val = atoi(argv[1]);
		for(i=0;i<val;i++)
		{
			item=random()%100000;
		printf("%d\t",item);
		root=insert(root,item,1); 
		}
		printf("\n");
		preorder(root);
		/*outputFile = fopen("b+tree.dot", "a");
		dotDump (root,outputFile);
		fclose (outputFile);
		pipe=popen("dot -Tps b+tree.dot -o b+tree.ps","w");
		pclose(pipe);	
		pipe=popen("evince b+tree.ps","r"); 
		pclose(pipe);*/
		if(verify(root))
			printf("verified\n");
		else
			printf("NOT GOOD\n");
		return 0;
}
