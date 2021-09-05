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

const int maxn = 1e6 + 1;

char id[maxn];
int n, top, tot, ans[maxn], sta[maxn], sum[maxn],
    fa[maxn], head[maxn];

class Edge {
    public:
        int to, nxt;
        Edge() {}
        Edge(int a, int b) : to(a), nxt(b) {}
};

Edge E[maxn];

inline void Add_edge(int u, int v) {
    E[++tot] = Edge(v, head[u]);
    head[u] = tot;
}

inline void Dfs(int x, int ff) {
    int g = 0;
    if(id[x] == ')' and top > 0)
        ans[x] = ans[fa[(g = sta[top--])]] + 1;
    else if(id[x] == '(')
        sta[++top] = x;
    sum[x] = sum[fa[x]] + ans[x];
    for(int v, i = head[x]; i; i = E[i].nxt) {
        if((v = E[i].to) ^ ff)
            Dfs(v, x);
    }
    if(id[x] == ')' and g != 0)
        sta[++top] = g;
    else if(id[x] == '(')
        top--;
}

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        cin >> id[i];
    for(int i = 2; i <= n; ++i)
        fa[i] = read(), Add_edge(fa[i], i), Add_edge(i, fa[i]);
    Dfs(1, 0);

    int res = 0;
    for(int i = 2; i <= n; ++i)
        res ^= (i * sum[i]);
    
    printf("%lld\n", res);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
