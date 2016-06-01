#include <stdio.h>
#include <stdlib.h>

static int gName=0;
FILE *outputFile;


typedef struct nodes
{
    int k[3];
    struct nodes *child[4];
    int n;
    int leaf;
} Node;

Node* newnode()
{
    Node* x = malloc(sizeof(Node));
    x->n = 0;
    x->leaf = 1;
    return x;
}


void split(Node* x, int i)
{
    Node* a = x->child[i];
    Node* b = newnode();

    for (int j = x->n; j > i; j--)
    {
        x->child[j+1] = x->child[j];
        x->k[j] = x->k[j-1];
    }
    x->k[i] = a->k[1];
    x->child[i+1] = b;
    x->n++;
    if (a->leaf)
    {
        b->leaf = 1;

        for (int j = 0; j < 1; j++)
        {
            b->k[j] = a->k[j + 2];
            b->n++;
        }
        a->n = 1;
    } else
    {
        b->leaf = 0;

        for (int j = 0; j <1; j++)
        {
            b->k[j] = a->k[j + 2];
            b->child[j] = a->child[j + 2];
            b->n++;
        }
        b->child[2] = a->child[3];
        a->n = 1;

    }
}

Node* insert1(Node* x, int value)
{
    int i = 0;
    while ( i < x->n && value > x->k[i])
        i++;
    if (x->leaf)
    {
        int j;
        for (j = x->n; j > i; j--)
        {
            x->k[j] = x->k[j-1];
        }
        x->k[j] = value;
        x->n++;
        return x;
    } else
    {
        if (x->child[i]->n == 3)
        {

            split(x, i);
            if (value > x->k[i])
            {
                i++;
            }
        }
        return insert1(x->child[i], value);
    }
}

Node* insert(Node** root, int value)
{
    Node* r = *root;
    if (r->n == 3)
    {
        Node* a = newnode();
        a->child[0] = r;
        a->leaf = 0;
        *root= a;
        split(a,0);
        return insert1(a, value);
    } else {
        return insert1(r,value);
    }
}


void display(Node *x,FILE *outfile)
{
     	fprintf (outputFile, "node%d[label=\" %d ",x->k[0],x->k[0]);
	int i=1;
			while(x->k[i]!='\0')
			{			
				fprintf (outputFile, " %d ",x->k[i]);
				i++;			
			}
			fprintf (outputFile,"\"];\n");	
			i=0;
			while(x->child[i]!=NULL)
				{			
									
					fprintf (outputFile, "\"node%d\":f%d -> \"node%d\":f%d;\n",x->k[i],0, x->child[i]->k[i],0);
					i++;			
				}
			i=0;

        		while(x->child[i]!=NULL)
			{			
				display (x->child[i], outputFile);
				i++;			
			}
			
			
				
				
        		
        	
			
    /*    int i;
    //    printf("8====>%d",x->n);
        for (i = 0; i < x->n - 1; i++)
        {
            printf("%d ",x->k[i]);
        }
        printf("%d\n",x->k[i]);*/
}

void dotDump(Node *root, FILE *outFile)
{
    gName++;
    fprintf (outFile, "digraph 234 {\n",gName);
    display (root, outFile);
    fprintf (outFile, "}\n");
}

int main()
{
    Node *n=NULL;
    int ch;
    FILE *pipe;
    int value;
    Node* r = newnode();
    Node** root= &r;
    outputFile = fopen ("234.dot", "w");
    fclose (outputFile);

    while(1)
    {
        printf("1.Insert\n2.Display Dotty\n3.Exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            printf("Enter the value of the node\n");
            scanf("%d", &value);
            /*8=====>*/   n=insert(root,value);
            outputFile = fopen ("234.dot", "a");
            if (outputFile != NULL)
            {
                dotDump (n,  outputFile);
            }
            fclose (outputFile);
            printf("Root--\t");
            display(*root,NULL);
            pipe=popen("dot -Tps 234.dot -o 234.ps","w");
					pclose(pipe);	
            break;
        case 2:
            pipe=popen("dot -Tps 234.dot -o 234.ps","w");
            pclose(pipe);
            pipe=popen("evince 234.ps","r");
            pclose(pipe);
            break;

        case 3:
            exit(0);
        default:
            printf("Enter proper choice\n");
            break;
        }

    }

    return 0;
}



