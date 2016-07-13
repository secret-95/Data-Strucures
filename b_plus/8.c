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
void dump(struct node *r,FILE *out)
{
	if(r!=NULL)
	{
		int i;
		char st[1000],a[1000],b[1000];
		strcpy(st,"");
		strcpy(b," , ");
		for(i=0;i<r->count;i++)
		{
			snprintf(a,1000,"%d",r->key[i]);
			strcat(st,a);
			strcat(st,b);
		}
		fprintf(out,"st%d [label=\"%s\"",r->sl,st);
		fprintf(out,"];\n");
		if(r->l ==1 && r->ptr[r->count]!=NULL){fprintf(out,"st%d->st%d [style = dashed];\n",r->sl,r->ptr[r->count]->sl);}
		if(r->l!=1)
		{
			for(i=0;i<=r->count;i++)
			{
				if(r->ptr[i]!=NULL){dump(r->ptr[i],out);}
			}
		}
	}
}


void sdump(struct node *r,FILE *out)
{
	if(r!=NULL && r->l !=1)
	{
		int i;
		for(i=0;i<=r->count;i++)
		{
			fprintf(out,"st%d->st%d;\n",r->sl,r->ptr[i]->sl);
		}
		if(r->l!=1)
		{
			for(i=0;i<=r->count;i++)
			{
				if(r->ptr[i]!=NULL){sdump(r->ptr[i],out);
				}
			}
		}
	}

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
           out=fopen("b+.txt","w");
				fprintf(out,"digraph struct{\nnode [shape=record];\n");
				dump(root,out);
				sdump(root,out);
				fprintf(out,"{rank=same;");
				ranksame(root,out);
				fprintf(out,"}\n");
				fprintf(out,"}");
				fclose(out);

				pipe=popen("dot -Tps b+.txt -o b+.ps","w");
				pipe=popen("evince b+.ps","r");
				pclose(pipe);
				break;
            break;

        case 2:
            exit(0);
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------
