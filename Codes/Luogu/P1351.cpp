#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1, mod = 1e4 + 7;

int w[maxn], f[maxn], head[maxn];
int n, res, tot;

class Edge {
    public:
        int to, nxt;
        Edge() {}
        Edge(int a, int b) : to(a), nxt(b) {}
};

Edge E[maxn];

inline void Add_edge(int u, int v) {
    E[++tot] = Edge(v, head[u]);
    head[u] = tot;
}


inline void Dfs(int x, int fa) {
    int ress = 0, maxx = 0;
    for(int v, i = head[x]; i; i = E[i].nxt) {
        if((v = E[i].to) ^ fa) {
            f[x] = max(f[x], w[v] * maxx), res = (res + (w[v] * ress) % mod) % mod;
            for(int vv, e = head[v]; e; e = E[e].nxt)
                if((vv = E[e].to) ^ x)
                    f[x] = max(f[x], w[x] * w[vv]), res = (res + (w[x] * w[vv]) % mod) % mod;
            Dfs(v, x);
            f[x] = max(f[x], f[v]);
            ress = (ress + w[v]) % mod, maxx = max(maxx, w[v]);
        }
    }
}

signed main() {
    n = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v);
        Add_edge(v, u);
    }
    
    for(int i = 1; i <= n; ++i)
        w[i] = read();

    Dfs(1, 0);
    printf("%d %d\n", f[1], (res * 2) % mod);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
