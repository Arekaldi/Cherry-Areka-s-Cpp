#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

#define int long long

const int maxn = 1e6 + 1;
const int Inf = 0x7f7f7f7f;

class Edge {
    public:
        int to, nxt, val, cst;
};

int head[maxn], dis[maxn], tot = -1;
Edge E[maxn];

inline void Add_edge(int u, int v, int vl, int cst) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].cst = cst, E[tot].val = vl;
    head[u] = tot;
}

bool vis[maxn], inq[maxn];
int s, t, n;
queue <int> Q;

inline bool SPFA() {
    memset(dis, 0x7f, sizeof(dis));
    dis[s] = 0, Q.push(s);
    inq[s] = true;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inq[u] = false;

        for(int i = head[u]; i > -1; i = E[i].nxt) {
            int v = E[i].to;
            if(dis[v] > dis[u] + E[i].cst and E[i].val) {
                dis[v] = dis[u] + E[i].cst;
                if(!inq[v])
                    Q.push(v), inq[v] = true;
            }
        }
    }

    return dis[t] < Inf;
}

int cur[maxn];
inline int Dfs(int x, int flew) {
    if(x == t)
        return flew;
    
    vis[x] = true;

    int rest = flew;

    for(int i = cur[x]; i > -1 and rest; i = E[i].nxt) {
        int f = E[i].val, v = E[i].to;

        cur[x] = i;
        if(vis[v] or !f or dis[v] != dis[x] + E[i].cst or !rest)
            continue;
        
        int k = Dfs(v, min(E[i].val, rest));
        rest -= k, E[i].val -= k, E[i ^ 1].val += k;

        if(!k)
            dis[v] = -1;
    }
    vis[x] = false;

    return flew - rest;
}

bool flag;
int F, C;
inline void Cost_Current() {
    while(SPFA()) {
        memcpy(cur, head, sizeof(head));
        int k = Dfs(s, Inf);
        flag = (flag | k);
        F += k, C += dis[t] * k;
    }
}

int m[maxn], a[maxn], b[maxn], k[maxn];

signed main() {
    memset(head, -1, sizeof(head));

    n = read();
    s = 0, t = (n << 1) + 1;

    for(int i = 1; i <= n; ++i)
        Add_edge(s, i, 1, 0), Add_edge(i, s, 0, 0);
    
    for(int i = n + 1; i <= (n << 1); ++i)
        Add_edge(i, t, 1, 0), Add_edge(t, i, 0, 0);

    for(int i = 1; i <= n; ++i) {
        m[i] = read(), a[i] = read(), b[i] = read(), k[i] = read();
        for(int j = a[i]; j <= b[i]; ++j) {
            Add_edge(i, j + n, Inf, abs(j - m[i]) * k[i]);
            Add_edge(j + n, i, 0, -(abs(j - m[i]) * k[i]));
        }
    }

    Cost_Current();

    if(!flag or F != n)
        puts("NIE");
    else
        printf("%lld\n", C);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
