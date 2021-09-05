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

const int MAXN = 1e4 + 10, MAXM = 1e6 + 10, Mod = 9987;

struct Node {
    int d, dx, dy;
    Node(int x, int y, int z) : d(x), dx(y), dy(z) {}
    friend bool operator < (const Node a, const Node b) {
        return a.dx == b.dx ? a.dy > b.dy : a.dx > b.dx;
    }
};

struct Edge {
    int to, nxt, val;
}E[MAXM];

int head[MAXN], tot;

void Add_edge(int u, int v, int w) {
    E[++tot].to = v;
    E[tot].nxt = head[u];
    head[u] = tot;
    E[tot].val = w;
}

priority_queue <Node, vector <Node> > Q;


bool vis[MAXN];

pair <int, int> dis[MAXN];

bool Comp(pair <int, int> a, pair <int, int> b) {
    return a.first == b.first ? a.second < b.second : a.first < b.first;
}

int n, m;

void Bfs() {
    dis[1].first = 0, dis[1].second = 1;

    Q.push(Node(1, 0, 1));

    while(!Q.empty()) {
        Node x = Q.top(); Q.pop();
        int u = x.d, ux = x.dx, uy = x.dy;
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = head[u]; i; i = E[i].nxt) {
            int y = E[i].to;
            dis[0].first = (dis[u].second * E[i].val) >= Mod ? (dis[u].first + 1) : (dis[u].first);
            dis[0].second = (dis[0].first == dis[u].first) ? (dis[u].second * E[i].val) : (dis[u].second % Mod);
            if(dis[0].second == 0) dis[0].second = 1ll;
            if(Comp(dis[0], dis[y])) {
                dis[y] = dis[0];
                Q.push(Node(y, dis[y].first, dis[y].second));
            }
        }
    }
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
    }

    for(int i = 1; i <= n; ++i) dis[i].first = dis[i].second = INT_MAX;
    
    Bfs();

    cout << dis[n].second << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
