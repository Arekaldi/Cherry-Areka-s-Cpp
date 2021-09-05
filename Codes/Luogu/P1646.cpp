#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int Inf = 0x7fffffff;
const int maxn = 1000001, maxm = 9000001;

struct Edge {
    int to, val, next;
}E[maxm];

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];
int n, m, s, t;

void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    memset(dis, 0, sizeof(dis));

    Q.push(s); dis[s] = 1;

    while(!Q.empty()) {
        int x = Q.front(); Q.pop();
        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(!dis[v] and E[i].val) {
                dis[v] = dis[x] + 1;
                Q.push(v);
            }
        }
    }

    return dis[t];
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

int sci[101][101], dem[101][101];
int cnt, sum;

signed main() {
    n = read(), m = read();
    memset(head, -1, sizeof(head));

    s = 0, t = n * m * 6 + 1;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int x = read();
            sum += x;
            dem[i][j] = ++cnt;
            Add_edge(s, cnt, x), Add_edge(cnt, s, 0);
        }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int x = read();
            sum += x;
            sci[i][j] = ++cnt;
            Add_edge(cnt, t, x), Add_edge(t, cnt, 0);
        }

    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int x = read();
            sum += x;
            int nep = ++cnt;
            Add_edge(nep, dem[i][j], Inf), Add_edge(dem[i][j], nep, 0);
            Add_edge(nep, dem[i + 1][j], Inf), Add_edge(dem[i + 1][j], nep, 0);
            Add_edge(s, nep, x), Add_edge(nep, s, 0);
        }
    }

    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int x = read();
            sum += x;
            int nep = ++cnt;
            Add_edge(nep, sci[i][j], 0), Add_edge(sci[i][j], nep, Inf);
            Add_edge(nep, sci[i + 1][j], 0), Add_edge(sci[i + 1][j], nep, Inf);
            Add_edge(nep, t, x), Add_edge(t, nep, 0);
        }
    }

    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < m; ++j) {
            int x = read();
            sum += x;
            int nep = ++cnt;
            Add_edge(nep, dem[i][j], Inf), Add_edge(dem[i][j], nep, 0);
            Add_edge(nep, dem[i][j + 1], Inf), Add_edge(dem[i][j + 1], nep, 0);
            Add_edge(s, nep, x), Add_edge(nep, s, 0);
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < m; ++j) {
            int x = read();
            sum += x;
            int nep = ++cnt;
            Add_edge(nep, sci[i][j], 0), Add_edge(sci[i][j], nep, Inf);
            Add_edge(nep, sci[i][j + 1], 0), Add_edge(sci[i][j + 1], nep, Inf);
            Add_edge(nep, t, x), Add_edge(t, nep, 0);
        }
    }
    
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            Add_edge(dem[i][j], sci[i][j], Inf), Add_edge(sci[i][j], dem[i][j], 0);

    int ans = Dinic(s, t);
    cout << sum - ans << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif

    return 0;
}