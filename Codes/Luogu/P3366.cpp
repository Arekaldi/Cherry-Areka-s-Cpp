#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 4e5 + 1;
const int maxn = 5e3 + 1;

class Edge {
    public:
        int to, nxt, val, from;
        inline bool operator < (const Edge &a) const {
            return a.val > val;
        }
};

Edge E[maxm];
int head[maxn], tot, n, m;

inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u],
    E[tot].val = w, E[tot].from = u;
    head[u] = tot;
}

int fa[maxn], cnt = 1;

inline int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

signed main() {
    n = read(), m = read();
    
    for(int i = 1; i <= n; ++i)
        fa[i] = i;

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
    }

    sort(E + 1, E + tot + 1);

    int res = 0;
    for(int i = 1; i <= tot; ++i) {
        int u = E[i].from, v = E[i].to;
        int fu = Find(u), fv = Find(v);
        if(fu == fv)
            continue;
        res += E[i].val;
        fa[fv] = fu;
        if(++cnt == n)
            break;
    }

    if(cnt != n)
        puts("orz");
    else
        printf("%d\n", res);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
