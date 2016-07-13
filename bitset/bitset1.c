#include<stdio.h>
#include<stdlib.h>
//------------------------------------------------------------------//------------------------------------------------------------------
struct node
{
    int start;
   unsigned int a[4];
    struct node *link;
}*head1=NULL, *head2=NULL, *temp=NULL;
//------------------------------------------------------------------//------------------------------------------------------------------
struct node * getnode()
{
	struct node *temp=(struct node *) malloc(sizeof(struct node));
	temp->start=0;
	for(int j=0;j<=3;j++)
	temp->a[j]=0;
	temp->link=NULL;
	return temp;
}
//------------------------------------------------------------------//------------------------------------------------------------------
int bitset(int number,int position)
{
//	int position;
//	position=number%128;
	number = number |(1<<position);
	printf("%d\n",number);
	return number;
}
//------------------------------------------------------------------//------------------------------------------------------------------
struct node * insert(struct node *head, int productno)
{
	struct node *new=getnode();
	unsigned int q,kstartk,bitno,nodeno,nodebitno,x;
	q=productno/128;
	kstartk=128*q;
	bitno=productno-kstartk;
	nodebitno=bitno%32;
	nodeno=bitno/32;
	if(head==NULL)
	{
		new->start=kstartk;
		new->a[nodeno]=bitset(new->a[nodeno],nodebitno);
		new->link=NULL;		
		head=new;
		
	} 
	else
	{
		temp=head;
		while(temp->link != NULL)
		{
			if(temp->start == kstartk)
			{
				x=bitset(temp->a[nodeno],nodebitno);
				temp->a[nodeno]=temp->a[nodeno]+x;
			}
			else
			{
				temp=temp->link;
			}
		}
		if(temp->link == NULL)		
		{
			if(temp->start == kstartk)
			{
				x=bitset(temp->a[nodeno],nodebitno);
				temp->a[nodeno]=x;
				for(int j=0;j<=3;j++)
				printf("%u\t",temp->a[j]);
				printf("\n");
			}
			else
			{
				new->start=kstartk;
				temp->link=new;
				x=bitset(new->a[nodeno],nodebitno);
				new->a[nodeno]=new->a[nodeno]+x;
				new->link=NULL;	
			}
			
		}
		
	}
/*	for(int j=0;j<=3;j++)
	printf("%d\t",new->a[j]);*/
	return head;
	
	
}
//------------------------------------------------------------------//------------------------------------------------------------------
int main()
{
	int custchoice,choice,productno;
	while(1)
	{
choicex:	printf("1.Customer 1\n2.Customer 2\n3.Exit\n");
		scanf("%d",&custchoice);
		switch(custchoice)
		{
			case 1:	while(1)
				{
					printf("\n1.Enter product number\n2.Back\n");
					scanf("%d",&choice);	
					switch(choice)
					{
						case 1: scanf("%d",&productno);
							head1=insert(head1,productno);
							break;
 
						case 2: goto choicex;

						default: printf("Enter proper choice\n");
							 
					}
				} 
			case 2: while(1)
				{
					printf("1.Enter product number\n2.Back\n");
					scanf("%d",&choice);	
					switch(choice)
					{
						case 1: scanf("%d",&productno);
							head2=insert(head2,productno);
							break;

						case 2: goto choicex;

						default: printf("Enter proper choice\n");
							 
					}
				} 
			case 3: exit (0);
		}
	}
}

//------------------------------------------------------------------//------------------------------------------------------------------
