#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 1e6 + 1;

class Node {
    public :
        int v, val;
        Node(int a, int b) : v(a), val(b) {}
        friend bool operator < (const Node a, const Node b) {
            return a.val > b.val;
        }
};

priority_queue < Node, vector <Node> > Q;

int head[maxm], tot;
class Edge {
    public :
        int to, val, nxt;
};

Edge E[maxm];

inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w;
    head[u] = tot;
}

int n, p;
int dis[maxm];
bool vis[maxm];

inline void Dijkstra() {
    memset(dis, 0x7f, sizeof(dis));
    
    dis[1] = 0, Q.push(Node(1, 0));

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

    return;
}

signed main() {
    n = read();
    
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) {
            int w = read();
            Add_edge(i, j, w);
        }

    int p = read();

    for(int i = 1; i <= p; ++i) {
        int x = read();
        // vis[x] = true;
    }

    // for(int i = 1; i <= n; ++i)
    //     vis[i] = !vis[i];

    // for(int i = 1; i <= n; ++i)
    //     cout << vis[i] << endl;

    Dijkstra();

    printf("%d\n", dis[n]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
