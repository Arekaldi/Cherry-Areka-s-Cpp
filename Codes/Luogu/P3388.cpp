#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e6 + 1;

int to[maxn], nxt[maxn], low[maxn], dfn[maxn], head[maxn];
int n, m, tot, cnt;

bool s[maxn];

inline void Tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    int ch = 0;
    for(int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if(!dfn[v]) {
            Tarjan(v, fa);
            low[x] = min(low[x], low[v]);
            if(low[v] >= dfn[x] and x != fa)
                s[x] = true;
            if(x == fa)
                ch++;
        }
        else
            low[x] = min(low[x], dfn[v]);
    }
    if(x == fa and ch >= 2)
        s[fa] = true;
}

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u];
    head[u] = tot;
}

vector <int> v;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        Add_edge(u, v);
        Add_edge(v, u);
    }
    
    for(int i = 1; i <= n; ++i)
        if(!dfn[i])
            Tarjan(i, i);

    for(int i = 1; i <= n; ++i)
        if(s[i])
            v.push_back(i);

    cout << v.size() << endl;
    for(int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
