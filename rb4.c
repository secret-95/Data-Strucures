//--------------------------------
#include<stdio.h>
#include<stdlib.h>
static int gName=0;
struct node
{
    int key;
    char color;
    struct node *left, *right,*parent;
};
struct node* root = NULL;
void leftRotate(struct node *x)
{
    struct node *y;

    y = x->right;
    x->right = y->left;

    if( y->left != NULL)

    {
        y->left->parent = x;

    }

    y->parent = x->parent;

    if( x->parent == NULL)

    {
        root = y;

    }

    else if( (x->parent->left!=NULL) && (x->key == x->parent->left->key))

    {
        x->parent->left = y;

    }

    else x->parent->right = y;

    y->left = x;
    x->parent = y;
    return;

}

void rightRotate(struct node *y)

{
    struct node *x;

    x = y->left;
    y->left = x->right;

    if ( x->right != NULL)

    {
        x->right->parent = y;

    }

    x->parent = y->parent;

    if( y->parent == NULL)

    {
        root = x;

    }

    else if((y->parent->left!=NULL)&& (y->key == y->parent->left->key))

    {
        y->parent->left = x;

    }

    else

        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return;

}

void rbinsert(struct node *z)

{
    struct node *y=NULL;

    while ((z->parent != NULL) && (z->parent->color == 'r'))

    {

        if ( (z->parent->parent->left != NULL) && (z->parent->key == z->parent->parent->left->key))

        {
            if(z->parent->parent->right!=NULL)

                y = z->parent->parent->right;

            if ((y!=NULL) && (y->color == 'r'))

            {
                z->parent->color = 'b';

                y->color = 'b';

                z->parent->parent->color = 'r';

                if(z->parent->parent!=NULL)

                    z = z->parent->parent;

            }

            else

            {

                if ((z->parent->right != NULL) && (z->key == z->parent->right->key))

                {
                    z = z->parent;

                    leftRotate(z);

                }

                z->parent->color = 'b';

                z->parent->parent->color = 'r';

                rightRotate(z->parent->parent);

            }

        }

        else

        {

            if(z->parent->parent->left!=NULL)

                y = z->parent->parent->left;

            if ((y!=NULL) && (y->color == 'r'))

            {
                z->parent->color = 'b';

                y->color = 'b';

                z->parent->parent->color = 'r';

                if(z->parent->parent!=NULL)

                    z = z->parent->parent;

            }

            else

            {

                if ((z->parent->left != NULL) && (z->key == z->parent->left->key))

                {
                    z = z->parent;

                    rightRotate(z);

                }

                z->parent->color = 'b';

                z->parent->parent->color = 'r';

                leftRotate(z->parent->parent);

            }

        }

    }
    root->color = 'b';

}

void insert(int val)

{
    struct node *x, *y;

    struct node *z = (struct node*)malloc(sizeof(struct node));

    z->key = val;

    z->left = NULL;

    z->right = NULL;

    z->color = 'r';

    x=root;


    if ( root == NULL )

    {
        root = z;

        root->color = 'b';

        return;

    }

    while ( x != NULL)

    {
        y = x;

        if ( z->key < x->key)

        {   x = x->left;

        }

        else x = x->right;

    }

    z->parent = y;

    if ( y == NULL)

    {
        root = z;

    }

    else if( z->key < y->key )

    {
        y->left = z;

    }

    else y->right = z;

    rbinsert(z);

    return;

}


void preorderDotDump (struct node *root, FILE* outputFile)

{

    if (root != NULL)

    {

        fprintf (outputFile, "%d [label=%d,color=black];\n",root->key, root->key);

        if (root->left != NULL)

            fprintf (outputFile, "%d -> %d ;\n", root->key, (root->left)->key);



        if (root->right != NULL)

            fprintf (outputFile, "%d -> %d;\n", root->key, root->right->key);

        //	if (root->pptr != NULL)

        //   		fprintf (outputFile, "%d -> %d [style = dashed];\n", root->key, (root->pptr)->key);

        preorderDotDump (root->right, outputFile);

        preorderDotDump (root->left, outputFile);

    }

}



void dotDump(struct node *root, FILE *outFile)

{

    gName++;

    fprintf (outFile, "digraph BST {\n",gName);



    preorderDotDump (root, outFile);

    fprintf (outFile, "}\n");

}

FILE *outputFile;





int main()

{

    int choice,val,key,var,i;
    FILE *pipe;
    outputFile = fopen ("rbt.dot", "w");

    fclose (outputFile);

    for(i=0; i<20; i++)

    {

        val=random()%1000;

        printf("%d\t",val);

        insert(val);



        outputFile = fopen ("rbt.dot", "a");

        if (outputFile != NULL)

        {



            dotDump (root,  outputFile);

        }

        fclose (outputFile);

    }



    while(1)

    {   printf("\n1:Insert  2:Display inorder  3:Exit\n");

        scanf("%d",&choice);

        switch(choice)

        {
        case 1:
            printf("Enter the integer you want to add : ");

            scanf("%d",&val);

            insert(val);
            break;

        case 2:
            pipe=popen("dot -Tps rbt.dot -o rbt.ps","w");

            pclose(pipe);

            pipe=popen("evince rbt.ps","r");

            pclose(pipe);



            break;

        case 3:
            exit(0);

        default:
            printf("\nInvalid Choice\n");

        }


    }
    return 0;

}

