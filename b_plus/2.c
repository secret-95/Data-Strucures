#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define true 1
#define false 0

struct node

{

    int key[5];

    struct node *ptr[6];

    int leaf;

    int n,disp;

}*root=NULL,*np = NULL, *x = NULL;
int flg=0,val;
static int gName=0,disp=0;
FILE *outFile;
struct node* create()

{
    int i;

   struct node* np;
np=(struct node*)malloc(sizeof(struct node));
   
   for (i = 0; i < 5; i++)
    {
    np->key[i];
    }
    np->leaf = true;

    np->n = 0;

    for (i = 0; i < 6; i++)

    {

        np->ptr[i] = NULL;

    }

    return np;

}

/*void display(struct node *p)

{

    
    int i;

    for (i = 0; i < p->n; i++)

    {

        if (p->leaf == false)

        {

            display(p->ptr[i]);

        }
       printf(" ");
       printf("%d",p->key[i]);

    } 

    if (p->leaf == false)

    {

        display(p->ptr[i]);

    }


}*/

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

int split_child(struct node *x, int i)

{

    int  mid;

    struct node *np1, *np3, *y;

    np3 = create();

    np3->leaf = true;

    if (i == -1)

    {

        mid = x->key[2];

        x->key[2] = 0;

        x->n--;

        np1 = create();

        np1->leaf = false;

        x->leaf = true;

        for (int j = 3; j < 5; j++)

        {

            np3->key[j - 3] = x->key[j];

            np3->ptr[j - 3] = x->ptr[j];

            np3->n++;

            x->key[j] = 0;

            x->n--;

        }

        for(j = 0; j < 6; j++)

        {

            x->ptr[j] = NULL;

        }

        np1->key[0] = mid;

        np1->ptr[np1->n] = x;

        np1->ptr[np1->n + 1] = np3;

        np1->n++;

        root = np1;

    }

    else

    {

        y = x->ptr[i];

        mid = y->key[2];

        y->key[2] = 0;

        y->n--;

        for (j = 3; j < 5; j++)

        {

            np3->key[j - 3] = y->key[j];

            np3->n++;

            y->key[j] = 0;

            y->n--;

        }

        x->ptr[i + 1] = y;

        x->ptr[i + 1] = np3; 

    }

    return mid;

}

void insert(int a)

{

    int i, temp;

    x = root;

    if (x == NULL)

    {

        root= create();

        x = root;

    }

    else

    {

        if (x->leaf == true && x->n == 5)

        {

            temp = split_child(x, -1);

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

                    temp = split_child(x, i);

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

void dotDump(struct node *root,FILE *outFile)
{

gName++;
fprintf(outFile,"digraph tree{\n node [shape=record];\n",gName);
preorderDotDump(root,outFile);
fprintf(outFile,"}\n");
}


int main(int argc,char** argv)
{
                FILE *pipe;
                int ch,i,key,n;
               /* if (argc != 2)
                {
                        printf(" need one argument  \n");
                        exit(0);
                }*/
                printf("enter no of elements\n");
                scanf("%d",&n);
                outFile = fopen ("newbpt.dot", "w");
                fclose (outFile);
                //val = atoi(argv[1]);
                for(i=0;i<n;i++)
                {
                      //  key=random()%1000;
                        scanf("%d",&key);
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
                        printf("1.Display dotty \n2.exit");
                        printf("Enter your choice\n");
                        scanf("%d",&ch);
                        switch(ch)
                        {



                                /*case 1:printf("Enter element to be deleted\n");
                                        scanf("%d",&item);
                                        root=delete(item,root);
                                        printf("\nElement deleted\n");
                                        outputFile = fopen ("bst.dot", "a");
                                        dotDump (root,  outputFile);
                                        fclose (outputFile);
                                        break;*/

                                case 1:
                                         pipe=popen("dot -Tps newbpt.dot -o newbpt.ps","w");
                                        pclose(pipe);
                                        pipe=popen("evince newbpt.ps","r");
                                        pclose(pipe);

                                        break;

                                case 2:printf("wrong choice\n");
                                        exit(0);

                        }
              
 

  
}


}
