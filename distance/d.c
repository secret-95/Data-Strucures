#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NUM_COMMANDS 3
struct node
{
	int x;
	int y;
        int col;
} point[100];

float distance(int x1,int y1,int x2,int y2)
{
	float d;
	d=sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
	return d;
}	

int main()
{
	int i,n,j,v1,v2,x1,x2,y1,y2,p,q,r,s;		
	float min=5000.0,k;
	 char * commandsForGnuplot[] = {"set title \"Nearest destination\"","set palette model RGB defined (0 \"red\",1 \"blue\",2 \"green\")", "plot 'data.temp' using 1:2:3 notitle with points pt 2 palette"};
	printf("Enter the number of points\n");
	scanf("%d",&n);
	printf("Enter the x coordinate and y coordinate respectively\n");
	for(i=0;i<n;i++)	
	{
		point[i].x=rand()%100+1;
		point[i].y=rand()%50+2;
		point[i].col=1;                
	}
	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
		if(i==j)
		{}
		else
		{
			x1=point[i].x;
			y1=point[i].y;
			x2=point[j].x;
			y2=point[j].y;
			printf("(%d,%d)  (%d,%d)\t",x1,y1,x2,y2);
			k=distance(x1,y1,x2,y2);
			printf("Distance=%f\n",k);
			if(k<min)
			{	
				min=k;
				p=x1;
				q=y1;
				r=x2;
				s=y2;
				v1=i;v2=j;

			}
		}
	}
	}
			point[v1].col=point[v2].col=3;
			printf("Minimum distance is\n");
			printf("(%d,%d)<--->(%d,%d)=\t",p,q,r,s);
			printf("%f\n",min);

    FILE * temp1 = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    
    for (i=0;i<n;i++)
    {
    fprintf(temp1, "%d %d %d\n", point[i].x, point[i].y, point[i].col); //Write the data to a temporary file
    }

    for (i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
}	

	
	

