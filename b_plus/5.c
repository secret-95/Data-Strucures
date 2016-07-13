#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define true 1
#define false 0
//--------------------------------------------------------------------------------------------------------------------
struct node
{
    int key[5];
    struct node *ptr[6];
    int leaf;
    int n;
}*root=NULL,*np = NULL, *x = NULL;
//--------------------------------------------------------------------------------------------------------------------
static int gName=0;
FILE *outFile;
//--------------------------------------------------------------------------------------------------------------------
struct node* getnode()
{
    int i;
    struct node* new;
    new=(struct node*)malloc(sizeof(struct node));
    for (i = 0; i < 5; i++)
    {
        new->key[i];
    }
    new->leaf = true;
    new->n = 0;
    for (i = 0; i < 6; i++)
    {
        new->ptr[i] = NULL;
    }
    return new;
}
//--------------------------------------------------------------------------------------------------------------------
void sort(int *p, int n)
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (p[i] > p[j])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------
int split(struct node *x, int i)
{
    int j, mid;
    struct node *nonleaf, *nleaf, *y;
    nleaf = getnode();
    nleaf->leaf = true;
    if (i == -1)
    {
        mid = x->key[2];
        x->key[2] = 0;
        x->n--;
        nonleaf = getnode();
        nonleaf->leaf = false;
        x->leaf = true;
	nleaf->key[0]=mid;
	nleaf->ptr[0]=x->ptr[2];
        for (j = 3; j < 5; j++)
        {
            nleaf->key[j - 2] = x->key[j];
            nleaf->ptr[j - 2] = x->ptr[j];
            nleaf->n++;
            x->key[j] = 0;
            x->n--;
        }
	
        for(j = 0; j < 6; j++)
        {
            x->ptr[j] = NULL;
        }
        nonleaf->key[0] = mid;
        nonleaf->ptr[nonleaf->n] = x;
        nonleaf->ptr[nonleaf->n + 1] = nleaf;
        nonleaf->n++;
        root = nonleaf;
    }
   else
    {
        y = x->ptr[i];
        mid = y->key[2];
        y->key[2] = 0;
        y->n--;
        for (j = 3; j <5; j++)
        {
            nleaf->key[j - 3] = y->key[j];
            nleaf->n++;
            y->key[j] = 0;
            y->n--;
        }
        x->ptr[i + 1] = y;
        x->ptr[i + 1] = nleaf;
    }
    return mid;
}
//--------------------------------------------------------------------------------------------------------------------
void insert(int a)
{
    int i, temp;
    x = root;
    if (x == NULL)
    {
        root= getnode();
       x = root;
    }
    else
    {
        if (x->leaf == true && x->n == 5)
        {
            temp = split(x, -1);
            x = root;
            for (i = 0; i < (x->n); i++)
           {
                if ((a > x->key[i]) && (a < x->key[i + 1]))
                {
                    i++;
                    break;
                }
                else if (a < x->key[0])
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            x = x->ptr[i];
        }
        else
        {
            while (x->leaf == false)
            {
                for (i = 0; i < (x->n); i++)
                {
                    if ((a > x->key[i]) && (a < x->key[i + 1]))
                    {
                        i++;
                        break;
                    }
                    else if (a < x->key[0])
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if ((x->ptr[i])->n == 5)
                {
                    temp = split(x, i);
                    x->key[x->n] = temp;
                    x->n++;
                    continue;
                }
                else
                {
                    x = x->ptr[i];
                }
            }
        }
    }
    x->key[x->n] = a;
    sort(x->key, x->n);
    x->n++;
}
//--------------------------------------------------------------------------------------------------------------------
void preorderDotDump(struct node *root,FILE *outFile)
{
    int i;
    if(root!=NULL)
    {
        fprintf(outFile,"node%d[label=\"<f0>%d",root->n,root->key[0]);
        i=1;
        while(root->key[i]!=0)
        {
            fprintf(outFile,"|<f%d>%d",i,root->key[i]);
            i++;
        }
        fprintf(outFile,"\"];\n");
        i=0;
        while(root->ptr[i]!=NULL&& i<6)
        {
            fprintf(outFile,"\"node%d\":f%d->\"node%d\":f%d;\n",root->n,0,root->ptr[i]->n,0);
            i++;
        }
        i=0;
        while(root->ptr[i]!=NULL&& i<6)
        {
            preorderDotDump(root->ptr[i],outFile);
            i++;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------
void dotDump(struct node *root,FILE *outFile)
{

    gName++;
    fprintf(outFile,"digraph tree{\n node [shape=record];\n",gName);
    preorderDotDump(root,outFile);
    fprintf(outFile,"}\n");
}
//--------------------------------------------------------------------------------------------------------------------

int main()
{
    FILE *pipe;
    int ch,i,key,n;
    printf("enter no of elements\n");
    scanf("%d",&n);
    outFile = fopen ("newbpt.dot", "w");
    fclose (outFile);
    for(i=0; i<n; i++)
    {
	scanf("%d",&key);       
//	key=rand()%100;
        insert(key);
        outFile = fopen ("newbpt.dot", "a");
        if (outFile != NULL)
        {

            dotDump (root,  outFile);
        }
        fclose (outFile);
    }
    while(1)
    {
        printf("\n1.Display dotty \n2.exit\n");
        scanf("%d",&ch);
        switch(ch)
        {

        case 1:
            pipe=popen("dot -Tps newbpt.dot -o newbpt.ps","w");
            pclose(pipe);
            pipe=popen("evince newbpt.ps","r");
            pclose(pipe);

            break;

        case 2:
            exit(0);
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------
