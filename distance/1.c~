#include <stdlib.h>

#include <stdio.h>

#include<math.h>

#define NUM_POINTS 12

#define NUM_COMMANDS 3



int main()

{	int  x1, x2, y1, y2,xleast,yleast,c,colort=11;

        float  r,least;

	least=100;

    char * commandsForGnuplot[] = {"set title \"Nearest destination\"","set palette model RGB defined (0 \"red\",1 \"blue\",2 \"green\")", "plot 'data.temp' using 1:2:3 notitle with points pt 2 palette"};

    double xvals[NUM_POINTS] ;

    double yvals[NUM_POINTS] ;

     int col[NUM_POINTS];

	printf( "Enter Present Position (x1,y1): \n" );

        scanf( "%d" ,&x1);

        scanf( "%d" ,&y1);

	xvals[0]=x1;

	yvals[0]=y1;

	col[0]=1;

      for (c = 1; c <= 10; c++) 

     {

    		x2 = rand()%100 ;

		y2 = rand()%100 ;

		xvals[c]=x2;

		yvals[c]=y2;

		col[c]=2;

    		printf("(%d,%d)\n", x2 ,y2);

		r = sqrt(pow((y2-y1),2) + pow((x2-x1),2));

                printf( "Distance= %f \n\n" ,r);

		if(r < least)

		{

		col[colort]=2;

		col[c]=1;

		least=r;

		xleast=x2;

		yleast=y2;

		printf("%d,%d\n", xleast ,yleast);

		colort=c;

		}

		

     }

        printf("The nearest coordinate is: (%d,%d) at a distance of %f\n\n",xleast,yleast,least);

    FILE * temp = fopen("data.temp", "w");

    /*Opens an interface that one can use to send commands as if they were typing into the

     *     gnuplot command line.  "The -persistent" keeps the plot open even after your

     *     C program terminates.

     */

    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    int i;

    for (i=0; i < NUM_POINTS; i++)

    {

    fprintf(temp, "%lf %lf %d\n", xvals[i], yvals[i],col[i]); //Write the data to a temporary file

    }



    for (i=0; i < NUM_COMMANDS; i++)

    {

    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.

    }

    return 0;

}
