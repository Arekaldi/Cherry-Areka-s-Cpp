#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include <cstring>
using namespace std;
#define int long long
const int kM = 1e6 + 10;
const int INF = 0x7f7f7f7f;
int tot = -1, n, m, maxflow, mincost;
bool vis[kM], inq[kM];
int cost[kM], dep[kM];
int ver[kM], head[kM], nxt[kM], edge[kM], cur[kM];
queue<int> q;
void add(int x, int y, int z, int c)
{
	ver[++tot] = y;
	edge[tot] = z;
	cost[tot] = c;
	nxt[tot] = head[x];
	head[x] = tot;
	ver[++tot] = x;
	edge[tot] = 0;
	cost[tot] = -c;
	nxt[tot] = head[y];
	head[y] = tot;
}
bool spfa(int s, int t)
{
    memset(dep, 0x7f, sizeof(dep));
    memset(inq, false, sizeof(inq));
	q.push(s);
	dep[s] = 0, inq[s] = true;
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		inq[x] = false;
		for(int i = head[x]; i > -1; i = nxt[i])
		{
			int z = edge[i], y = ver[i], c = cost[i];
			if(z && dep[x] + c < dep[y])
			{
				dep[y] = dep[x] + c;
				if(!inq[y])
				{
					q.push(y);
					inq[y] = 1;
				}
			}
		}
	}
	return dep[t] != INF;
}
int dfs(int x, int t, int flow)
{
	if(x == t)
		return flow;
	vis[x] = 1;
	int res = flow, k;
	for(int i = cur[x]; i > -1; i = nxt[i])
	{
		int z = edge[i], y = ver[i], c = cost[i];
		if(vis[y] || !z || dep[y] != dep[x] + c)
		{
			continue;
		}
		cur[x] = i;
		int k = dfs(y, t, min(res, z));
		if(!k)
		{
			dep[y] = -1;
		}
		res -= k;
		edge[i] -= k;
		edge[i ^ 1] += k;
	}
	vis[x] = 0;
    if(res)
        dep[x] = 0;
	return flow - res;
}
void dinic(int s, int t)
{
	while(spfa(s, t))
	{
		memcpy(cur, head, sizeof(cur));
		int k = dfs(s, t, INF);
        maxflow += k, mincost += k * dep[t];
	}
}
signed main()
{
	int s, t;
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
    memset(head, -1, sizeof(head));
	int u, v, w, c;
	for(int i = 1; i <= m; i++)
	{
		scanf("%lld%lld%lld%lld", &u, &v, &w, &c);
		add(u, v, w, c);
	}
	dinic(s, t);
	printf("%lld %lld", maxflow, mincost);
	return 0;
}