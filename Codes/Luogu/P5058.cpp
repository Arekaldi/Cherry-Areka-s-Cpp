#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e6 + 1;

int to[maxn], nxt[maxn], low[maxn], dfn[maxn], head[maxn];
int n, m, tot, cnt;
int a, b;

bool s[maxn];

inline bool Judge(int x) {
	if(dfn[x] <= dfn[a] and dfn[x] > dfn[b])
        return true;
	if(dfn[x] <= dfn[b] and dfn[x] > dfn[a])
        return true;
	return false;
}

inline void Tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    int ch = 0;
    for(int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if(!dfn[v]) {
            Tarjan(v, fa);
            low[x] = min(low[x], low[v]);
            if(low[v] >= dfn[x] and x != a and x != b and Judge(x))
                s[x] = true;
        }
        else if(dfn[v])
            low[x] = min(low[x], dfn[v]);
    }
}

inline void Add_edge(int u, int v) {
    to[++tot] = v, nxt[tot] = head[u];
    head[u] = tot;
}

signed main() {
    n = read();
    while(true) {
        int u = read(), v = read();
        if(!u and !v)
            break;
        Add_edge(u, v);
        Add_edge(v, u);
    }

    a = read(), b = read();

    for(int i = 1; i <= n; ++i)
        if(!dfn[i])
            Tarjan(i, i);

    for(int i = 1; i <= n; ++i)
        if(s[i]) {
            cout << i << endl;
            goto Areka;
        }
    goto Areka_;
    if(false) {
        Areka:;
        #ifndef ONLINE_JUDGE
            getchar();
        #endif
        return 0;
    }

    if(false) {
        Areka_:;
        puts("No solution");
        #ifndef ONLINE_JUDGE
            getchar();
        #endif
        return 0;
    }
}
