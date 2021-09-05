#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 10;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, m;

struct Node {
    int head[maxn], etot;
    struct Edge {
        int to, nxt;
    }E[maxn << 1];
    void Add_edge(int a, int b) {
        E[++etot].nxt = head[a];
        E[etot].to = b;
        head[a] = etot;
        return;
    }
}Mp, Ump, Dt, Udt, Zt;

int cnt, dfn[maxn], id[maxn], Fa[maxn];

void dfs(int x) {
    id[dfn[x] = ++cnt] = x;
    for(int i = Mp.head[x]; i; i = Mp.E[i].nxt) {
        int y = Mp.E[i].to;
        if(!dfn[y]) 
            dfs(y), Fa[y] = x, Dt.Add_edge(x, y);
    }
}

int anc[maxn], Manc[maxn], semi[maxn];

int FiFa(int x) {
    if(x == anc[x]) return x;
    int fa = anc[x];
    anc[x] = FiFa(anc[x]);
    if(dfn[semi[Manc[x]]] > dfn[semi[Manc[fa]]])
        Manc[x] = Manc[fa];
    return anc[x];
}

void Tarjan() {
    for(int i = 1; i <= n; ++i)
        anc[i] = Manc[i] = semi[i] = i;
    for(int j = n; j > 1; --j) {
        int x = id[j];
        if(!x)
            continue;
        int res = j;
        for(int i = Ump.head[x]; i; i = Ump.E[i].nxt) {
            int y = Ump.E[i].to;
            if(!dfn[y])
                continue;
            if(dfn[y] < dfn[x]) res = min(res, dfn[y]);
            else {
                FiFa(y);
                res = min(res, dfn[semi[Manc[y]]]);
            }
        }
        semi[x] = id[res];
        anc[x] = Fa[x];
        Dt.Add_edge(semi[x], x);
    }
}

int in[maxn], dept[maxn], fath[maxn][30];

int Lca(int x, int y) {
    if(dept[x] < dept[y]) swap(x, y);
    int d = dept[x] - dept[y];
    for(int i = 0; i <= 20; ++i) 
        if((1 << i) & d) 
            x = fath[x][i];
    if(x == y) return x;
    for(int i = 20; i >= 0; --i) 
        if(fath[x][i] != fath[y][i]) 
            x = fath[x][i], y = fath[y][i];
    return fath[x][0];
}

void Build_T(int x) {
    int s = Udt.E[Udt.head[x]].to;
    for(int i = Udt.head[x]; i; i = Udt.E[i].nxt) {
        int y = Udt.E[i].to;
        s = Lca(s, y);
    }
    dept[x] = dept[s] + 1;
    fath[x][0] = s;
    Zt.Add_edge(s, x);
    for(int i = 1; i <= 20; ++i)
        fath[x][i] = fath[fath[x][i - 1]][i - 1];
}

void topu() {
    for(int i = 1; i <= n; ++i) {
        for(int e = Dt.head[i]; e; e = Dt.E[e].nxt) {
            int y = Dt.E[e].to;
            in[y]++;
            Udt.Add_edge(y, i);
        }
    }
    for(int i = 1; i <= n; ++i) 
        if(!in[i]) 
            Udt.Add_edge(i, 0), Dt.Add_edge(0, i);
    
    queue <int> Q;
    Q.push(0);

    while(!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for(int i = Dt.head[x]; i; i = Dt.E[i].nxt) {
            int y = Dt.E[i].to;
            if(--in[y] <= 0) 
                Q.push(y), Build_T(y);
        }
    }
}

int siz[maxn];

void Upd_sz(int x) {
    siz[x] = 1;
    for(int i = Zt.head[x]; i; i = Zt.E[i].nxt) {
        int y = Zt.E[i].to;
        Upd_sz(y);
        siz[x] += siz[y];
    }
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        Mp.Add_edge(x, y);
        Ump.Add_edge(y, x);
    }

    dfs(1); Tarjan(); topu(); Upd_sz(0);

    for(int i = 1; i <= n; ++i) 
        printf("%d ", siz[i]);
    // cout << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
