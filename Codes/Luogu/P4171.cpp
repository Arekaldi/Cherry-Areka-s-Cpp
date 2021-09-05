#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 6e6 + 1;

class Edge {
    public :
        int to, nxt;
        inline void Add(const int a, const int b) {
            to = a, nxt = b;
            return;
        }
};

int head[maxn], tot;
Edge E[maxn];

inline void Add_edge(int u, int v) {
    E[++tot].Add(v, head[u]);
    head[u] = tot;
}

int dfn[maxn], low[maxn];
int ind;
int s[maxn], top, cnt_scc;
int scc[maxn];
bool in[maxn];
int n, m;

inline void Tarjan(int x) {
    dfn[x] = ++ind;
    low[x] = dfn[x];
    s[top++] = x;
    in[x] = true;
    for(int i = head[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(!dfn[v]) {
            Tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else
            if(in[v])
                low[x] = min(low[x], dfn[v]);
    }

    if(dfn[x] == low[x]) {
        cnt_scc++;
        while(s[top] != x) {
            in[s[--top]] = false;
            scc[s[top]] = cnt_scc;
        }
    }
    return;
}

inline void Init() {
    tot = ind = top = cnt_scc = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(s, 0, sizeof(s));
    memset(scc, 0, sizeof(scc));
    memset(in, 0, sizeof(in));
    memset(head, 0, sizeof(head));
}


signed main() {
    int T = read();

    while(T--) {
        n = read(), m = read();
        Init();
        for(int k = 1; k <= m; ++k) {
            // m -> 0 h -> 1
            char c1, c2;
            int i, j;
            cin >> c1 >> i >> c2 >> j;
            int a = ((c1 == 'm') ? 0 : 1), b = ((c2 == 'm') ? 0 : 1);
            Add_edge(i + n * (a ^ 1), j + n * (b & 1));
            Add_edge(j + n * (b ^ 1), i + n * (a & 1));
        }
    
        for(int i = 1; i <= n * 2; ++i)
            if (!dfn[i])
                Tarjan(i);
    
        bool flag = true;
        for(int i = 1; i <= n; ++i)
            if(scc[i] == scc[i + n]) {
                flag = false;
                break;
            }
    
        puts(flag ? "GOOD" : "BAD");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}