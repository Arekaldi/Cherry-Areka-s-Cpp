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

const int Inf = 0x7fffffff, maxn = 6010, maxm = 10000010;

struct edge {
    int to, val, next;
}E[maxm];

int n, m, p, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxm];


void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    for(int i = t; i <= s; ++i) dis[i] = -1;

    while(!Q.empty()) Q.pop();

    Q.push(s); dis[s] = 1;

    while(!Q.empty()) {
        int x = Q.front(); Q.pop();

        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(dis[v] == -1 and E[i].val) {
                dis[v] = dis[x] + 1;
                Q.push(v);
            }
        }
    }

    return dis[t] != -1;
}

int Dfs(int x, int flew, int t) {
    if(x == t) return flew;

    int rest = flew;

    for(int i = cur[x]; i > -1 && rest; i = E[i].next) {
        int v = E[i].to, f = E[i].val;

        cur[x] = i;

        if(!f or dis[v] != dis[x] + 1) continue;

        int k = Dfs(v, min(rest, f), t);
        E[i].val -= k, E[i ^ 1].val += k;
        rest -= k;

        if(!k) dis[v] = 0;
    }
    return flew - rest;
}

int Dinic(int s, int t) {
    int ans = 0, k;
    while(Bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        while(k = Dfs(s, INT_MAX, t))
            ans += k;
    }
    return ans;
}

bool vis[maxn];

signed main() {
    memset(head, -1, sizeof(head));
    p = read(), m = read(), n = read();

    t = 1, s = p + p + 1;
    for(int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        Add_edge(x + p, y, Inf), Add_edge(y, x + p, 0);
        Add_edge(y + p, x, Inf), Add_edge(x, y + p, 0);
    }
    for(int i = 1; i <= n; ++i) {
        int y = read();
        vis[y] = 1;
        Add_edge(s, y, Inf), Add_edge(y, s, 0);
    }

    for(int i = 1; i <= p; ++i) {
        if(!vis[i]) Add_edge(i, i + p, 1), Add_edge(i + p, i, 0);
        else Add_edge(i, i + p, Inf), Add_edge(i + p, i, 0);
    }

    cout << Dinic(s, t) << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif


    return 0;
}
