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

const int maxn = 3e5 + 1;

int n, m, q;

class SegMent {
    private:
        class Tree {
            public:
                int l, r;
                long long sum;
                long long ad;
        };
        Tree T[maxn * 15];

        inline void Upd(int p) {
            T[p].sum = (T[p << 1].sum + T[(p << 1) | 1].sum);
        }

        inline void Pushdown(int p) {
            int l = p << 1, r = (p << 1) | 1;
            int d = T[p].ad;
            if(T[p].l == T[p].r) {
                T[p].ad = 0;
                return;
            }
            if(T[p].ad and T[p].l != T[p].r) {
                T[l].sum += (T[l].r - T[l].l + 1) * d, T[l].ad += d;
                T[r].sum += (T[r].r - T[r].l + 1) * d, T[r].ad += d;
                T[p].ad = 0;
                Upd(p);
            }
            return;
        }
    public:
        inline void Build(int p, int l, int r) {
            T[p].l = l, T[p].r = r;
            if(l == r) {
                T[p].sum = 0;
                return;
            }
            int mid = (l + r) >> 1;
            Build(p << 1, l, mid);
            Build((p << 1) | 1, mid + 1, r);
            Upd(p);
            return;
        }

        inline void Change(int p, int l, int r, int v) {
            Pushdown(p);
            if(l <= T[p].l and r >= T[p].r) {
                T[p].ad += v, T[p].sum += (T[p].r - T[p].l + 1) * v;
                return;
            }
            int mid = (T[p].l + T[p].r) >> 1;
            if(l <= mid)
                Change(p << 1, l, r, v);
            if(r > mid)
                Change((p << 1) | 1, l, r, v);
            Upd(p);
            return;
        }

        inline long long Ask(int p, int l, int r) {
            Pushdown(p);
            if(T[p].l >= l and T[p].r <= r)
                return T[p].sum;

            int mid = (T[p].l + T[p].r) >> 1;
            int res = 0;

            if(l <= mid) {
                res = res + Ask(p << 1, l, r);
            }
            if(r > mid) {
                res = res + Ask((p << 1) | 1, l, r);
            }
            return res;
        }
};

SegMent S;


class Point {
    public:
        int l, r, w;
};
Point a[maxn];

class Node {
    public:
        int l, r, id, type;
};

vector <Node> v[maxn];

long long ans[maxn];

class Edge {
    public:
        int to, nxt;
};

Edge E[maxn];
int head[maxn], tot, cnt;
inline void Add_edge(int u, int v) {
    E[++tot].to = v, E[tot].nxt = head[u];
    head[u] = tot;
}

int fa[maxn][25], dep[maxn];

inline void Dfs1(int x, int f) {
    fa[x][0] = f;
    dep[x] = dep[f] + 1;
    for(int i = 1; i < 25; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == f)
            continue;
        Dfs1(v, x);
    }
    return;
}

inline int Getl(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 24; i >= 0; --i) {
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    }
    if(x == y) return x;
    for(int i = 24; i >= 0; --i) {
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}

inline void Dfs2(int x, int f) {
    int l = a[x].l, r = a[x].r, w = a[x].w;
    S.Change(1, l, r, w);
    for(int i = 0; i < v[x].size(); ++i) {
        int id = v[x][i].id;
        int ll = v[x][i].l, rr = v[x][i].r;
        ans[id] += S.Ask(1, ll, rr) * v[x][i].type;
    }
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == f)
            continue;
        Dfs2(v, x);
    }
    S.Change(1, l, r, -w);
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();
    
    S.Build(1, 1, m);

    for(int i = 0; i < 25; ++i)
        fa[1][i] = 0;

    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v), Add_edge(v, u);
    }

    Dfs1(1, 0);

    for(int i = 1; i <= n; ++i)
        a[i].l = read(), a[i].r = read(), a[i].w = read();
    
    for(int i = 1; i <= q; ++i) {
        int u = read(), vs = read(), l = read(), r = read();
        int ff = Getl(u, vs), fff = fa[ff][0];
        Node vv;
        vv.id = i, vv.l = l, vv.r = r;
        vv.type = 1;
        v[u].push_back(vv), v[vs].push_back(vv);
        vv.type = -1;
        v[ff].push_back(vv), v[fff].push_back(vv);
    }

    Dfs2(1, 0);

    for(int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
