#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}


const int maxn = 1e5 + 1, maxm = 5e7 + 1, Inf = 0x7f7f7f7f;

struct edge {
    int to, val, next, cost;
}E[maxm];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];

void Add_edge(int u, int v, int w, int c) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u], E[tot].cost = c;
    head[u] = tot;
    swap(u, v);
    E[++tot].to = v, E[tot].val = 0, E[tot].next = head[u], E[tot].cost = -c;
    head[u] = tot;
}

deque <int> Q;
bool vis[maxn];
bool Inq[maxn];

bool Spfa(int s, int t) {
    memset(dis, 0x7f, sizeof(dis));
    
    Q.push_back(s); dis[s] = 0;
    Inq[s] = true;
    
    while(!Q.empty()) {
        int x = Q.front(); Q.pop_front();
        Inq[x] = false;
        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(dis[v] > dis[x] + E[i].cost and E[i].val) {
                dis[v] = dis[x] + E[i].cost;
                if(!Inq[v]) {
                    if(!Q.empty() and dis[v] < dis[Q.front()]) 
                        Q.push_front(v), Inq[v] = true;
                    else
                        Q.push_back(v), Inq[v] = true;
                }
            }
        }
    }
    
    return dis[t] < Inf;
}

int Dfs(int x, int flew, int t) {
    if(x == t) 
        return flew;
    vis[x] = true;
    
    int rest = flew;
    
    for(int i = cur[x]; i > -1 && rest; i = E[i].next) {
        int v = E[i].to, f = E[i].val;
        
        cur[x] = i;
        
        if(vis[v] or !f or dis[v] != dis[x] + E[i].cost) continue;
        
        int k = Dfs(v, min(rest, f), t);
        E[i].val -= k, E[i ^ 1].val += k;
        rest -= k;
        
        if(!k) dis[v] = 0;
    }
    
    vis[x] = false;
    return flew - rest;
}

int F, C;

inline void Dinic(int s, int t) {
    int k;
    while(Spfa(s, t)) {
        memcpy(cur, head, sizeof(head));
        k = Dfs(s, INT_MAX, t);
        C += dis[t] * k;
        F += k;
    }
}

const int Maxn = 1e2 + 1;

int c[Maxn][Maxn];

signed main() {
    memset(head, -1, sizeof(head));
    
    n = read();

    s = 0, t = 2 * n + n * n + 1;

    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) 
            c[i][j] = read();

    for(int i = 1; i <= n; ++i)
        Add_edge(s, i, 1, 0);
    for(int j = 1; j <= n; ++j) {
        int j2 = j + n * n + n;
        Add_edge(j2, t, 1, 0);
        for(int k = 1; k <= n; ++k) {
            int j1 = k + (j - 1) * n + n;
            Add_edge(j1, j2, Inf, 0);
            Add_edge(k, j1, Inf, c[k][j]);
        }
    }

    Dinic(s, t);

    cout << C << endl;

    memset(head, -1, sizeof(head));
    tot = -1;
    
    for(int i = 1; i <= n; ++i)
        Add_edge(s, i, 1, 0);
    for(int j = 1; j <= n; ++j) {
        int j2 = j + n * n + n;
        Add_edge(j2, t, 1, 0);
        for(int k = 1; k <= n; ++k) {
            int j1 = k + (j - 1) * n + n;
            Add_edge(j1, j2, Inf, 0);
            Add_edge(k, j1, Inf, -c[k][j]);
        }
    }

    C = 0;
    Dinic(s, t);
    cout << -C << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
