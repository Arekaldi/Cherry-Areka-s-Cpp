#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1;

int to[maxn], nxt[maxn], head[maxn], low[maxn],
    dfn[maxn], st[maxn], val[maxn], scc[maxn],
    sum[maxn], frm[maxn], f[maxn];
bool inq[maxn];
int n, m, cnt, tot, top, bot = 1, all_scc;

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u];
    head[u] = tot, frm[tot] = u;
}

inline void Tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    st[++top] = x, inq[x] = true;
    for(int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if(!dfn[v])
            Tarjan(v), low[x] = min(low[x], low[v]);
        else if(inq[v])
            low[x] = min(low[x], low[v]);
    }
    if(dfn[x] == low[x]) {
        all_scc++;
        while(st[top + 1] != x) {
            int z = st[top];
            scc[z] = all_scc;
            sum[all_scc] += val[z];
            inq[z] = false;
            top--;
        }
    }
}

int ans = 0;
inline void Dfs(int x) {
    if(f[x])
        return;
    f[x] = sum[x];
    int M = 0;
    for(int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if(!f[v])
            Dfs(v);
        M = max(M, f[v]);
    }
    f[x] += M;
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        val[i] = read();

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        Add_edge(u, v);
    }

    for(int i = 1; i <= n; ++i)
        if(!dfn[i])
            Tarjan(i);
    
    memset(head, 0, sizeof(head));
    tot = 0;

    for(int i = 1; i <= m; ++i) {
        int u = frm[i], v = to[i];
        if(scc[u] != scc[v])
            Add_edge(scc[u], scc[v]);
    }

    for(int i = 1; i <= all_scc; ++i)
        if(!f[i])
            Dfs(i), ans = max(ans, f[i]);
    
    printf("%d\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
