#include<stdio.h>
void LR(int i,int j,int a[10][10])
{
	int k,l;
	for(k=i,l=i;l<=j;l++)
        printf("%d\n",a[k][l]);
}

void TD(int i,int j,int a[10][10])
{
	int k,l;
	 for(k=i+1,l=j;k<=j;k++)
         printf("%d\n",a[k][l]);
}

void RL(int i,int j,int a[10][10])
{
	  int k,l;
	  for(k=j,l=j-2i-1;l>=i;l--)
                printf("%d\n",a[k][l]);

}

void DT(int i,int j,int a[10][10])
{
	int k,l;
	for(k=j-2i-1,l=i;k>i;k--)
                printf("%d\n",a[k][l]);

}

void ite(int a[10][10],int n)
{
	int i,j;
	for(i=0,j=n-1;i<n&&j!=-1;i++,j--)
        {
		LR(i,j,a);
                TD(i,j,a);
		RL(i,j,a);
		DT(i,j,a);
	}
}

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
	ite(a,n);
}
