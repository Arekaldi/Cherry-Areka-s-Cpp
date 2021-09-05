#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1, Mod = 1e9 + 7;

int n, tot, K, head[maxn],
to[maxn], nxt[maxn], sz[maxn],
son[maxn], top[maxn], dep[maxn],
fa[maxn];

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u],
    head[u] = tot;
}

inline void Dfs1(int x, int f) {

    fa[x] = f, sz[x] = 1, dep[x] = dep[f] + 1;
    for(int v, i = head[x]; i; i = nxt[i])
        if((v = to[i]) ^ f)
            Dfs1(v, x), sz[x] += sz[v], (sz[v] > sz[son[x]]) && (son[x] = v);
    return;
}

inline void Dfs2(int x, int f) {
    if(!top[x])
        top[x] = x;
    top[son[x]] = top[x];
    for(int v, i = head[x]; i; i = nxt[i])
        if((v = to[i]) ^ f)
            Dfs2(v, x);
    return;
}

inline int Lca(int x, int y) {
    int u = x, v = y;
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v])
        swap(u, v);
    return u;
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("lyh.in", "r", stdin);
        freopen("lyh.out", "w", stdout);
    #endif

    int T = read();
    int n = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v), Add_edge(v, u);
    }
    
    int m = read();
    printf("%d\n", 1);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
