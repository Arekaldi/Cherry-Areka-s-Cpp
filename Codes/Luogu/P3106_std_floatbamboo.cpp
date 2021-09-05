
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
priority_queue<P,vector<P>,greater<P> > q;
const int N=5e4+100;
int tot,n,m;
int u[N],v[N],val_a[N],val_b[N],dis_a[N],dis_b[N],dis_c[N];
int edge[N],head[N],ver[N],nxt[N],vis[N];
int read() {
	int x = 0, f = 1, ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
	return x * f;
}
void add(int x,int y,int z)
{
	ver[++tot]=y;
	edge[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
void Dij(int s,int *dis)
{
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	vis[s]=0;
	q.push(P(dis[s],s));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])
		continue;
		vis[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=ver[i],z=edge[i];
			if(dis[y]>=dis[x]+z)
			{
				dis[y]=dis[x]+z;
				q.push(P(dis[y],y));
			}
		}
	}
    for(int i = 1; i <= n; ++i)
        cout << dis[i] << " ";
    cout << endl;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
        u[i]=read();
		v[i]=read();
		val_a[i]=read();val_b[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		add(u[i],v[i],val_a[i]);
	}
	memset(dis_a,0x3f,sizeof(dis_a));
	Dij(1,dis_a);
	memset(head,0,sizeof(head));
//	memset(nxt,0,sizeof(nxt));
	tot=0;
	for(int i=1;i<=m;i++)
	{
		add(u[i],v[i],val_b[i]);
	}
	memset(dis_b,0x3f,sizeof(dis_b));
	Dij(1,dis_b);
	memset(head,0,sizeof(head));
//	memset(nxt,0,sizeof(nxt));
	tot=0;
	for(int i=1;i<=m;i++)
	{
		int num=0;
		if(dis_a[u[i]]+val_a[i]!=dis_a[v[i]])
		num++;
		if(dis_b[u[i]]+val_b[i]!=dis_b[v[i]])
		num++;
        cout << num << endl;
		add(u[i],v[i],num);
	}
	memset(dis_c,0x3f,sizeof(dis_c));
	Dij(1,dis_c);
	printf("%d\n",dis_c[n]);
	return 0;
} 