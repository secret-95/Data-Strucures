#include<stdio.h>
int main()
{
        int i,j,n,a[10][10],k,l;
        //--------------------------
//      printf("Enter the order of the matrix\n");
        scanf("%d",&n);
//      printf("Enter the matrix\n");
        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        scanf("%d",&a[i][j]);
        //-------------------------
        for(i=0,j=n-1;i<n&&j!=-1;i++,j--)
        {
                for(k=i,l=i;l<=j;l++)
                printf("%d\n",a[k][l]);
//              printf("\n");

                for(k=i+1,l=j;k<=j;k++)
                printf("%d\n",a[k][l]);
 //              printf("\n");

                for(k=j,l=j-2i-1;l>=i;l--)
                printf("%d\n",a[k][l]);
//                printf("\n");

                for(k=j-2i-1,l=i;k>i;k--)
                printf("%d\n",a[k][l]);
  //              printf("\n");

        }
        //-------------------------
}
