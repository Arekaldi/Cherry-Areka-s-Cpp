#include<bits/stdc++.h>
#define N 200005
using namespace std;
int tot,n,m;
int a[N],poz[N];
int head[N],to[N],nex[N];
int sy[N],kuai[N][404],len;
int fa[N],sz[N];
int ans[N],mode[N],x[N],y[N];
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
void add(int x,int y)
{
	++tot;
	nex[tot]=head[x];
	to[tot]=y;
	head[x]=tot;
	return ;
}
int find(int k)
{
	if(k==fa[k])
		return k;
	return find(fa[k]);
}
int query(int k)
{
	x[k]=find(x[k]);
	for(int i=0;i<=sy[n];i++)
	{
	  	if(y[k]>kuai[x[k]][i])
		{
			y[k]-=kuai[x[k]][i];
		}
		else
		{
			for(int j=i*len+1;j<=(i+1)*len&&j<=n;j++)
			{
				if ((find(poz[j])==x[k]))
				{
					--y[k];
					if(y[k]==0)
					return a[poz[j]];
				}
			}
		}
	}
	return -1;
}
void add(int k)
{
	y[k]=find(y[k]);
	x[k]=find(x[k]);
	if (x[k]==y[k])return;
	if (sz[x[k]]>sz[y[k]])
		swap(x[k],y[k]);
	fa[x[k]]=y[k];
	sz[y[k]]+=sz[x[k]];
	for(int i=0;i<=sy[n];i++)
		kuai[y[k]][i]+=kuai[x[k]][i];
	return ;
}
void del(int k)
{
	if (x[k]==y[k])return;
	fa[x[k]]=x[k];
	sz[y[k]]-=sz[x[k]];
	for(int i=0;i<=sy[n];i++)
		kuai[y[k]][i]-=kuai[x[k]][i];
	return ;
}
void dfs(int k)
{
	if (mode[k]==1)
		add(k);
	if (mode[k]==3)
		ans[k]=query(k);
	for(int i=head[k];i;i=nex[i])
		dfs(to[i]);
	if (mode[k]==1)
		del(k);
	return ;
}
int main()
{
	freopen("1.txt","r",stdin);
	freopen("ans.txt","w",stdout);
	scanf("%d %d",&n,&m);
	len=1111;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;++i)
		poz[i]=i;
	sort(poz+1,poz+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		sy[i]=(i-1)/len;
		sz[i]=kuai[poz[i]][sy[i]]=1;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&mode[i],&x[i]);
		if(mode[i]==2)
		{
			add(x[i],i);
		}
		else
		{
			scanf("%d",&y[i]);
			add(i-1,i);
		}
	}
	dfs(0);
	for(int i=1;i<=m;i++)
	{
		if (mode[i]==3)
		{
			printf("%d\n",ans[i]);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}