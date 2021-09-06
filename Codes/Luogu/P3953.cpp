#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e6 + 1;

int n, m, tot, ans, k, p, dis[maxn], head[maxn];
bool vis[maxn];

class Node {
    public:
        int dis, x;
        inline bool operator < (const Node &g) const {
            return g.dis > dis;
        }
        Node() {}
        Node(int a, int b) : x(a), dis(b) {}
};

class Edge {
    public:
        int to, nxt, val;
        Edge() {}
        Edge(int u, int v, int w) : to(u), nxt(v), val(w) {}
};

Edge E[maxn];

inline void Add_edge(int u, int v, int w) {
    E[++tot] = Edge(v, head[u], w);
    head[u] = tot;
}

priority_queue <Node> Q;
inline void Dijkstra() {
    dis[1] = 0, Q.push(Node(1, 0));
    while(!Q.empty()) {
        int x = Q.top().x; Q.pop();
        if(vis[x])
            continue;
        for(int v, i = head[x]; i; i = E[i].nxt) {
            v = E[i].to;
            if(dis[v] > dis[x] + E[i].val) {
                if(v == n)
                    ans = 0;
                dis[v] = dis[x] + E[i].val;
                Q.push(Node(v, dis[v]));
            }
            if(v == n and dis[v] == dis[x] + E[i].val)
                ans = (ans + 1) % p;
        }
    }
}

signed main() {
    int T = read();
    while(T--) {
        memset(vis, false, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));
        ans = 0;
        n = read(), m = read(), k = read(), p = read();
        for(int i = 1; i <= m; ++i) {
            int u = read(), v = read(), w = read();
            Add_edge(u, v, w), Add_edge(v, u, w);
        }
        Dijkstra();
        printf("%d\n", ans);
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
