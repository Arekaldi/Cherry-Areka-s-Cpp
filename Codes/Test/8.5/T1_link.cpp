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

int n, tot, K, f[maxn][101][2][2], head[maxn],
to[maxn], nxt[maxn], sz[maxn];

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u],
    head[u] = tot;
}

inline void Dfs1(int x, int f) {
    sz[x] = 1;
    for(int v, i = head[x]; i; i = nxt[i])
        if((v = to[i]) ^ f)
            Dfs1(v, x), sz[x] += sz[v];
    return;
}

inline void Dfs2(int x, int fa) {
    f[x][0][1][0] = f[x][1][1][1] = 1;
    for(int v, i = head[x]; i; i = nxt[i]) {
        v = to[i];
        if(v == fa)
            continue;
        f[x][0][1][0] = f[x][1][1][1] = 0;
        Dfs2(v, x);
        for(int j = 0; j <= sz[x]; ++j) {
            if(j)
                f[x][j][1][1] = (f[x][j][1][1] + f[v][j - 1][0][0] + f[v][j - 1][1][0]) % Mod;
            if(j)
                f[x][j][0][1] = (f[x][j][0][1] + f[v][j - 1][0][1] + f[v][j - 1][1][1]) % Mod;
            f[x][j][1][0] = (f[x][j][1][0] + f[v][j][0][0]) % Mod;
            f[x][j][0][0] = (f[x][j][0][0] + f[v][j][0][1]) % Mod;
            if(sz[v] == 1)
                f[x][j][0][0] = f[x][j][1][0] = 0;
        }
    }
}

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("polynomial.in", "r", stdin);
        freopen("polynomial.out", "w", stdout);
    #endif

    n = read(), K = read();

    for(int i = 1, u, v; i < n; ++i)
    (u = read(), v = read(), 1) &&
    (Add_edge(u, v), Add_edge(v, u), 1);
    
    Dfs1(1, 0);
    Dfs2(1, 0);

    int res = 0;
    for(int i = 1; i <= K; ++i)
        res += f[1][i][0][0] + f[1][i][0][1];
    
    printf("%d\n", res);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
