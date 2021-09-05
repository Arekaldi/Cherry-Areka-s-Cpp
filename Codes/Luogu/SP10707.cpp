#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int to[maxn], head[maxn], nxt[maxn], st[maxn],
    ed[maxn], son[maxn], sz[maxn], top[maxn],
    f[maxn], dep[maxn], tot, ind;
int col[maxn], pos[maxn], cnt[maxn], L[400],
    R[400], b[maxn], a[maxn], pd[maxn];
int n, m, k, t, ans;
bool vis[maxn];
double Sn;

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u],
    head[u] = tot;
}

inline void Dfs1(int x, int fa) {
    st[x] = ++ind, sz[x] = 1, f[x] = fa, dep[x] = dep[fa] + 1;
    for(int v, i = head[x]; i; i = nxt[i]) {
        if((v = to[i]) ^ fa) {
            Dfs1(v, x);
            sz[x] += sz[v];
            (sz[v] > sz[son[x]]) and (son[x] = v);
        }
    }
    ed[x] = ++ind;
}

inline void Dfs2(int x, int fa) {
    if(!top[x])
        top[x] = x;
    top[son[x]] = top[x];
    for(int v, i = head[x]; i; i = nxt[i])
        if((v = to[i]) ^ fa)
            Dfs2(v, x);
}

inline int Lca(int x, int y) {
    while(top[x] ^ top[y]) {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = f[top[x]];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    return x;
}

class Ask{
    public :
        int id, l, r, ual;
        int ans;
}Q[maxn];

inline bool Comp1(Ask a, Ask b) {
    if(pos[a.l] == pos[b.l])
        return a.r < b.r;
    else
        return pos[a.l] < pos[b.l];
}

inline bool Comp2(Ask a, Ask b) {
    return a.id < b.id;
}

inline void init() {
    int nn = n * 2;
    Sn = sqrt(nn);
    t = Sn;

    for(int i = 1; i <= t; ++i) 
        L[i] = (i - 1) * Sn + 1, R[i] = i * Sn;
        
    if(R[t] < nn) {
        ++t;
        L[t] = R[t - 1] + 1;
        R[t] = nn;
	}
    
    for(int i = 1; i <= t; ++i)
        for(int j = L[i]; j <= R[i]; ++j)
            pos[j] = i;
}

inline void Upd(int x)
{
	if(!(vis[pd[x]] ^= 1) && (--cnt[a[x]]) == 0)
		ans--;
	if(vis[pd[x]] && (cnt[a[x]]++) == 0)
		ans++;
}

signed main() {
	n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        col[i] = read(), b[i] = col[i];
    sort(b + 1, b + n + 1);
    int nn = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; ++i)
        col[i] = lower_bound(b + 1, b + nn + 1, col[i]) - b;

    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        Add_edge(u, v), Add_edge(v, u);
    }

    Dfs1(1, 0), Dfs2(1, 0);
    init();

    for(int i = 1; i <= n; ++i)
        a[st[i]] = a[ed[i]] = col[i],
        pd[st[i]] = pd[ed[i]] = i;

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        Q[i].id = i;
        int ll = Lca(u, v);
		if(u == ll or v == ll) {
            if(st[v] < st[u])
                swap(u, v);
            Q[i].l = st[u], Q[i].r = st[v], Q[i].ual = 0;
		}
		else {
			if(ed[v] < st[u])
                swap(u, v);
			Q[i].l = ed[u], Q[i].r = st[v], Q[i].ual = st[ll];
		}
    }

    // for(int i = 1; i <= ind; ++i)
    //     cout << a[i] << " ";
    // cout << endl;

    sort(Q + 1, Q + m + 1, Comp1);

    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i) {
        while(l > Q[i].l)
            Upd(--l);
        while(r < Q[i].r)
            Upd(++r);
        while(l < Q[i].l)
            Upd(l++);
        while(r > Q[i].r)
            Upd(r--);
        if(Q[i].ual)
            Upd(Q[i].ual);
        Q[i].ans = ans;
        if(Q[i].ual)
            Upd(Q[i].ual);
    }

    sort(Q + 1, Q + m + 1, Comp2);

    for(int i = 1; i <= m; ++i)
        printf("%d\n", Q[i].ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}