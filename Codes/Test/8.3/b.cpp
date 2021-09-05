#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int n, tot, Rt;

int head[maxn], cnt;
class Edge {
    public:
        int to, nxt, val;
};

Edge E[maxn];
inline void Add_edge(int u, int v, int w) {
    E[++cnt].to = v, E[cnt].nxt = head[u], E[cnt].val = w;
    head[u] = cnt;
}

int dis[maxn], sz[maxn];
inline void Dfs1(int x, int f) {
    sz[x] = 1;
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == f)
            continue;
        dis[v] = dis[x] + E[i].val;
        Dfs1(v, x);
        sz[x] += sz[v];
    }
}

int dep[maxn], ct[maxn], c[maxn], cl[maxn];
int col[maxn], a[maxn], b[maxn];
int ask[maxn];
pair <int, int> ans[maxn];

signed main() {

    #define Areka
    #ifdef Areka
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
        Add_edge(v, u, w);
    }
    
    Dfs1(1, 0);

    for(int i = 1; i <= n; ++i)
        a[i] = read(), b[i] = a[i];

    sort(a + 1, a + n + 1);

    int tt = unique(a + 1, a + n + 1) - a - 1;
    for(int i = 1; i <= n; ++i)
        col[i] = lower_bound(a + 1, a + tt + 1, b[i]) - a;

    for(int i = 1; i <= n; ++i) {
        ask[i] = read();
        if(ask[i] > sz[i])
            ans[i].second = -1;
    }

    // Dfs2(1, 0);

    for(int i = 1; i <= n; ++i)
        cout << col[i] << " " << -1 << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
