#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

class Edge {
    public:
        int to, nxt, val;
        Edge() {}
        Edge(int a, int b, int c) : to(a), nxt(b), val(c) {}
};

Edge E[maxn];
int tot, n, s, p, ans = (1 << 30), head[maxn],
    dis[maxn], f[maxn];
bool vis[maxn];

inline void Add_edge(int u, int v, int w) {
    E[++tot] = Edge(v, head[u], w);
    head[u] = tot;
}

inline void Dfs(int fa, int x) {
    f[x] = fa;
    if(dis[x] > dis[p])
        p = x;
    for(int v, i = head[x]; i; i = E[i].nxt) {
        if(((v = E[i].to) ^ fa) and !vis[v]) {
            dis[v] = dis[x] + E[i].val;
            Dfs(x, v);
        }
    }
}

signed main() {
    n = read(), s = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
        Add_edge(v, u, w);
    }
    Dfs(0, 1);
    dis[p] = 0; Dfs(0, p);
    
    for(int p1 = p, p2 = p; p1; p1 = f[p1]) {
        while(dis[p2] - dis[p1] > s)
            p2 = f[p2];
        
        ans = min(ans, max(dis[p] - dis[p2], dis[p1]));
    }

    for(int i = p; i; i = f[i])
        vis[i] = true;

    for(int i = p; i; i = f[i])
        dis[i] = 0, Dfs(f[i], i);

    for(int i = 1; i <= n; ++i)
        ans = max(ans, dis[i]);
    
    cout << ans;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
