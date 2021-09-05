// 'Cause we were both young when I first saw you
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
//#define int long long
using namespace std;
const int INF = 1e9 + 7;
const int kM = 3e6 + 10;
int ver[kM], edge[kM], head[kM], nxt[kM], d[kM];
bool v[kM], can[kM], bian[kM];
int n, m;
priority_queue< pair<int, int> > q;
int tot;
void add(int x, int y ,int z, int k)
{
	ver[++tot] = y;
	edge[tot] = z;
	nxt[tot] = head[x];
	head[x] = tot;
	bian[tot] = k;
}
void dfs(int s, int k)
{
	for(int i = 1 ; i <= n; i++)
	{
		d[i] = INF;
	}
	d[s] = 0;
	q.push(make_pair(0, s));
	while(!q.empty())
	{
		int x = q.top().second;
		q.pop();
		if(v[x])
		{
			continue;
		}
		v[x] = 1;
		for(int i = head[x]; i; i = nxt[i])
		{
			if(bian[i] != k)
			{
				continue;
			}
			int y = ver[i], z = edge[i];
			if(can[y] == 1)
			{
				continue;
			}
			if(d[y] > d[x] + z)
			{
				d[y] = d[x] + z;
				q.push(make_pair(-d[y], y));
			}
		}
	}
	return ;
}
int main()
{
	scanf("%d%d", &n, &m);
	int x, y;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		add(x, y, 1, 1);
		add(y, x, 1, 0);
	}
	int s, t;
	scanf("%d%d", &s, &t);
	dfs(t, 0);
	for(int i = 1; i <= n; i++)
	{
//		cout<<d[i]<<endl<<endl;
		if(d[i] == INF)
		{
			can[i] = 1;
//			cout<<i<<endl;
			continue;
		}
		for(int j = head[i]; j; j = nxt[j])
		{
			if(bian[j] == 0)
			{
				continue;
			}
			int y = ver[j];
			if(d[y] == INF)
			{
				can[i] = 1;
//				cout<<i<<endl;
				break;
			}
		}
	}
	memset(d, 0, sizeof(d));
	memset(v, 0, sizeof(v));
	dfs(s, 1);
	for(int i = 1; i <= n; i++)
	{
//		cout<<d[i]<<endl<<endl;
//		if(d[i] == INF)
//		{
//			can[i] = 1;
//		}
	}
	if(d[t] == INF)
	{
		cout<<"-1";
	}
	else
	{
		cout<<d[t];
	}
	return 0;
}