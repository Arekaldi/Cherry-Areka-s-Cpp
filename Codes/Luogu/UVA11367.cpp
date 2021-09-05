#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e3 + 1, inf = 0x7f7f7f7f, maxm = 2e4 + 1;

class Node {
    public:
        int oil, c, now;
        Node() {}
        Node(int a, int b, int d) : oil(a), c(b), now(d) {}
        inline bool operator < (const Node &g) const {
            if(g.c == c) {
                if(g.now == now)
                    return g.oil > oil;
                else
                    return g.now > now;
            }
            else
                return g.c < c;
        }
};

priority_queue <Node> q;

int head[maxn], to[maxm], nxt[maxm], val[maxm], a[maxn],
    tot, n, m, Q;
bool vis[maxn][101];

inline void Add_edge(int u, int v, int w) {
    to[++tot] = v, nxt[tot] = head[u],
    val[tot] = w, head[u] = tot;
}

inline int Bfs(int s, int t, int Mx) {
    memset(vis, false, sizeof(vis));
    while(!q.empty())
        q.pop();
    q.push(Node(0, 0, s));
    while(!q.empty()) {
        Node x = q.top();
        q.pop();
        if(vis[x.now][x.oil])
            continue;
        vis[x.now][x.oil] = true;
        if(x.now == t)
            return x.c;
        for(int j = 1; j <= Mx - x.oil; ++j)
            q.push(Node(x.oil + j, x.c + j * a[x.now], x.now));
        for(int i = head[x.now]; i; i = nxt[i]) {
            int v = to[i];
            if(vis[v][x.oil - val[i]])
                continue;
            if(x.oil < val[i])
                continue;
            q.push(Node(x.oil - val[i], x.c, v));
        }
    }
    return inf;
}

signed main() {
    // freopen("1.txt", "r", stdin);
    // freopen("w.txt", "w", stdout);
    n = read(), m = read();
    for(int i = 0; i < n; ++i)
        a[i] = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
        Add_edge(v, u, w);
    }

    Q = read();
    for(int i = 1; i <= Q; ++i) {
        int c = read(), u = read(), v = read();
        int ans = Bfs(u, v, c);
        printf(ans == inf ? "impossible\n" : "%d\n", ans);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
