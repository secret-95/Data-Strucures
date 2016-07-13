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
void display(struct node *head)
{
	int i,count,value;
	struct node *temp=head;
	unsigned int arr[4];
	while(temp!=NULL)
	{
		for(i=0;i<4;i++)
		{
			count=0;
			arr[i]=temp->a[i];
			while(arr[i]>0)
			{
				if(arr[i]%2==1)
				{
					value=temp->start+32*i+count;
					printf("%d\t",value);
				}
				arr[i]=arr[i]/2;
				count++;
			}
		}	
		temp=temp->link;
	}
}
//------------------------------------------------------------------//------------------------------------------------------------------
void intersection(struct node *head1, struct node *head2)
{	
	int i=0;
	struct node *temp3=(struct node *) malloc(sizeof(struct node));
	struct node *temp1=head1, *temp2=head2;
	printf("Intersection\n");
	printf("Customer1:\t");
	display(temp1);
	printf("\n");
	printf("Customer2:\t");
	display(temp2);	
	printf("\n");
	printf("Common items:\t");
	while(temp1!=NULL)
	{
		while(temp2!=NULL)
		{
			if(temp1->start==temp2->start)
				{	
					for(i=0;i<4;i++)
					{	
						temp3->a[i]=temp1->a[i]&temp2->a[i];
					}
					display(temp3);	
					break;
				}
			temp2=temp2->link;
		}
		temp1=temp1->link;
	}
	printf("\n");
}
//------------------------------------------------------------------//------------------------------------------------------------------
/*void difference(struct node* head1, struct node* head2)// A-B
{	int i=0,flag=0,arr[4]={0,0,0,0};
	struct node *a=head1,*b=head2;
	printf("\n First customer has:\n");     
        displaylist(a);
        printf("\nSecond Customer has:\n");     
        displaylist(b);
	printf("\n Products in first that are not in b are:\n");
	for(a=head1;a;a=a->next)
	{       flag=0;
		for(b=head2;b;b=b->next)
		{       if(a->start==b->start)
			{	for(i=0;i<4;i++)
				{       arr[i]=a->a[i]^b->a[i];
					arr[i]=arr[i]&a->a[i];
				}
				display(arr,a->start);
				flag=1;
			}
		}
		if(!flag)
		{	display(a->a,a->start);
		}
	}
}*/
//------------------------------------------------------------------//------------------------------------------------------------------
void uni(struct node *head1, struct node *head2)
{	
	int i=0;
	struct node *temp3=(struct node *) malloc(sizeof(struct node));
	struct node *temp1=head1, *temp2=head2;
	printf("Union\n");
	printf("Customer1:\t");
	display(temp1);
	printf("\n");
	printf("Customer2:\t");
	display(temp2);	
	printf("\n");
	printf("Union of items:\t");
	while(temp1!=NULL)
	{
		while(temp2!=NULL)
		{
			if(temp1->start==temp2->start)
				{	
					for(i=0;i<4;i++)
					{	
						temp3->a[i]=temp1->a[i]|temp2->a[i];
					}
					display(temp3);	
					break;
				}
			temp2=temp2->link;
		}
		temp1=temp1->link;
	}
	printf("\n");
}
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
			/*	for(int j=0;j<=3;j++)
				printf("%u\t",temp->a[j]);
				printf("\n");*/
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
choicex:	printf("1.Customer 1\n2.Customer 2\n3.Intersection\n4.Union\n5.Exit\n");
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
 
						case 2: 
							goto choicex;


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

						case 2:
							goto choicex;

						default: printf("Enter proper choice\n");
							 
					}
				}
			case 3: intersection(head1,head2); 
				break;

			case 4: uni(head1,head2); 
				break;
		
			case 5: exit (0);
		}
	}
}

//------------------------------------------------------------------//------------------------------------------------------------------
