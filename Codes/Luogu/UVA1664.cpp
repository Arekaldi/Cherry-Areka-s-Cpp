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

const int maxn = 2e5 + 1;

int n, fa[maxn], sz[maxn], ans[maxn];

inline int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

class Edge {
    public:
        int frm, to, val;
        inline bool operator < (const Edge &g) const {
            return g.val < val;
        }
};

Edge E[maxn];

inline void init() {
    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
        sz[i] = 1;
        ans[i] = 0;
    }
}

signed main() {
    while(scanf("%lld", &n) != EOF) {
        init();
        
        for(int i = 1; i < n; ++i)
            E[i].frm = read(), E[i].to = read(), E[i].val = read();
        
        sort(E + 1, E + n);

        for(int i = 1; i < n; ++i) {
            int u = E[i].frm, v = E[i].to, val = E[i].val;
            int fu = Find(u), fv = Find(v);
            int a = ans[fu] + sz[fv] * val, b = ans[fv] + sz[fu] * val;
            if(a > b)
                fa[fv] = fu, sz[fu] += sz[fv], ans[fu] = a;
            else if(a == b) {
                if(sz[fv] >= sz[fu])
                    fa[fu] = fv, sz[fv] += sz[fu], ans[fv] = a;
                else
                    fa[fv] = fu, sz[fu] += sz[fv], ans[fu] = a;
            }
            else
                fa[fu] = fv, sz[fv] += sz[fu], ans[fv] = b;
        }

        printf("%lld\n", ans[Find(1)]);
    }
    
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
