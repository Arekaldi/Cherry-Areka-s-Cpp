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

int n, m;
class Edge {
    public:
        int to, nxt, val;
}E[maxm];

int tot, head[maxm];

inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w;
    head[u] = tot;
}

class Node {
    public :
        int v, val;
        Node(int a, int b) : v(a), val(b) {}
        friend bool operator < (const Node a, const Node b) {
            return a.val > b.val;
        }
};

priority_queue < Node, vector <Node> > Q;


const int maxn = 1e5 + 1;

int Fa[maxn];
vector <int> V[maxn];

int dis[maxn];
int p;
bool vis[maxn];

const int Inf = 0x7f7f7f7f;

inline void Dijkstra(int op) {

    memset(dis, 0x7f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    
    dis[op] = 0, Q.push(Node(op, 0));

    while(!Q.empty()) {
        Node x = Q.top();
        Q.pop();

        int u = x.v, w = x.val;

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

    for(int i = 1; i <= n; ++i)
        if(dis[i] != Inf)
            V[op].push_back(i);

    sort(V[op].begin(), V[op].end());

    return;
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("infusion.in", "r", stdin);
        freopen("infusion.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        Add_edge(x, y, 1);
    }

    for(int i = 1; i <= n; ++i)
        Dijkstra(i);

    int q = read();
    for(int i = 1; i <= q; ++i) {
        int x = read(), y = read();
        int w = lower_bound(V[x].begin(), V[x].end(), y) - V[x].begin();
        if(V[x][w] == y)
            puts("Alive");
        else
            puts("Dead");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
