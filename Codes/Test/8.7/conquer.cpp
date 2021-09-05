#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1, maxl = 1e3 + 1;

int n, tot, to[maxn], nxt[maxn], val[maxn],
head[maxn], t[maxn],s[maxn], sz[maxn],
ht[maxn], d[maxn], ans[maxn];

inline void Dfs(int x, int f) {
    sz[x] = 1;
    for(int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if(v == f)
            continue;
        t[val[i]]++;
        Dfs(v, x);
        sz[x] += sz[v];
    }
    if(sz[x] == 1) {
        ans[x] = 0;
        return;
    }
    for(int i = 1; i <= maxl; ++i) {
        s[i] = s[i - 1] + t[i];
        ht[i] = ht[i - 1] + s[i];
    }
    if(d[x] > ht[1000])
        ans[x] = 1000 + (d[x] - ht[1000]) / s[1000];
    else {
        int l = 1, r = 1000;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(ht[mid] < d[x])
                l = mid + 1;
            else if(ht[mid] > d[x])
                r = mid - 1;
            else {
                ans[x] = mid;
                break;
            }
        }
        if(!ans[x])
            ans[x] = l;
    }
}

inline void Add_edge(int u, int v, int w) {
    to[++tot] = v, nxt[tot] = head[u], val[tot] = w;
    head[u] = tot;
}

signed main() {
    #define Areka
    #ifdef Areka
        freopen("conquer.in", "r", stdin);
        freopen("conquer.out", "w", stdout);
    #endif
    n = read();
    for(int i = 1; i <= n; ++i)
        d[i] = read();
    
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w), Add_edge(v, u, w);
    }

    Dfs(1, 0);

    int res = -1;
    for(int i = 1; i <= n; ++i)
        res = max(res, ans[i]);
    printf("%d\n", res);
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
