#warning 就一个if我就把这题切了
#warning 真就死活不写大括号呗

#include <bits/stdc++.h>

using namespace std;

#define mid (l + r >> 1)
#define ls (k << 1)
#define rs (k << 1) | 1

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int n, m, u, v, x, y, tot, res, a[maxn], b[maxn],
top[maxn], dep[maxn], fa[maxn], son[maxn],
sz[maxn], head[maxn], to[maxn], nxt[maxn];

char op;

inline int Len(int u, int v) {
    if(u == 0 or v == 0)
        return (u | v) ? 0 : -1;
    x = u, y = v;
    while(top[x] ^ top[y])
    (dep[top[x]] < dep[top[y]]) && (swap(x, y), 1),
    x = fa[top[x]];
    (dep[x] > dep[y]) && (swap(x, y), 1);
    return dep[u] + dep[v] - (dep[x] << 1);
}

inline void Dfs1(int x, int f) {
    sz[x] = 1, 
    dep[x] = dep[f] + 1,
    fa[x] = f;
    for(int y, i = head[x]; i; i = nxt[i])
    ((y = to[i]) ^ f) && (Dfs1(y, x), sz[x] += sz[y],
    (sz[y] > sz[son[x]]) && (son[x] = y));
}

inline void Dfs2(int x, int f) {
    (!top[x]) && (top[x] = x),
    top[son[x]] = top[x];
    for(int y, i = head[x]; i; i = nxt[i])
    ((y = to[i]) ^ f) && (Dfs2(y, x), 1);
}

inline void Cek(int k, int u, int v) {
    (Len(u, v) > Len(a[k], b[k])) &&
    (a[k] = u, b[k] = v);
}

inline void upd(int k) {
    a[k] = a[ls], b[k] = b[ls];
    Cek(k, a[ls], a[rs]);
    Cek(k, a[ls], b[rs]);
    Cek(k, a[rs], b[ls]);
    Cek(k, a[rs], b[rs]);
    Cek(k, b[ls], b[rs]);
}

inline void Build(int k, int l, int r) {
    (l == r) ? (a[k] = l, b[k] = 0) :
    (Build(ls, l, mid), Build(rs, mid + 1, r), upd(k), 0);
}

inline void Change(int k, int l, int r, int pos) {
    (l == r) ? (a[k] ^= l) :
    (((pos <= mid) ? Change(ls, l, mid, pos) :
    Change(rs, mid + 1, r, pos)), upd(k), 0);
}

inline void Add_edge(int u, int v) {
    to[++tot] = v,
    nxt[tot] = head[u],
    head[u] = tot;
}

signed main() {
    n = read();
    for(int i = 1; i < n; ++i) 
    (u = read(), 1) && (v = read(), 1) &&
    ((Add_edge(u, v), 1) && (Add_edge(v, u), 1));
    Dfs1(1, 0), Dfs2(1, 0),
    Build(1, 1, n), m = read();
    for(int i = 1; (i <= m) && (cin >> op, 1); ++i)
    (op ^ 'G') ? (u = read(), 1) &&
    (Change(1, 1, n, u), 1) :
    printf("%d\n", Len(a[1], b[1]));
    return 0;
}
