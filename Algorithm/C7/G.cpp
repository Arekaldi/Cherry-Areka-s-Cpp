#include <bits/stdc++.h>

using namespace std;

#define int long long

int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e6 + 1;

int n, m;

class Edge {
    public:
        int to, nxt, val, frm;
        inline bool operator < (const Edge &a) const {
            return a.val > val;
        }
}E[maxn];

int head[maxn], tot;
inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w,
    E[tot].frm = u;
    head[u] = tot;
}

int fa[maxn];

inline int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n + 1; ++i)
        fa[i] = i;
    int cnt = 1, ans = 0;

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w), Add_edge(v, u, w);
    }
    
    sort(E + 1, E + tot + 1);

    for(int i = 1; i <= tot; ++i) {
        int u = E[i].to, v = E[i].frm;
        int fu = Find(u), fv = Find(v);
        if(fv != fu) {
            fa[fu] = fv;
            ans += E[i].val;
            cnt++;
            if(cnt == n + 1)
                break;
        }
    }

    cout << ans;
    
    return 0;
}