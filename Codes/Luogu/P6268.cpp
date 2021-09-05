#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}


const int maxM = 1e6 + 10, maxn = 1010, Inf = 0x7ffffff;

struct edge {
    int to, val, next;
}E[maxM];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];


void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    memset(dis, -1, sizeof(dis));

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
        k = Dfs(s, INT_MAX, t);
        ans += k;
    }
    return ans;
}

int c[maxn];

inline void Color(int x) {
    if(head[x] == -1) return;
    Q.push(x), c[x] = 1;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i = head[u]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(c[v]) continue;
            if(c[u] == 1) c[v] = 2;
            else c[v] = 1;
            Q.push(v);
        }
    }
}

int his;

signed main() {
    memset(head, -1, sizeof(head));
    n = read(), m = read();

    for(int i = 1; i <= m; ++i) {
        int a = read(), b = read();
        Add_edge(a + 1, b + 1, 0), Add_edge(b + 1, a + 1, 0);
        // mb = max(mb, b + 1);
    }

    his = tot;

    for(int i = 1; i <= n; ++i)
        if(!c[i]) Color(i);

    s = 0, t = n + 1;

    for(int i = 1; i <= n; ++i) {
        if(c[i] == 2)
            Add_edge(i, t, 1), Add_edge(t, i, 0);
        else if(c[i] == 1)
            Add_edge(s, i, 1), Add_edge(i, s, 0);
    }

    for(int i = 0; i <= his; i += 2) {
        int u = E[i ^ 1].to, v = E[i].to;
        if(c[u] == 1)
            Add_edge(u, v, Inf), Add_edge(v, u, 0);
        else if(c[u] == 2)
            Add_edge(v, u, Inf), Add_edge(u, v, 0);
    }

    int ans = Dinic(s, t);

    // cout << ans << endl;

    cout << n - ans << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}