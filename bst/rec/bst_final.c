#include<stdio.h>
#include<stdlib.h>

FILE *outputFile;
static int gName=0;
int pre[20],in[20],prex[20],inx[20];
static int p=0,c=0,px=0,cx=0;
struct node
{
    int data;
    struct node *lchild, *rchild;
};

struct node*  newnode(int datax)
{
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->data=datax;
    temp->lchild = NULL;
    temp->rchild = NULL;
    return temp;
}

int find(int in[], int val,int il,int ih )
{
    int i;
     for(i=il;i<=ih;i++)
	if(val==in[i])
	return i;
}        

struct node* create(int pre[],int in[], int il, int ih)
{	
	static int pl=0;	
	if(il>ih)
        return NULL;
	struct node* t=newnode(pre[pl++]); 
	if(il==ih)
	return t;
	 int key=find(in,t->data,il,ih);
	t->lchild=create(pre,in,il,key-1);
	t->rchild=create(pre,in,key+1,ih);
	return t;
}

void parr(int data)
{
    pre[p]=data;
    p++;
}

void iarr(int data)
{
    in[c]=data;
    c++;
}

void parrx(int data)
{
    prex[px]=data;
    px++;
}

void iarrx(int data)
{
    inx[cx]=data;
    cx++;
}

struct node * get_node()
{
    struct node *temp;
    temp = (struct node *) malloc(sizeof(struct node));
    temp->lchild = NULL;
    temp->rchild = NULL;
    return temp;
}

void insert(struct node *root, struct node *new_node)
{
    if (new_node->data < root->data)
    {
        if (root->lchild == NULL)
            root->lchild = new_node;
        else
            insert(root->lchild, new_node);
    }

    if (new_node->data > root->data)
    {
        if (root->rchild == NULL)
            root->rchild = new_node;
        else
            insert(root->rchild, new_node);
    }
}
void inorder(struct node *temp)
{
    if (temp != NULL)
    {
        inorder(temp->lchild);
        iarr(temp->data);
        inorder(temp->rchild);
    }
}
void preorder(struct node *temp)
{
    if (temp != NULL)
    {
        parr(temp->data);
        preorder(temp->lchild);
        preorder(temp->rchild);
    }
}

void inorderx(struct node *temp)
{
    if (temp != NULL)
    {
        inorderx(temp->lchild);
        iarrx(temp->data);
        inorderx(temp->rchild);
    }
}
void preorderx(struct node *temp)
{
    if (temp != NULL)
    {
        parrx(temp->data);
        preorderx(temp->lchild);
        preorderx(temp->rchild);
    }
}

void preorderDotDump (struct node *root, FILE* outputFile)

{

	if (root != NULL) 

	{

		fprintf (outputFile, "%d [label=%d,color=black];\n",root->data, root->data);

		if (root->lchild != NULL) 

		         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->lchild)->data);

		

        	if (root->rchild != NULL)

            		fprintf (outputFile, "%d -> %d;\n", root->data, root->rchild->data);

	//	if (root->pptr != NULL)

         //   		fprintf (outputFile, "%d -> %d [style = dashed];\n", root->data, (root->pptr)->data);

        	preorderDotDump (root->rchild, outputFile);

        	preorderDotDump (root->lchild, outputFile);

    	}

}



void dotDump(struct node *root, FILE *outFile)

{

	gName++;

	fprintf (outFile, "digraph BST {\n",gName);

	

	preorderDotDump (root, outFile);

    	fprintf (outFile, "}\n");

}

//---------------------------------------
int main()
{
    FILE *pipe;
    int i,n,ch;
    struct node *new_node, *root, *tmp, *parent;
    struct node *get_node();
    root = NULL;
   //printf("Enter the number of nodes\n");
    scanf("%d",&n);
    outputFile=fopen("bst.dot","w");
    fclose(outputFile);
    for(i=0; i<n; i++)
    {
        new_node = get_node();
        scanf("%d",&new_node->data);
        //new_node->data=rand() % 1000 + 1;
  //    printf("%d\n",new_node->data);
	if (root == NULL) /* Tree is not Created */
	{
            root = new_node;
	    outputFile = fopen ("bst.dot", "a");
        }
        else
            insert(root, new_node);
             outputFile = fopen ("bst.dot", "a");
	if (outputFile != NULL) 
	{
  		dotDump (root,  outputFile);
        }

        fclose (outputFile);

    }
//--------------------------------------
    preorder(root);
    inorder(root);
//--------------------------------------
/*    printf("Preorder\n");
    for(i=0; i<p; i++)
       printf("%d\n",pre[i]);
    printf("Inorder\n");
    for(i=0; i<c; i++)
        printf("%d\n",in[i]);*/
   struct node *rootx=create(pre,in,0,n-1);
	inorderx(rootx);
	preorderx(rootx);
        scanf("%d",&ch);
	while(1)
	{
                
		switch(ch)
		{
			case 1: 
                         	printf("preorderx\n");
				for(i=0; i<px; i++)
        			printf("%d\n",prex[i]);
				printf("inorderx\n");
				for(i=0; i<cx; i++)
			       printf("%d\n",inx[i]);
				break;

			case 2: 
				pipe=popen("dot -Tps bst.dot -o bst.ps","w");
                                pclose(pipe);
                                pipe=popen("evince bst.ps","r");
                                pclose(pipe);
                                exit(0);
                                break;


		}
	}
			


}

