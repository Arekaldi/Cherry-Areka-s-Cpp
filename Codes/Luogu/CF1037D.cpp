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

int to[maxn], nxt[maxn], dfn[maxn], head[maxn], low[maxn],
    a[maxn];
int n, m, tot, cnt;
bool vis[maxn];

queue <int> q;
vector <int> v;
map <int, int> M;

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u];
    head[u] = tot;
}

inline bool Comp(int u, int v) {
    return dfn[u] < dfn[v];
}
//sds

inline void Bfs() {
    q.push(1);
    while(!q.empty()) {
        int x = q.front(); q.pop();
        low[x] = ++cnt;
        vis[x] = true;
        v.clear();

        for(int i = head[x]; i; i = nxt[i]) {
            int vs = to[i];
            if(vis[vs])
                continue;
            v.push_back(vs);
        }

        if(v.empty())
            continue;

        sort(v.begin(), v.end(), Comp);

        for(int i = 0; i < v.size(); ++i)
            q.push(v[i]);
    }
}

signed main() {
    n = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v), Add_edge(v, u);
    }

    for(int i = 1; i <= n; ++i)
        a[i] = read(), M[a[i]] = i;
    
    for(int i = 1; i <= n; ++i)
        dfn[i] = M[i];

    Bfs();

    for(int i = 1; i <= n; ++i) {
        if(dfn[i] != low[i]) {
            puts("No");
            goto Areka;
        }
    }
    
    puts("Yes");
    
    Areka:;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
