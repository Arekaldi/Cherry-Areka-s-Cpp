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

int head[maxn], to[maxn], nxt[maxn], val[maxn],
    pre[maxn], dis[maxn], n, m, tot;
bool vis[maxn];

class Node {
    public:
        int x, dis;
        inline bool operator < (const Node &g) const {
            return g.dis < dis;
        }
        Node() {}
        Node(int a, int b) : x(a), dis(b) {}
};

priority_queue <Node> Q;

inline void Add_edge(int u, int v, int w) {
    to[++tot] = v, nxt[tot] = head[u], val[tot] = w;
    head[u] = tot;
}

inline void Dijkstra(int s) {
    memset(dis, 0x7f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    Q.push(Node(s, 0)), dis[s] = 0;
    while(!Q.empty()) {
        Node now = Q.top(); Q.pop();
        int x = now.x;
        if(vis[x])
            continue;
        vis[x] = true;
        for(int i = head[x]; i; i = nxt[i]) {
            int v = to[i];
            if(dis[v] > dis[x] + val[i]) {
                dis[v] = dis[x] + val[i];
                Q.push(Node(v, dis[v]));
                pre[v] = i;
            }
            else if(dis[v] == dis[x] + val[i] and val[i] < val[pre[v]])
                pre[v] = i;
        }
    }
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
        Add_edge(v, u, w);
    }

    int ss = read();
    Dijkstra(ss);
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        ans += val[pre[i]];
    printf("%lld\n", ans);
    pre[ss] = -1;
    sort(pre + 1, pre + n + 1);
    for(int i = 2; i <= n; ++i)
        printf("%lld ", pre[i] + 1 >> 1);
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
