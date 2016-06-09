#include<stdio.h>
#include<stdlib.h>

struct node
{
	int start;
	unsigned int a[4];
	struct node* link;
}*head1=NULL,*head2=NULL;

void display(unsigned int a[],int start);

struct node* insert(struct node* head,int prodno)
{
	int nodeno,bit,part,head1;

	nodeno=prodno/128;
	head1=prodno-(nodeno*128);
	bit=head1%32;
	part=head1/32;

	struct node* new=(struct node*)malloc(sizeof(struct node));

	if(head==NULL)
	{

		new->start=nodeno;
		new->link=NULL;
		new->a[part]=new->a[part] | (1<<(bit));	//bit set
		head=new;
		return head;
	}

	else
	{
		struct node* temp=head;
		z:if(temp->start==nodeno)
  		{
	  		temp->a[part]=temp->a[part] | (1<<bit);
	  		return head;
  		}
  		while(temp->link!=NULL)
  		{
	  		temp=temp->link;
	 		 goto z;
  	}

  	new->start=nodeno;
  	new->link=NULL;
  	new->a[part]=new->a[part] | (1<<bit);
  	temp->link=new;
  	return(head);
	}
}

void disp(struct node* z)
{       
        struct node* temp=z;
        while(temp!=NULL)
	{
		display(temp->a,temp->start);
		temp=temp->link;
	}
}

void display(unsigned int a[],int start)
{       
	unsigned int arr[4];
	int k=0,i=0,p;
	{       
		for(i=0;i<4;i++)
		{      
			arr[i]=a[i];    //copy to another array so that value doesn't alter
			k=0;
			while(arr[i]>0)
			{       p=arr[i]%2;
				if(p==1)
					printf("%u\t", (start*128+(i*32)+(k)));
				k++;
				arr[i]=arr[i]/2;
			}
		}
	}
	printf("\n");
}

void unions(struct node *head1, struct node *head2)
{	
	int i,start,j,k;
	unsigned int arr[4];
	struct node *temp1=head1;
	struct node *temp2=head2;
      while(temp1!=NULL) 
	{
		while(temp2!=NULL) 
		{	
			if(temp1->start==temp2->start)
			{	
				for(i=0; i<=3; i++)
				{
					arr[i]=temp1->a[i]|temp2->a[i];
				}
				start=temp1->start;
				display(arr,start);
				break;
			}
		        temp2=temp2->link;
		}
		temp1=temp1->link;
	}
    	temp1=head1;
	temp2=head2;
       while(temp1!=NULL)
        {
		j=1;
                while(temp2!=NULL)
                {
                        if(temp1->start == temp2->start)
                        {
                            j=0;
			    break;
                        }
			temp2=temp2->link;
                }
		if(j)
		display(temp1->a,temp1->start);
		temp1=temp1->link;
        }
	temp1=head1;
	temp2=head2;

	while(temp2!=NULL)
	{      
		k=1;
		while(temp1!=NULL)
		{       
			if(temp1->start==temp2->start)
			{    
				k=0;
				break;
			}
			temp1=temp1->link;
		}
		if(k)
		display(temp2->a,temp2->start);
		temp2=temp2->link;
	}

}

void intersection(struct node* head1, struct node* head2)
{
        int i,start;
        unsigned int arr[4];
        struct node* temp1=head1;
	struct node* temp2=head2;
        while(temp1!=NULL)
        {
                while(temp2!=NULL)
                {
                        if(temp1->start==temp2->start)
                        {
                                for(i=0; i<=3; i++)
                                {
                                        arr[i]=temp1->a[i] & temp2->a[i];
                                }
                                start=temp1->start;
                                display(arr,start);
                                break;
                        }
			temp2=temp2->link;
                }
		temp1=temp1->link;
        }

}

void difference1(struct node *head1, struct node *head2)
{
  	int i,start,j,k;
        unsigned int arr[4];
        struct node* temp1=head1;
	struct node* temp2=head2;
 	while(temp1!=NULL)
        {
                j=1;
                while(temp2!=NULL)
                {
                        if(temp1->start == temp2->start)
                        {
                            j=0;
                        break;
                        }
			temp2=temp2->link;
                }
                if(j)
                display(temp1->a,temp1->start);
		temp1=temp1->link;
        }

}

void difference2(struct node *head1, struct node *head2)
{
 	 int i,start,j,k;
         unsigned int arr[4];
         struct node* temp1=head1;
	 struct node* temp2=head2;
         while(temp2!=NULL)
         {
      	          k=1;
      	          while(temp1!=NULL)
      	          {
      	                  if(temp1->start==temp2->start)
      	                  {
      	                          k=0;
      	                          break;
      	                  }
			  temp1=temp1->link;
      	          }
      	          if(k)
      	          display(temp2->a,temp2->start);
		  temp2=temp2->link;
        }
}


int main()
{
	int prod,ch;

	while(1)
	{
		printf("\n1.Customer 1\n2.Customer 2\n3.Display\n4.Union\n5.Intersection\n6.Difference(1-2)\n7.Difference(2-1)\n8.Exit\n");
		scanf("%d",&ch);

		switch(ch)
		{

			case 1: printf("\nEnter Product number\n");
				scanf("%d",&prod);
				head1=insert(head1,prod);
				break;

			case 2: printf("\nEnter Product number\n");
				scanf("%d",&prod);
				head2=insert(head2,prod);
				break;

			case 3: printf("\nCustomer 1 items:\t");
				disp(head1);
				printf("\nCustomer 2 items:\t");
				disp(head2);
				break;

			case 4: printf("\nUnion of items of Customer 1 and 2:\t");
				unions(head1,head2);
				break;

			case 5: printf("\nIntersection of items of Customer 1 and 2:\t");
				intersection(head1,head2);
                                break;

			case 6: printf("Difference 1 - 2:\t");
				difference1(head1,head2);
				break;

			case 7:	printf("Difference 2 - 1:\t");
				difference2(head1,head2);
                                break;

			case 8:exit(0);

			default:printf("\nEnter correct choice....!!\n");
				
		}
	}
	return 0;
}
