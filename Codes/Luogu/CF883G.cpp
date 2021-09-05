#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 6e5 + 1;

int n, m, s, res1, res2;
bool vis[maxn];
int tp[maxn];
queue <int> q;
int head[maxn], tot;
class Edge {
    public:
        int to, nxt, val;
};

Edge E[maxn];

inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w;
    head[u] = tot;
}

inline void Dfs(int x) {
    if(vis[x])
        return;
    vis[x] = true;
    for(int i = head[x]; i; i = E[i].nxt) {
        if(E[i].val == 2) {
            tp[i] = 1;
            return;
        }
        q.push(i), res1++;
    }
}

inline void Bfs()

signed main() {
    n = read(), m = read(), s = read();
    
    for(int i = 1; i <= m; ++i) {
        int t = read(), u = read(), v = read();
        Add_edge(u, v, t);
        if(t != 1)
            Add_edge(v, u, t);
    }
    
    Dfs(s);
    Bfs();

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
