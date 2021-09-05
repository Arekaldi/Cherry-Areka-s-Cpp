#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1, Mod = 1e9 + 7;

int n, tot, K, f[maxn][101][2][2], head[maxn],
to[maxn], nxt[maxn], sz[maxn], g[101][2][2];

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u],
    head[u] = tot;
}

// f_x,j,0/1,0/1 -> 是否被选中/是否被孩子覆盖
#define to1 v
#define siz sz
#define mod Mod
inline void Dfs1(int x, int fa) {
    // sz[x] = 1, f[x][0][0][0] = f[x][1][1][0] = 1;
    f[x][1][1][0]=1;f[x][0][0][0]=1;siz[x]=1;
    // 若没被覆盖、没被选中的话，就只能自己选中自己
    // 可以靠父亲覆盖
    for(int i = head[x]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == fa)
            continue;
        Dfs1(v, x);
        int mx = min(sz[x], K), mt = min(sz[v], K);
        for(int j = 0; j <= mx; ++j)
            for(int k = 0; k < 2; ++k)
                for(int l = 0; l < 2; ++l)
                    g[j][k][l] = f[x][j][k][l], f[x][j][k][l] = 0;
        // 把上一个子树的状态存下来 *
        for(int j = 0; j <= mx; ++j) {
            for(int k = 0; k <= mt and j + k <= K; ++k) {
                // x 没有被选的情况下，子树里的转移只能是被孙子覆盖的情况
                // 枚举 x 子树和小子树里分别选了多少
                f[x][j + k][0][0] = (f[x][j + k][0][0] + (ll)g[j][0][0] * f[v][k][0][1]) % Mod;
                // x 既没有被选又没有被覆盖，那么他只能靠他的父亲覆盖他，且子树里不能存在被选的情况
                f[x][j + k][0][1] = (f[x][j + k][0][1] + (ll)g[j][0][1] * (f[v][k][0][1] + f[v][k][1][1]) + (ll)g[j][0][0] * f[v][k][1][1]) % Mod;
                // x 没有被选，却被覆盖，就考虑子树中至少出现 1 个被选
                // 孩子必须都被覆盖，因为父亲靠不住
                // 考虑 g 是原来的子树，必须选，v 可以不选
                f[x][j + k][1][0] = (f[x][j + k][1][0] + (ll)g[j][1][0] * (f[v][k][0][1] + f[v][k][0][0])) % Mod;
                f[x][j + k][1][1] = (f[x][j + k][1][1] + (ll)g[j][1][1] * (f[v][k][0][1] + f[v][k][0][0]) + (ll)(g[j][1][0] + g[j][1][1]) * (f[v][k][1][0] + f[v][k][1][1])) % Mod;

            }
        }
        sz[x] += sz[v];
    }
    return;
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("polynomial.in", "r", stdin);
        freopen("polynomial.out", "w", stdout);
    #endif

    memset(head, -1, sizeof(head));
    n = read(), K = read();

    for(int i = 1, u, v; i < n; ++i) {
        u = read(), v = read();
        Add_edge(u, v), Add_edge(v, u);
    }
    
    Dfs1(1, 0);

    int res = (f[1][K][0][1] + f[1][K][1][1]) % Mod;
    
    printf("%d\n", res);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
