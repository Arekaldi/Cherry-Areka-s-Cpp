#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int kM = 1e6 + 10;
int a[kM], bl[10100], lg[kM], n, m;
int e[kM], s[kM], t[kM], cnt1[kM];
int ans1, tot, cnt, f[kM][25], ans[kM];
int ver[kM], nxt[kM], head[kM], dep[kM];
bool use[kM];
struct js
{
	int l, r, id, lca, pos;
}ask[kM];
bool cmp(js x, js y)
{
	if(x.pos == y.pos)
	{
		return x.r < y.r;
	}
	return x.pos < y.pos;
}
void suan_log()
{
	int t = 0, res = 2;
	for(int i = 1; i <= n; i++)
	{
		if(i >= res)
		{
			res *= 2;
			t++;
		}
		lg[i] = t;
	}
	return ;
}
void add(int x, int y)
{
	ver[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}
void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	e[++cnt] = u;//记录欧拉序 
	s[u] = cnt;//记录开始位置 
	for(int i = 1; i <= 20; i++)
	{
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	for(int i = head[u]; i; i = nxt[i])
	{
		int y = ver[i];
		if(y == fa)
		{
			continue;
		}
		dfs(y, u);
	}
	e[++cnt] = u;//记录欧拉序 
	t[u] = cnt;//记录结束位置 
	return ;
}
int lca(int x, int y)
{
	if(dep[x] < dep[y])
	{
		swap(x, y);
	}
	while(dep[x] > dep[y])
	{
		x = f[x][lg[dep[x] - dep[y]]];
	}
	if(x == y)
	{
		return x;
	}
	for(int i = 20; i >= 0; i--)
	{
		if(f[x][i] != f[y][i])
		{
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}
void update(int x)
{
	if(!(use[x] ^= 1) && (--cnt1[a[x]]) == 0)//注意先减在判断 
	{
		ans1--;
	}
	if(use[x] && (cnt1[a[x]]++) == 0)//注意判断完再加 
	{
		ans1++;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	int len = sqrt(n);
	suan_log();
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		t[i] = a[i];
	}
	sort(t + 1, t + 1 + n);
	int tot = unique(t + 1, t + 1 + n) - t - 1;
	for(int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(t + 1, t + 1 + tot, a[i]) - t;
	}
	int u, v;
	for(int i = 1; i <= n - 1; i++)
	{
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		int l = lca(u, v);
		ask[i].id = i;
		if(u == l || v == l)
		{
			if(s[v] < s[u])
			{
				swap(u, v);
			}
			ask[i].l = s[u];
			ask[i].r = s[v];
		}
		else
		{
			if(t[v] < s[u])
			{
				swap(u, v);
			}
			ask[i].l = t[u];
			ask[i].r = s[v];
			ask[i].lca = l;
		}
		ask[i].pos = ask[i].l / len;
	}
	sort(ask + 1, ask + 1 + m, cmp);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++)
	{
        cout << ask[i].l << " " << ask[i].r << endl;
		while(l > ask[i].l)
		{
			l--;
			update(e[l]);
		}
		while(r < ask[i].r)
		{
			r++;
			update(e[r]);
		}
		while(l < ask[i].l)
		{
			update(e[l]);
			l++;
		}
		while(r > ask[i].r)
		{
			update(e[r]);
			r--;
		}
		if(ask[i].lca)
		{
			update(ask[i].lca);
		}
		ans[ask[i].id] = ans1;
		if(ask[i].lca)
		{
			update(ask[i].lca);
		}
	}
	for(int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}