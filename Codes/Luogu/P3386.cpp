#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

int cur[maxn], head[maxn], to[maxn], nxt[maxn],
    val[maxn], dep[maxn];
int n, m, s, t, e, tot = -1;

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
        int v = to[i];
        cur[x] = i;
        if(!val[i] or !rest or dep[v] != dep[x] + 1)
            continue;
        int k = Dfs(v, min(val[i], rest), t);
        val[i] -= k, rest -= k, val[i ^ 1] += k;
    }

    if(rest)
        dep[x] = 0;
    
    return vals - rest;
}

inline void Add_edge(int u, int v, int w) {
    val[++tot] = w, to[tot] = v, nxt[tot] = head[u];
    head[u] = tot;
}

inline int Dinic() {
    int ans = 0;
    while(Bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ans += Dfs(s, (1 << 30), t);
    }
    return ans;
}

signed main() {
    memset(head, -1, sizeof(head));
    n = read(), m = read(), e = read();
    s = 0, t = n + m + 1;
    for(int i = 1; i <= e; ++i) {
        int u = read(), v = read() + n;
        Add_edge(u, v, 1);
		Add_edge(v, u, 0);
    }

    for(int i = 1; i <= n; ++i)
        Add_edge(s, i, 1), Add_edge(i, s, 0);
    for(int i = n + 1; i <= n + m; ++i)
        Add_edge(i, t, 1), Add_edge(t, i, 0);

    int ans = Dinic();
    cout << ans;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
