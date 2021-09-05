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
int cur[maxn], g[maxn];
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

signed main() {
    n = read(), m = read();
    memset(head, -1, sizeof(head));

    

    #ifndef ONLINE_JUDGE
        getchar();
    #endif

    return 0;
}