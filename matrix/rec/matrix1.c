#include<stdio.h>
void LR(int i,int j,int k,int l,int a[10][10])
{
	
	if(l<=j)
	{
		printf("%d\n",a[k][l]);
        	l++;
		LR(i,j,k,l,a);
	}

}

void TD(int i,int j,int k,int l,int a[10][10])
{
	
	if(k<=j)
	{
		printf("%d\n",a[k][l]);
		k++;
		TD(i,j,k,l,a);
	}
}

void RL(int i,int j,int k,int l,int a[10][10])
{
	if(l>=i)
	{
                printf("%d\n",a[k][l]);
		l--;
		RL(i,j,k,l,a);
	}

}

void DT(int i,int j,int k,int l,int a[10][10])
{
	
	if(k>i)
	{
                printf("%d\n",a[k][l]);
		k--;
		DT(i,j,k,l,a);
	}

}

void rec(int a[10][10],int n)
{
	int i,j,k,l;
	for(i=0,j=n-1;i<n&&j!=-1;i++,j--)
        {
		k=i;l=i;
		LR(i,j,k,l,a);
                k=i+1;l=j;
                TD(i,j,k,l,a);
		k=j;l=j-2i-1;
		RL(i,j,k,l,a);
		k=j-2i-1;l=i;
		DT(i,j,k,l,a);

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
	rec(a,n);
}
