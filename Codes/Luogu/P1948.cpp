#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define int long long
#define P make_pair
using namespace std;
const int kM = 3e6 + 10;
const int INF = 1e9 + 10;
int n, p, k, tot, ans, id[kM], cnt, dis[kM], pre[kM];
bool vis[kM];
int a, b, l, num;
int ver[kM], head[kM], nxt[kM], edge[kM];
priority_queue< pair<int, int> > q;
void add(int x, int y, int z)
{
	ver[++tot] = y;
	edge[tot] = z;
	nxt[tot] = head[x];
	head[x] = tot;
}
bool dij(int kk)
{
	for(int i = 1; i <= n; i++)
	{
		dis[i] = INF;
//		vis[i] = 0;
//		cout<<"sds " << d[i]<<endl;
	}
	int s = 0;
	dis[1] = 0;
	vis[1] = 1;
	q.push(P(1, 0));
	while(!q.empty())
	{
//		cnt++;
//		if(cnt > 1000)
//		{
//			return 0;
//		}
		int x = q.top().first;
		q.pop();
//		cout<<d[x]<<endl;
//		if(vis[x])
//		{
//			continue;
//		}
//		vis[x] = 1;
		for(int i = head[x]; i; i = nxt[i])
		{
			int y = ver[i], z = edge[i];
//			cout<<d[y]<<" "<<z<<endl;
			if(z > kk)
			{
				s = dis[x] + 1;
			}
			else
			{
				s = dis[x];
			}
			if(s < dis[y])
			{
				dis[y] = s;
				if(!vis[y])
				{
//					num++;
					q.push(P(y, -dis[y]));
//					if(num > 1000)
//					{
//						num = 0;
//					}
				}
			}
		}
		vis[x] = 0;
	}
	if(dis[n] <= k)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
signed main()
{
	scanf("%lld%lld%lld", &n, &p, &k);
	for(int  i = 1; i <= p; i++)
	{
		scanf("%lld%lld%lld", &a, &b, &l);
		add(a, b, l);
		add(b, a, l);
	}
	int ans = -1;
	int l=0, r=1000000, mid;
	while(l <= r)
	{
		mid = (l + r) / 2;
		if(dij(mid))
		{
			r = mid - 1;
			ans = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%lld", ans);
	return 0;
}