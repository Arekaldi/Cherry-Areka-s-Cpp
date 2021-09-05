#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int fa[maxn], sz[maxn], a[maxn], b[maxn];

int n, m, f, k;

inline int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

int vis[310][310];

signed main() {
    n = read(), m = read(), k = read(), f = read();
    for(int i = 1; i <= n; ++i)
        fa[i] = i;
    
    for(int i = 1; i <= m; ++i)
        a[i] = read(), b[i] = read();

    for(int i = 1; i <= f; ++i) {
        int a1 = read(), b1 = read();
        int fa1 = Find(a1), fb1 = Find(b1);
        if(fa1 == fb1)
            continue;
        fa[fa1] = fb1;
    }
    
    for(int i = 1; i <= m; ++i) {
        int u = a[i], v = b[i];
        int fu = Find(u);
        if(vis[fu][v])
            continue;
        vis[fu][v] = true;
        sz[fu]++;
    }

    int ans = (1 << 30);
    for(int i = 1; i <= n; ++i)
        ans = min(ans, sz[Find(i)]);

    printf("%d\n", min(ans + k, n));

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
