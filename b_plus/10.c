#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	int key[100],count;
	struct node *ptr[100],*pptr;
	int l,sl;
};
FILE *out;
int degree = 3;
int ss =0;
struct node *root;
struct node* insert(int v,struct node *p);
struct node* getnode();
int findki(struct node *c,int value);
struct node* find(int v);
struct node* insert_entry(struct node *l,int v,struct node *p);
struct node* addinto(struct node *n,int v,struct node *p);

struct node* getnode()
{
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->pptr=NULL;
	int i=0;
	for(i =0 ;i< degree;i++)
	{
		temp->ptr[i] =NULL;
	}
	temp->count=0;
	temp->l =1;
	temp->sl=ss;
	ss = ss+1;
	return temp;
}


int findki(struct node *c,int value)
{
	int i;
	for(i=0;i<c->count;i++)
	{
		if(c->key[i]>value)
		{
			return i;
		}
	}
	return -1;
}


struct node* find(int v)
{
	struct node *c;
	c=root;
	while(c->l!=1)
	{
		int ki;
		ki=findki(c,v);
		if(ki==-1)
		{
			c=c->ptr[c->count];
		}
		else
		{
			c=c->ptr[ki];
		}
	}
	return c;
}


struct node* addinto(struct node *n,int v,struct node *p)
{
	int un[100],so[100],i;
	struct node *ap[100];
	for(i=0;i<n->count;i++)
	{
		so[i] = n->key[i];
		un[i] = n->key[i];
		ap[i] =n->ptr[i];
	}
	so[n->count] = v;
	int d,c,t;
	//insertion sort
	for (c = 1 ; c <= n->count; c++)
	{
		d = c;

		while ( d > 0 && so[d] < so[d-1])
		{
			t          = so[d];
			so[d]   = so[d-1];
			so[d-1] = t;

			d--;
		}
	}
	int count = n->count;
	if(count!=0)
	{
		for(i=0;i<count+1;i++)
		{
			if(so[i] != v)
			{
				int j;
				for(j=0;j<count;j++)
				{
					if(un[j]==so[i])
					{
						n->key[i] = so[i];
						n->ptr[i] = ap[j];
					}
				}

			}
			else
			{
				n->key[i] = so[i];
				n->ptr[i] = p;
			}
		}
	}
	else
	{
		n->key[0] = so[0];
		n->ptr[0] = p;
	}
	n->count =count +1;
	return n;

}


struct node* insert_entry(struct node *l,int v,struct node *p)
{
	if(l->count<(degree-1))
	{
		l=addinto(l,v,p);
	}
	else
	{
		struct node *ll;
		ll=getnode();
		/* finding vv and m */
		int vv,m,thr,cou;
		cou = (degree/2);
		cou =cou;
		int tv,i,j;
		tv = v;
		for(i=0;i<l->count;i++)
		{
			if(l->key[i]<tv)
			{
				thr = thr +1;
			}
		}
		if(thr == cou)
		{
			vv = v;
			for(i=0;i<l->count;i++)
			{
				if(l->key[i]>vv)
				{
					m = i;
					break;
				}
			}
		}
		else
		{
			for(i =0;i<l->count;i++)
			{
				tv = l->key[i];
				thr=0;
				if(v<tv){thr = thr +1;}
				int j;
				for(j = 0;j<(i+1);j++)
				{
					if(l->key[j]<tv){thr = thr+1;}
				}
				if(thr == cou)
				{
					m = i;
					vv = tv;
					break;
				}
			}
		}
		// till here keeping atleast n-1 in c
		if(l->l==1)
		{
			int tmcou = l->count;
			for(i=m;i<l->count;i++)
			{
				ll=addinto(ll,l->key[i],l->ptr[i+1]);
				tmcou = tmcou -1;
				l->ptr[i]=NULL;
			}
			l->count = tmcou;

			if(v<vv)
			{
				l=addinto(l,v,p);
			}
			else
			{
				ll=addinto(ll,v,p);
			}
		}
		else
		{
			ll->l =0;

			if(v == vv)
			{
				int i;
				ll = addinto(ll,l->key[m],p);
				for(i=(m+1);i<l->count;i++)
				{
					ll = addinto(ll,l->key[i],l->ptr[i]);
				}

			}
			else
			{
				int i;
				for(i=(m+1);i<l->count;i++)
				{
					ll = addinto(ll,l->key[i],l->ptr[i]);
				}
			}
			l->count = m;
			if(v<vv)
			{
				l = addinto(l,v,p);
			}
			else
			{
				ll= addinto(ll,v,p);
			}
			int i;
			for(i=0;i<ll->count;i++)
			{
				ll->ptr[i]->pptr = ll;
			}
		}
		if(l!=root)
		{
			struct node *parl;
			parl=l->pptr;
			parl=insert_entry(parl,vv,l);
			parl = l->pptr;
			parl->ptr[parl->count] =ll;
			ll->pptr=l->pptr;
		}
		else
		{
			struct node *nroot;
			nroot=getnode();
			nroot->l =0;
			nroot=addinto(nroot,vv,l);
			nroot->ptr[1]=ll;
			l->pptr=nroot;
			ll->pptr=nroot;
			root=nroot;
		}
		if(l->l==1)
		{
			l->ptr[l->count]= ll;
		}

	}
	return root;

}


