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

const int maxn = 1e6 + 1;

int n, tot, to[maxn], nxt[maxn], head[maxn];
class Node {
    public:
        int c, d;
        inline bool operator < (const Node &g) const {
            return g.c == c ? g.d > d : g.c > c;
        }
};

Node a[maxn];

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u];
    head[u] = tot;
}

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i].d = read();
    for(int i = 1; i <= n; ++i)
        a[i].c = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v);
        Add_edge(v, u);
    }
    sort(a + 1, a + n + 1);
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i].d > 0)
            res += a[i].d;
        for(int j = head[i]; j; j = nxt[j]) {
            int v = to[j];
            a[v].d -= a[i].c;
        }
    }
    
    printf("%lld\n", res);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
