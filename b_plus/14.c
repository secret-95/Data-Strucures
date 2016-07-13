#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key[2],count;
    struct node *pptr,*ptr[3];
};

typedef struct node *node;
node root;
int order=3,tarr[3];
static int gName=0;
FILE *outFile;
void dotDump(node,FILE *);
void preorderDotDump(node,FILE *);
//Create new node in the tree
node getnode(node N)
{
    N=(node)malloc(sizeof(struct node));
    int i;
    N->pptr=NULL;
    for(i=0; i<2; i++)
        N->key[i]=0;
    for(i=0; i<3; i++)
        N->ptr[i]=NULL;
    N->count=0;
    return N;
}

//Find the appropriate leaf node to insert
node find(node root,int k)
{
    node t=root;
    int i,count;
    while(t->ptr[0] != NULL)
    {
        count=t->count;
        for(i=0; i<(t->count); i++)
        {
            if(t->key[i]>k)
            {
                t=t->ptr[i];
                break;
            }
        }
        if(i != count)
            continue;
        else
            t=t->ptr[i];
    }
    return t;
}

//Add value into a node
node addinto(node N,int v,node pr)
{
    int count;
    count=N->count;
    N->key[count]=v;
    count++;
    N->count++;
    if(N->ptr[0] != NULL)
        N->ptr[count]=pr;
    return N;
}

//Search a key node in the tree
void search(int k,node root)
{
    int i;
    while(root->ptr[0] != NULL)
        root=root->ptr[0];
    while(root != NULL)
    {
        i=0;
        while(i < root->count)
        {
            if(root->key[i] == k)
            {
                printf("Key found\n");
                return;
            }
            i++;
        }
        root=root->ptr[2];
    }
    printf("Key not found\n");
    return;
}

//Insert into the tree with reconstruction of tree
node insertentry(node L,int value,node p)
{
    node T;
    int i,j,count,m,X,temp;
    if(L->count != 2)
    {
        if(L->count==0)
        {
            L=addinto(L,value,p);
            return L;
        }
        if(L->key[0]<value)
            L=addinto(L,value,p);
        else
        {
            L->key[1]=L->key[0];
            L->key[0]=value;
            if(L->ptr[0] != NULL)
                L->ptr[2]=L->ptr[1];
            L->ptr[1]=p;
            if(p != NULL)
                p->pptr=L;
            L->count++;
        }
        return root;
    }
    m=1;
    for(i=0; i<2; i++)
        tarr[i]=L->key[i];
    tarr[2]=value;
    for(i=0; i<3; i++)
    {
        for(j=i; j<3; j++)
        {
            if(tarr[i]>tarr[j])
            {
                temp=tarr[i];
                tarr[i]=tarr[j];
                tarr[j]=temp;
            }
        }
    }
    X=tarr[1];
    T=getnode(T);
    if(L->ptr[0]==NULL)
    {
        for(i=m; i<2; i++)
        {
            T=addinto(T,X,p);
            L->key[i]=0;
            L->ptr[i]=NULL;
            (L->count)--;
        }
        T=addinto(T,tarr[2],p);
        L->key[0]=tarr[0];
    }
    else
    {
        for(i=m; i<2; i++)
        {
            L->key[i]=0;
            (L->count)--;
        }
        L->key[0]=tarr[0];
        T=addinto(T,tarr[2],p);
        T->ptr[0]=L->ptr[2];
        (L->ptr[2])->pptr=T;
        L->ptr[2]=NULL;
        p->pptr=T;
    }
    if(L->pptr != NULL)
        root=insertentry(L->pptr,X,T);
    else
    {
        root=getnode(root);
        root->key[0]=X;
        root->count=1;
        root->ptr[0]=L;
        root->ptr[1]=T;
        L->pptr=root;
        T->pptr=root;
    }
    if(L->ptr[0] == NULL)
    {
        T->ptr[2]=L->ptr[2];
        L->ptr[2]=T;
    }
    return root;
}

//Check if new value already exists, else insert into the tree
node insert(int value,node p,node root)
{
    node L;
    L=find(root,value);
    root=insertentry(L,value,p);
    return root;
}

//Display all leaf elements in order, starting from the left most leaf
void traverse(node root)
{
    int i;
    while(root != NULL)
    {
        i=0;
        while(i < root->count)
        {
            printf("%d\t",root->key[i]);
            i++;
        }
        root=root->ptr[2];
    }
}
void preorderDotDump(node root,FILE *outFile)
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
void dotDump(node root,FILE *outFile)
{
    gName++;
    fprintf(outFile,"digraph tree{\nnode[shape=record];\n",gName);
    preorderDotDump(root,outFile);
    fprintf(outFile,"}\n");
}

//Traverse to the left most leaf
void display(node root)
{
    while(root->ptr[0] != NULL)
        root=root->ptr[0];
    traverse(root);
    return;
}

void main()
{
    FILE *pipe;
    int ch,val,choice,op,key;
    root=getnode(root);
    while(1)
{
   printf("Enter your choice\n 1.Insert\n2.Display\n");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            //Insertion and display
            printf("Enter the value you want to insert\n");
            scanf("%d",&val);
            root=insert(val,NULL,root);
            outFile=fopen("bplus.dot","w");
            fclose(outFile);
            outFile=fopen("bplus.dot","a");
            if(outFile!=NULL)
                dotDump(root,outFile);
            fclose(outFile);
           
            //Display tree elements upon each element insertion
            //display(root);
            printf("\n");

            break;


        case 2:
           pipe=popen("dot -Tps bplus.dot -o bplus.ps","w");
            pclose(pipe);
            pipe=popen("evince bplus.ps","r");
            pclose(pipe);;
            break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
}