struct node* insert(int v,struct node *p)
{
	struct node *l;
	l=find(v);
	root=insert_entry(l,v,p);
	return root;
}
void ranksame(struct node *r,FILE *out){
if(r!=NULL){
	if(r->l ==1){
		fprintf(out,"st%d; ",r->sl);
	}
	if(r->l!=1)
		{ int i;
			for(i=0;i<=r->count;i++)
			{
				if(r->ptr[i]!=NULL){ranksame(r->ptr[i],out);}
			}
		}
}
}

void dump(struct node *r,FILE *out)
{
	if(r!=NULL)
	{
		int i;
		char st[1000],a[1000],b[1000];
		strcpy(st,"");
		strcpy(b," , ");
		for(i=0;i<r->count;i++)
		{
			snprintf(a,1000,"%d",r->key[i]);
			strcat(st,a);
			strcat(st,b);
		}
		fprintf(out,"st%d [label=\"%s\"",r->sl,st);
		fprintf(out,"];\n");
		if(r->l ==1 && r->ptr[r->count]!=NULL){fprintf(out,"st%d->st%d [style = dashed];\n",r->sl,r->ptr[r->count]->sl);}
		if(r->l!=1)
		{
			for(i=0;i<=r->count;i++)
			{
				if(r->ptr[i]!=NULL){dump(r->ptr[i],out);}
			}
		}
	}
}


void sdump(struct node *r,FILE *out)
{
	if(r!=NULL && r->l !=1)
	{
		int i;
		for(i=0;i<=r->count;i++)
		{
			fprintf(out,"st%d->st%d;\n",r->sl,r->ptr[i]->sl);
		}
		if(r->l!=1)
		{
			for(i=0;i<=r->count;i++)
			{
				if(r->ptr[i]!=NULL){sdump(r->ptr[i],out);
				}
			}
		}
	}

}


void main()
{
	printf("Enter the degree\t");
	scanf("%d",&degree);
	root=getnode();
	int i;
	FILE *pipe;
	//pipe = popen("rm b+.ps","r");
	int ch;
	while(1)
	{
		printf("Enter the choice\n1:Insert\n2:Print and Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("Enter number (unique)\n");
				scanf("%d",&i);
				root = insert(i,NULL);
				break;
			case 2:
				out=fopen("b+.txt","w");
				fprintf(out,"digraph struct{\nnode [shape=record];\n");
				dump(root,out);
				sdump(root,out);
				fprintf(out,"{rank=same;");
				ranksame(root,out);
				fprintf(out,"}\n");
				fprintf(out,"}");
				fclose(out);

				pipe=popen("dot -Tps b+.txt -o b+.ps","w");
				pipe=popen("evince b+.ps","r");
				pclose(pipe);
				exit(0);
				break;
			default:
				printf("Enter legitimate input\n");
				break;
		}
	}

}
