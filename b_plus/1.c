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

}*np = NULL, *x = NULL, *root=NULL;
int disp=0,flg=0;
static int gName=0;

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

    int j, mid;

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

        for (j = 3; j < 5; j++)

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

struct node* insert(struct node* head,int a)

{

    int i, temp;

    x = head;

    if (x == NULL)

    {

        head = create();

        x = head;

    }

    else

    {

        if (x->leaf == true && x->n == 5)

        {

            temp = split_child(x, -1);

            x = head;

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
return x;
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
		while(root->ptr[i]!=NULL && i<4)
		{
			fprintf(outFile,"\"node%d\":f%d->\"node%d\":f%d;\n",root->n,0,root->ptr[i]->n,0);
			i++;
		}
		i=0;
		while(root->ptr[i]!=NULL && i<4)
		{
			preorderDotDump(root->ptr[i],outFile);
			i++;
		}
	}
}
void dotDump(struct node* root,FILE *outFile)
{
	gName++;
	fprintf(outFile,"digraph tree{\nnode[shape=record];\n",gName);
	preorderDotDump(root,outFile);
	fprintf(outFile,"}\n");
}
FILE *outputFile;


int main()

{
   
    int i, n, t,choice;
    FILE *pipe;
    struct node* root;
   // struct node* L;
   struct node* new;
    struct node* head;
   head->ptr[0]=head; 		
    root=NULL;
    printf("enter the no of elements to be inserted\n");

    scanf("%d",&n);
    while(1)
    {
    printf("1.insert 2.display\n");
    scanf("%d",&choice);
    switch(choice)
    {
     case 1:
            
   		 for(i = 0; i < n; i++)
                 {
                 

                  printf("enter the element\n");

                  scanf("%d",&t);

                new=insert(head,t);
                 }
               root=head->ptr[0];
                 outputFile=fopen("bplus1.dot","a");
                  dotDump(root,outputFile);
                  fclose(outputFile);
                  pipe=popen("dot -Tps bplus1.dot -o bplus1.ps","w");
                  pclose(pipe);
                  
                  break;
    case 2:       if(flg==0)
		  {
                  root=head->ptr[0];
		  outputFile=fopen("bplus1.dot","a");
		  dotDump(root,outputFile);
                  fclose(outputFile);
                  pipe=popen("dot -Tps bplus1.dot -o bplus1.ps","w");
                  pclose(pipe);
                  } 			               
                 pipe=popen("evince bplus1.ps","r");
                 pclose(pipe);
                  break;
    //printf("traversal of constructed tree\n");

   //display(root);
break;
    default:exit(0);
  


}
}
}

