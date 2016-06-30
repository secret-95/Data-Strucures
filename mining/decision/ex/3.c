#include<stdio.h>
//--------------------------------------------------------------
struct node
{
	int a3,a1,a2;
	int class;

}instance[9];
//--------------------------------------------------------------
void gini (struct node *instance)
{
	int c1=0,c2=0;
	float g1=0,g2=0,g3=0,s1=0,s2=0;
	
	for(int i=0;i<9;i++)
	{
		
		if(instance[0].a1==instance[i].a1)
			c1++;
		else
			c2++;

	}
	printf("%d\n",c1);
	printf("%d\n",c2);
	s1=(float)c1/(float)(c1+c2);
	s2=(float)c2/(float)(c1+c2);
	s1*=s1;
	s2*=s2;
	g1=1-s1-s2;
	printf("Gini for a1 = %f\n",g1);
	c1=0,c2=0;
	g1=0,g2=0,g3=0,s1=0,s2=0;
	for(int i=0;i<9;i++)
	{
		
		if(instance[0].a2==instance[i].a2)
			c1++;
		else
			c2++;

	}
	printf("%d\n",c1);
	printf("%d\n",c2);
	s1=(float)c1/(float)(c1+c2);
	s2=(float)c2/(float)(c1+c2);
	s1*=s1;
	s2*=s2;
	g2=1-s1-s2;
	printf("Gini for a2 = %f\n",g2);

}

//--------------------------------------------------------------
int main()
{
	
	for(int i=0;i<9;i++)
		scanf("%d",&instance[i].a1);


	for(int i=0;i<9;i++)
		scanf("%d",&instance[i].a2);

	for(int i=0;i<9;i++)
		scanf("%d",&instance[i].a3);

	for(int i=0;i<9;i++)
		scanf("%d",&instance[i].class);

	gini(instance);  //To calculate gini values for all attributes


	printf("Instance\ta1\ta2\ta3\tclass\n\n");
	for (int  i= 0; i < 9; ++i)
	{
		printf("%d\t\t%d\t%d\t%d\t%d\n",i+1,instance[i].a1,instance[i].a2,instance[i].a3,instance[i].class);
	}
	return 0;

}