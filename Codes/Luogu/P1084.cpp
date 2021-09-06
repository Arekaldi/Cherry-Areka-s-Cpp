#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1, maxt = 16;
typedef pair <int, int> pii;

inline bool operator < (const pii &a, const pii & b) {
    return a.first == b.first ? a.second < b.second : a.first < b.first;
}

int n, m, tot, top, total1, total2, t, head[maxn],
    dep[maxn], fa[maxn][maxt], dis[maxn][maxt],
    id[maxn], lev[maxn], lea[maxn];

pii sta[maxn];
bool vis[maxn], ned[maxn];

class Edge {
    public:
        int to, nxt, val;
        Edge() {}
        Edge(int a, int b, int c) : to(a), nxt(b), val(c) {}
};

Edge E[maxn];

inline void Add_edge(int u, int v, int w) {
    E[++tot] = Edge(v, head[u], w);
    head[u] = tot;
}

inline void Dfs1(int x, int ff) {
    dep[x] = dep[ff] + 1, fa[x][0] = ff;
    for(int i = 1; i <= t; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1],
        dis[x][i] = dis[x][i - 1] + dis[fa[x][i - 1]][i - 1];
    for(int v, i = head[x]; i; i = E[i].nxt) {
        if((v = E[i].to) ^ ff) {
            dis[v][0] = E[i].val;
            Dfs1(v, x);
        }
    }
}

inline bool Dfs2(int x, int ff) {
    if(vis[x])
        return true;
    bool Leaf = false;
    for(int v, i = head[x]; i; i = E[i].nxt)
        if((v = E[i].to) ^ ff) {
            Leaf = true;
            if(!Dfs2(v, x))
                return false;
        }
    if(!Leaf)
        return false;
    return true;
}

inline bool check(int x) {
    memset(vis, false, sizeof(vis));
    memset(ned, false, sizeof(ned));
    top = total1 = total2 = 0;
    for(int i = 1; i <= m; ++i) {
        int now = id[i], cnt = 0;
        for(int j = t; j >= 0; --j) {
            if(fa[now][j] > 1 and cnt + dis[now][j] <= x)
                cnt += dis[now][j], now = fa[now][j];
        }
        if(fa[now][0] == 1 and cnt + dis[now][0] <= x)
            sta[++top] = make_pair(x - cnt - dis[now][0], now);
            // 把他放到 1 节点上
        else
            vis[now] = true;
    }

    for(int v, i = head[1]; i; i = E[i].nxt)
        if(((v = E[i].to) ^ 0) and !Dfs2(v, 1))
            ned[v] = true;

    sort(sta + 1, sta + top + 1);
    for(int i = 1; i <= top; ++i) {
        if(ned[sta[i].second] and sta[i].first < dis[sta[i].second][0] )
            ned[sta[i].second] = false;
            // 回不去了就不来
        else
            lev[++total1] = sta[i].first;
    }

    for(int v, i = head[1]; i; i = E[i].nxt)
        if((v = E[i].to) ^ 0 and ned[v])
            lea[++total2] = dis[v][0];
    if(total1 < total2)
        return false;
    sort(lev + 1, lev + total1 + 1);
    sort(lea + 1, lea + total2 + 1);
    int p1 = 1, p2 = 1;
    while(p1 <= total1 and p2 <= total2) {
        if(lev[p1] >= lea[p2])
            p1++, p2++;
        else
            p1++;
    }
    
    return (p2 > total2);
}

signed main() {
    n = read(), t = log2(n);
    int l = 0, r = 0, ans = -1;
    for(int u, v, w,i = 1; i < n; ++i) {
        u = read(), v = read(), w = read();
        Add_edge(u, v, w), Add_edge(v, u, w), r += w;
    }

    Dfs1(1, 0);
    
    m = read();
    for(int i = 1; i <= m; ++i)
        id[i] = read();
    
    while(l <= r) {
        int mid = (l + r >> 1);
        if(check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
