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

int n, m, tot;
int nxt[maxn], val[maxn], head[maxn], to[maxn],
    sz[maxn], dep[maxn], ask[maxn], f[maxn],
    ch[maxn], top[maxn], son[maxn], deps[maxn],
    fas[maxn];
bool vis[maxn];

inline void Add_edge(int u, int v, int w) {
    to[++tot] = v, val[tot] = w, nxt[tot] = head[u];
    head[u] = tot;
}

class Node {
    public:
        int id, pre, nxt;
};

Node a[maxn];

int cnt;
bool flag;
inline void ChenLian(int x, int fa) {
    a[x].pre = fa;
    if(x == n)
        a[fa].nxt = x, flag = true;
    if(flag)
        return;

    for(int v, i = head[x]; i; i = nxt[i]) {
        if((v = to[i]) ^ fa) {
            ChenLian(v, x);
            if(a[v].nxt)
                a[x].nxt = v;
        }
    }
    return;
}

inline void Dfs1(int x, int fa) {
    sz[x] = 1;
    deps[x] = deps[fa] + 1;
    fas[x] = fa;
    for(int v, i = head[x]; i; i = nxt[i]) {
        if((v = to[i]) ^ fa) {
            dep[v] = dep[x] + val[i];
            Dfs1(v, x);
            sz[x] += sz[v];
            (sz[v] > sz[son[x]]) and (son[x] = v);
        }
    }
}

inline void Dfs2(int x, int fa) {
    if(!top[x])
        top[x] = x;
    top[son[x]] = top[x];
    for(int v, i = head[x]; i; i = nxt[i]) {
        if((v = to[i]) ^ fa)
            Dfs2(v, x);
    }
}

inline int Lca(int x, int y) {
    while(top[x] ^ top[y]) {
        if(deps[top[x]] < deps[top[y]])
            swap(x, y);
        x = fas[top[x]];
    }
    if(deps[x] > deps[y])
        swap(x, y);
    return x;
}

inline int calc(int x, int y, int d) {
    if(deps[x] > deps[y])
        swap(x, y);
    if(deps[x] == deps[y]) {
        if(vis[x])
            swap(x, y);
    }
    int ll = Lca(y, n);
    int ss = dep[y] + dep[n] - (dep[ll] << 1);
    // cout << dep[x] << " " << x << " " << y << " " << n << " " << ss << endl;
    return ss + d + dep[x];
}

signed main() {
    n = read(), m = read();
    for(int u, v, w, i = 1; i < n; ++i) {
        u = read(), v = read(), w = read();
        Add_edge(u, v, w), Add_edge(v, u, w);
    }
    

    a[0].nxt = 1, a[n].nxt = -1;
    ChenLian(1, 0);
    Dfs1(1, 0);
    Dfs2(1, 0);

    bool is_chuans = false;
    for(int i = 1; i > -1; i = a[i].nxt) {
        int nt = a[i].nxt;
        f[i] = sz[i] - sz[nt] - 1;
        vis[i] = true;
        if(f[i] > 1)
            is_chuans = true;
        else {
            for(int j = head[i]; j; j = nxt[j]) {
                int v = to[j];
                if(v ^ nt and v ^ a[i].pre) {
                    ch[i] = v;
                    break;
                }
            }
        }
        // cout << ch[i] << " ";
    }
    // cout << endl;

    // for(int i = 1; i <= n; ++i)
    //     cout << deps[i] << " ";
    // cout << endl;

    for(int i = 1; i <= m; ++i)
        ask[i] = read();

    for(int i = 1; i <= m; ++i) {
        if(is_chuans and sz[1] > 3)
            printf("%lld\n", dep[n]);
        else {
            int res = 0;
            for(int k = 1; k > -1; k = a[k].nxt) {
                for(int j = a[k].nxt; j > -1; j = a[j].nxt) {
                    int cj = ch[j], ck = ch[k];
                    // if(!cj or !ck)
                    //     continue;
                    if(deps[j] < deps[k])
                        continue;
                    int c1 = 0, c2 = 0, c3 = 0;
                    if(ck)
                        c1 = calc(j, ck, ask[i]);
                    if(cj)
                        c2 = calc(cj, k, ask[i]);
                    if(cj and ck)
                        c3 = calc(cj, ck, ask[i]);
                    // cout << c1 << " " << c2 << " " << c3 << endl;
                    res = max(res, max(c1, max(c2, c3)));
                    if(deps[j] - deps[k] > 1)
                        res = max(res, calc(j, k, ask[i]));
                }
            }
            if(res > dep[n] or res == 0)
                res = dep[n];
            printf("%lld\n", res);
        }
    }


    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
