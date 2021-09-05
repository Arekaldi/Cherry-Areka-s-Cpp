#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1;

int ans1[maxn], sz[maxn], mk[maxn], fa[maxn];
int col[maxn];

int n, q, head[maxn], tot;

class Edge {
    public:
        int to, nxt;
};

Edge E[maxn];

inline void Add_edge(int u, int v) {
    E[++tot].to = v, E[tot].nxt = head[u];
    head[u] = tot;
}

inline void Dfs1(int x, int f) {
    ans1[x] = col[x], sz[x] = 1, mk[x] = 0;
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == f)
            continue;
        Dfs1(v, x);
        ans1[x] += ans1[v];
        sz[x] += sz[v];
    }
    return;
}

inline void PushDn(int x) {
    col[x] ^= 1;
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == fa[x])
            continue;
        PushDn(v);
    }
}

signed main() {
    n = read();
    for(int i = 2, x; i <= n; ++i)
        Add_edge(x = read(), i), Add_edge(i, x), fa[i] = x;
    
    for(int i = 1; i <= n; ++i)
        col[i] = read();
    
    Dfs1(1, 0);

    q = read();

    for(int i = 1, x; i <= q; ++i) {
        string ss;
        cin >> ss;
        if(ss == "get") {
            x = read();
            printf("%d\n", ans1[x]);
        }
        else {
            x = read();
            PushDn(x);
            Dfs1(1, 0);
        }
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
