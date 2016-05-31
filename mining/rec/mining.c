#include<stdio.h>
#include<math.h>
static int p1=0,p2=0,p3=0,p4=0,p5=0;
struct node
{
	int x,y;
} c1[10],c2[10],c3[10],c4[10],c5[10], point[100];

int min(int i,float d1,float d2,float d3,float d4,float d5)
{
	int p,k;
	float mini;
	float a[5];
	a[0]=d1;
	a[1]=d2;
	a[2]=d3;
	a[3]=d4;
	a[4]=d5;
	mini=a[0];
	for(k=1;k<5;k++)
	{
		if(a[k]<mini)
		{
			mini=a[k];
			p=k;
		}
	}
	return p;

}

void distance(int i,struct node *c1,struct node *c2,struct node *c3,struct node *c4,struct node *c5)
{
	float d1,d2,d3,d4,d5;
	int j,l;
	d1=sqrt(((point[i].x-c1[0].x)*(point[i].x-c1[0].x))+((point[i].y-c1[0].y)*(point[i].y-c1[0].y)));
	d2=sqrt(((point[i].x-c2[0].x)*(point[i].x-c2[0].x))+((point[i].y-c2[0].y)*(point[i].y-c2[0].y)));
	d3=sqrt(((point[i].x-c3[0].x)*(point[i].x-c3[0].x))+((point[i].y-c3[0].y)*(point[i].y-c3[0].y)));
	d4=sqrt(((point[i].x-c4[0].x)*(point[i].x-c4[0].x))+((point[i].y-c4[0].y)*(point[i].y-c4[0].y)));
	d5=sqrt(((point[i].x-c5[0].x)*(point[i].x-c5[0].x))+((point[i].y-c5[0].y)*(point[i].y-c5[0].y)));
	j=min(i,d1,d2,d3,d4,d5);
	{
		if(j==0)
		c1[p1++]=point[j];
		else if(j==1)
		c2[p2++]=point[j];
		else if(j==2)
        	c3[p3++]=point[j];
		else if(j==3)
        	c4[p4++]=point[j];
		else 
        	c5[p5++]=point[j];
	}
	for(l=0;l<10;l++)
	{
		printf("%d %d\t",c1[l].x,c1[l].y);
		 printf("%d %d\t",c2[l].x,c2[l].y);
		 printf("%d %d\t",c3[l].x,c3[l].y);
		 printf("%d %d\t",c4[l].x,c4[l].y);
		printf("%d %d\t",c5[l].x,c5[l].y);
		printf("\n");
	}
	
}

int main()
{
	int n=50,i;
	printf("Enter the x and y coordinates of points\n");
	for(i=0;i<n;i++)
	{
		point[i].x=rand()%100+1;
		point[i].y=rand()%n+2;
	}
/*	for(i=0;i<n;i++)
	{
		printf("%d %d\n",point[i].x,point[i].y);
	}
*/
	c1[p1++]=point[0];
	c2[p2++]=point[1];
	c3[p3++]=point[2];
        c4[p4++]=point[3];
	c5[p5++]=point[4];
	
	for(i=5;i<n;i++)
	distance(i,c1,c2,c3,c4,c5);
//--------------------------
}

