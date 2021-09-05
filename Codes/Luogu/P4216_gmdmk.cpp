#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int kM = 3e6 + 10;
int shu[kM], ans[kM], sc[kM], tot;
int f[kM][30], lg[kM], n, tre[kM];
int ver[kM], head[kM], nxt[kM], edge[kM], dep[kM];
struct js
{
    int val, id, fu;
};
vector<js> a[kM];
void add(int x, int y)
{
    ver[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}
void log()
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
}
void dfs(int x, int fa)
{
    f[x][0] = fa;
    dep[x] = dep[fa] + 1;
    for(int i = 1; i <= 25; i++)
    {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for(int i = head[x]; i; i = nxt[i])
    {
        int y = ver[i];
        if(y == fa)
        {
            continue;
        }
        dfs(y, x);
    }
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
    for(int i = 25; i >= 0; i--)
    {
        if(f[x][i] != f[y][i])
        {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
int lowbit(int x)
{
    return x & (-x);
}
void chage(int x, int v)
{
    while(x <= n)
    {
        tre[x] += v;
        x += lowbit(x);
    }
}
int ask(int x)
{
    int res = 0;
    while(x)
    {
        res += tre[x];
        x -= lowbit(x);
    }
    return res;
}
void Dfs(int x, int fa)
{
    if(sc[x] != 0)
    {
        chage(sc[x] + 1, 1);
    }
    for(int i = 0; i < a[x].size(); i++)
    {
        js xx = a[x][i];
        ans[xx.id] += ask(xx.val) * xx.fu;
    }
    for(int i = head[x]; i; i = nxt[i])
    {
        int y = ver[i];
        if(y == fa)
        {
            continue;
        }
        Dfs(y, x);
    }
    if(sc[x] != 0)
    {
        chage(sc[x] + 1, -1);
    }
}
signed main()
{
    scanf("%lld", &n);
    int p, rot;
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &p);
        if(p == 0)
        {
            rot = i;
        }
        add(i, p);
        add(p, i);
    }
    log();
    dfs(rot, 0);
    int cnt = 0, q = 0, opt = 0, u = 0, v = 0, c = 0, x = 0;
    scanf("%lld", &q);
    for(int i = 1; i <= q; i++)
    {
        scanf("%lld", &opt);
        if(opt == 1)
        {
            scanf("%lld%lld%lld", &u, &v, &c);          
            if(i < c)
            	continue;
            a[u].push_back(js{i - c, ++cnt, 1});
            a[v].push_back(js{i - c, cnt, 1});
            int l = lca(u, v);
            a[l].push_back(js{i - c, cnt, -1});
            a[f[l][0]].push_back(js{i - c, cnt, -1});
            shu[cnt] = dep[u] + dep[v] - dep[l] - dep[f[l][0]];
        }
        else
        {
            scanf("%lld", &x);
            sc[x] = i;
        }
    }
    Dfs(rot, 0);
    for(int i = 1; i <= cnt; i++)
    {
        printf("%lld %lld\n", shu[i], ans[i]);
    }
    return 0;
}
