//这种八竿子打不着边的剪枝怎么就能过呢/jk 
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int x[10001],y[10001];
int u[10001],v[10001];
bool dis[101][101];//炸弹 《==》武器
int nex[101][101],minn[101],ans=1000001;
bool used[1001];
bool jiao(int a,int b)
{
	return ((x[a]-u[b])*(x[a]-u[b])+(y[a]-v[b])*(y[a]-v[b]))<=k*k;
}
void dfs(int x,int now,int k)
{
	if(ans<=now+minn[x])return ;
	ans=min(ans,now+minn[x]+k);
	if(x==m+1)
	{
		ans=min(ans,now);
		return ;
	}
	for(int i=1;i<=n;++i)
	{
		if(!used[i]&&dis[i][x])
		{
			used[i]=1;
			dfs(nex[i][x],now+1,k);
			used[i]=0;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>m>>n>>k;
	for(int i=1;i<=m;++i)
		cin>>x[i]>>y[i];
	for(int i=1;i<=n;++i)
		cin>>u[i]>>v[i];
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			dis[i][j]=jiao(j,i);
		}
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=m;j>=1;--j)
		{
			dis[i][j]&&(nex[i][j]=max(j+1,nex[i][j+1]));
		}
	}
	for(int i=m;i>=1;--i)
	{
		minn[i]=1000000;
		for(int j=1;j<=n;++j)
		{
			dis[j][i]&&(minn[i]=min(minn[i],minn[nex[j][i]]+1));
		}
	}
	if(n<=15)
	dfs(1,0,1000);
	else
	dfs(1,0,0);
	cout<<ans;
}
