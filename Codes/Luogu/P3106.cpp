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

int to[3][maxn], nxt[3][maxn], val[3][maxn], head[3][maxn],
    dis[3][maxn], frm[3][maxn], n, m, tot[3];
bool vis[3][maxn];

inline void Add_edge(int u, int v, int w, int opt) {
    to[opt][++tot[opt]] = v, nxt[opt][tot[opt]] = head[opt][u],
    val[opt][tot[opt]] = w, frm[opt][tot[opt]] = u, head[opt][u] = tot[opt];
}

class Node {
    public:
        int x, dis;
        Node() {}
        Node(int a, int b) : x(a), dis(b) {}
        inline bool operator < (const Node &g) const {
            return g.dis < dis;
        }
};

priority_queue <Node> Q;

inline void Dijkstra(int k) {
    Q.push(Node(n, 0));
    memset(dis[k], 0x7f, sizeof(dis[k]));
    memset(vis[k], false, sizeof(vis[k]));
    dis[k][n] = 0;
    while(!Q.empty()) {
        Node now = Q.top();
        Q.pop();
        int x = now.x;
        if(vis[k][x])
            continue;
        vis[k][x] = true;
        for(int i = head[k][x]; i; i = nxt[k][i]) {
            int v = to[k][i];
            if(dis[k][v] > dis[k][x] + val[k][i]) {
                dis[k][v] = dis[k][x] + val[k][i];
                Q.push(Node(v, dis[k][v]));
            }
        }
    }
    // for(int i = 1; i <= n; ++i)
    //     cout << dis[k][i] << " ";
    // cout << endl;
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), p = read(), q = read();
        swap(u, v);
        Add_edge(u, v, p, 1);
        Add_edge(u, v, q, 2);
    }

    Dijkstra(1), Dijkstra(2);

    for(int i = 1; i <= m; ++i) {
        int num = 0;
        if(dis[1][to[1][i]] != dis[1][frm[1][i]] + val[1][i])
            num++;
        if(dis[2][to[2][i]] != dis[2][frm[2][i]] + val[2][i])
            num++;
        Add_edge(frm[2][i], to[2][i], num, 0);
    }
    Dijkstra(0);
    printf("%lld\n", dis[0][1]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
