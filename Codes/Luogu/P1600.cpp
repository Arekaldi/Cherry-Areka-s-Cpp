#include<bits/stdc++.h>
#define g() getchar()
#define il inline
#define eps 1e-10
#define LL long long
#define pa pair<int, int>
#define for_1(i, n) for(int i = 1; i <= (n); ++i)
#define for_0(i, n) for(int i = 0; i <= (n); ++i)
#define for_xy(i, x, y) for(int i = (x); i <= (y); ++i)
#define for_yx(i, x, y) for(int i = (x); i >= (y); --i)
#define for_edge(i, x) for(int i = head[x]; i; i = nxt[i])
#define int long long
#define DB double
// #define mid ((l + r) >> 1)
using namespace std;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;

inline int re()
{
	int x = 0, p = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') p = -1; ch = getchar();}
	while(ch <= '9' and ch >= '0') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * p;
}

int n, m;
map<int, int> up[N], down[N];
vector<int> del_up[N], del_down[N];

int head[N], ver[N], nxt[N], tot;
il void add(int x, int y)
{
    ver[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}

int dep[N], fa[N], son[N], maxson, siz[N];
il void dfs1(int x, int f)
{
    fa[x] = f; dep[x] = dep[f] + 1; siz[x] = 1; maxson = -1;
    for_edge(i, x)
    {
        int y = ver[i]; if(y == f) continue;
        dfs1(y, x);
        siz[x] += siz[y];
        if(maxson < siz[y]) {maxson = siz[y]; son[x] = y;}
    }
}

int top[N], ans[N], w[N];
il void dfs2(int x, int tp)
{
    top[x] = tp;
    if(!son[x]) return ;
    dfs2(son[x], tp);
    for_edge(i, x)
    {
        int y = ver[i]; if(y == fa[x] || y == son[x]) continue;
        dfs2(y, y);
    }
}

il int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] > dep[top[y]])
            x = fa[top[x]];
        else y = fa[top[y]];
    }
    return dep[x] < dep[y] ? x : y;
}

il void del(map<int, int> &x, vector<int> &y)
{
    for(int i = 0; i < y.size(); ++i)
    {
        x[y[i]]--;
        if(!x[y[i]])
        {
            auto it = x.lower_bound(y[i]);
            x.erase(it);
        }
    }
}

il void merge(map<int, int> &x, map<int, int> &y)
{
    if(x.size() < y.size()) swap(x, y);
    while(!y.empty())
    {
        auto it = y.begin();
        x[it->first] += it->second;
        y.erase(it);
    }
}

il void calc(int x, int f)
{
    for_edge(i, x)
    {
        int y = ver[i]; if(y == f) continue;
        calc(y, x);
        merge(down[x], down[y]);
        merge(up[x], up[y]);
    }
    del(down[x], del_down[x]);
    ans[x] = up[x][-dep[x] - w[x]] + down[x][dep[x] - w[x]];
    del(up[x], del_up[x]);
}

signed main()
{
    n = re(), m = re();
    for_1(i, n - 1) {int x = re(), y = re(); add(x, y), add(y, x);};
    for_1(i, n) w[i] = re();
    dfs1(1, 0), dfs2(1, 1);
    for_1(i, m)
    {
        int x = re(), y = re();
        int lc = lca(x, y);
        up[x][-dep[x]]++;
        del_up[lc].push_back(-dep[x]);
        down[y][dep[lc] - (dep[x] - dep[lc])]++;
        del_down[lc].push_back(dep[lc] - (dep[x] - dep[lc]));
    }
    calc(1, 1);
    for_1(i, n) cout<<ans[i]<<" ";
}