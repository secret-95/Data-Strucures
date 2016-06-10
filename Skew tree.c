# include <stdio.h>
# include <stdlib.h>
#include<string.h>
//---------------------------------------------------------------------------------
typedef struct BST
{
    int data;
    struct BST *left, *right;
} node;
//---------------------------------------------------------------------------------
int maxheight(node *node)
{
    if (node==NULL)
        return 0;
    else
    {

        int lDepth = maxheight(node->left);
        int rDepth = maxheight(node->right);


        if (lDepth > rDepth)
            return(lDepth+1);
        else return(rDepth+1);
    }
}
//---------------------------------------------------------------------------------
int minheight(node *node)
{
    if (node==NULL)
        return 0;
    else
    {

        int lDepth = minheight(node->left);
        int rDepth = minheight(node->right);


        if (lDepth < rDepth)
            return(lDepth+1);
        else return(rDepth+1);
    }
}
//---------------------------------------------------------------------------------
int validate(node *node )
{
    int max,min;
    max=maxheight(node);
    min=minheight(node);
    if(max > (3*min))
    {
        return 1;
    }
    else
        return -1;
}
//---------------------------------------------------------------------------------

node *get_node()
{
    node *temp;
    temp = (node *) malloc(sizeof(node));
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
//---------------------------------------------------------------------------------
void insert(node *root, node *new_node)
{
    if (new_node->data < root->data)
    {
        if (root->left == NULL)
            root->left = new_node;
        else
            insert(root->left, new_node);
    }

    if (new_node->data > root->data)
    {
        if (root->right == NULL)
            root->right = new_node;
        else
            insert(root->right, new_node);
    }
}
//---------------------------------------------------------------------------------
void checkstatus(int status)
{
    if(status == -1)
    {
        printf("Not skewed Tree\n");

    }
    else
    {
        printf("Skewed tree\n");
    }

}
//---------------------------------------------------------------------------------
int main()
{
    int choice,height,status;
    char ans = 'N';
    int key;
    node *new_node, *root, *tmp, *parent;
    node *get_node();
    root = NULL;
    new_node = get_node();
    for(int j=0; j<10000; j++)
    {
        new_node = get_node();
        new_node->data=rand()%10000;
        if (root == NULL)
            root = new_node;
        else
            insert(root, new_node);
       
    }
	 status=validate(root);
        checkstatus(status);
}
//---------------------------------------------------------------------------------

