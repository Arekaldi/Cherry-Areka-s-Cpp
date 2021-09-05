#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

class Edge {
    public :
        int to, nxt, val;
        inline void Add(Edge &H, int a, int &b, int c, int d) {
            H.to = a, H.nxt = b, H.val = c;
            b = d;
            return;
        }
};

class Node {
    public :
        int to, val;
        Node(int a, int b) : to(a), val(b) {}
        inline bool operator < (const Node &a) const {
            return val > a.val;
        }
};

Edge E[maxn];

int tot, head[maxn];
inline void Add_edge(int u, int v, int w) {
    E[++tot].Add(E[tot], v, head[u], w, tot);
}

priority_queue < Node > Q;

int dis[maxn];
bool vis[maxn];

int n, m, s, t;

inline int Dijkstra(int s, int t) {

    // memset(dis, 0x7f, sizeof(dis));
    for(int i = 1; i <= n; ++i)
        dis[i] = (1 << 30);
    dis[s] = 0, Q.push(Node(s, dis[s]));

    while(!Q.empty()) {
        Node now = Q.top();
        Q.pop();
        int u = now.to;
        if(vis[u])
            continue;
        vis[u] = true;
        
        for(int i = head[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(dis[v] > dis[u] + E[i].val) {
                dis[v] = dis[u] + E[i].val;
                Q.push(Node(v, dis[v]));
            }
        }
    }

    return dis[t];
}


signed main() {
    n = read(), m = read(), s = read(), t = read();

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
        Add_edge(v, u, w);
    }
    
    printf("%d\n", Dijkstra(s, t));
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
