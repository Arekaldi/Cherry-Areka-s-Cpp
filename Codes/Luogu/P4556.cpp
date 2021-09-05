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


int tot = 0;
int Rt[maxn];
class Tree {
    public:
        int sum, mx, idp;
        int ls, rs;
};
Tree T[maxn * 17];

class SegMentTree {
    private:

        inline void Pushup(int p) {
            T[p].sum = T[T[p].ls].sum + T[T[p].rs].sum;
            T[p].mx = max(T[T[p].ls].mx, T[T[p].rs].mx);
            if(T[p].mx == T[T[p].ls].mx)
                T[p].idp = T[T[p].ls].idp;
            else
                T[p].idp = T[T[p].rs].idp;
            return;
        }

    public:

        inline int Merge(int a, int b, int l, int r) {
            if(a == 0 or b == 0)
                return a | b;
            if(l == r) {
                T[a].sum += T[b].sum;
                T[a].mx += T[b].mx;
                T[a].idp = l;
                return a;
            }
            int mid = (l + r) >> 1;
            T[a].ls = Merge(T[a].ls, T[b].ls, l, mid);
            T[a].rs = Merge(T[a].rs, T[b].rs, mid + 1, r);
            Pushup(a);
            return a;
        }

        inline int Change(int p, int l, int r, int pos, int v) {
            if(p == 0)
                p = ++tot;
            if(l == r and l == pos) {
                T[p].sum += v;
                T[p].mx += v;
                T[p].idp = pos;
                return p;
            }
            int mid = (l + r) >> 1;
            if(pos <= mid)
                T[p].ls = Change(T[p].ls, l, mid, pos, v);
            if(pos > mid)
                T[p].rs = Change(T[p].rs, mid + 1, r, pos, v);
            Pushup(p);
            return p;
        }

        inline pair <int, int> Ask(int p) {
            return make_pair(T[p].idp, T[p].mx);
        }
};

SegMentTree S;

int n, m;

class Edge {
    public:
        int to, nxt;
};

Edge E[maxn];
int head[maxn], cnt;
inline void Add_edge(int u, int v) {
    E[++cnt].to = v, E[cnt].nxt = head[u];
    head[u] = cnt;
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

vector < pair<int, int> > kl[maxn];
int ans[maxn];

inline void Dfs2(int x, int f) {
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == f)
            continue;
        Dfs2(v, x);
        Rt[x] = S.Merge(Rt[x], Rt[v], 1, maxn);
    }
    
    for(int i = 0; i < kl[x].size(); ++i) {
        int u = kl[x][i].first, v = kl[x][i].second;
        Rt[x] = S.Change(Rt[x], 1, maxn, u, v);
    }

    pair <int, int> tt = S.Ask(Rt[x]);
    ans[x] = (tt.second == 0) ? 0 : tt.first;
    return;
}

signed main() {

    n = read(), m = read();

    for(int i = 0; i < 25; ++i)
        fa[1][i] = 0;

    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v), Add_edge(v, u);
    }

    Dfs1(1, 0);

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), z = read();
        int ff = Getl(u, v), fff = fa[ff][0];
        kl[u].push_back(make_pair(z, 1));
        kl[v].push_back(make_pair(z, 1));
        kl[ff].push_back(make_pair(z, -1));
        kl[fff].push_back(make_pair(z, -1));
    }

    Dfs2(1, 0);

    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
