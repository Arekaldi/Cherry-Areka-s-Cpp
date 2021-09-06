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

const int maxn = 5e6 + 1;

int head[maxn], cur[maxn], to[maxn], nxt[maxn],
    val[maxn], dep[maxn];
int n, m, s, t, tot = -1;

queue <int> q;
inline bool Bfs(int s, int t) {
    q.push(s);
    memset(dep, 0, sizeof(dep));
    dep[s] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = head[x]; i > -1; i = nxt[i]) {
            int v = to[i];
            if(val[i] and !dep[v]) {
                dep[v] = dep[x] + 1;
                q.push(v);
            }
        }
    }
    return dep[t];
}

inline int Dfs(int x, int vals, int t) {
    if(x == t)
        return vals;
    int rest = vals;
    for(int i = cur[x]; i > -1 and rest; i = nxt[i]) {
        cur[x] = i;
        int v = to[i];
        if(!val[i] or !rest or dep[v] != dep[x] + 1)
            continue;
        int k = Dfs(v, min(val[i], rest), t);
        val[i] -= k, val[i ^ 1] += k, rest -= k;
    }
    if(rest)
        dep[x] = 0;
    return vals - rest;
}


inline int Dinic() {
    int ans = 0;
    while(Bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        int k;
        while(k = Dfs(s, LLONG_MAX, t))
            ans += k;
    }
    return ans;
}

inline void Add_edge(int u, int v, int w) {
    to[++tot] = v, nxt[tot] = head[u], val[tot] = w;
    head[u] = tot;
}

signed main() {
    memset(head, -1, sizeof(head));

    n = read(), m = read(), s = read(), t = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w);
        Add_edge(v, u, 0);
    }

    cout << Dinic();
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}