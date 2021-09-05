#include <bits/stdc++.h>

using namespace std;

const int maxm = 2e5 + 1, maxn = 1e5 + 1;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, m;

class Node {
    private :
        struct Edge {
            int to, nxt, from;
            bool vis;
        }E[maxm];

    public :
        int head[maxn];
        int tot = 0;
        inline void Add_edge(int u, int v) {
            E[++tot].nxt = head[u], head[u] = tot;
            E[tot].to = v, E[tot].from = u;
        }
        inline void Mark(int tot) {
            E[tot].vis = true;
        }
        inline pair <int, int> Get(int tot) {
            return make_pair(E[tot].from, E[tot].to);
        }
        inline bool Judge(int tot) {
            return E[tot].vis;
        }
        inline int N(int tot) {
            return E[tot].nxt;
        }
}Es;

class Union_Set {
    public :
        int Fa[maxn];

        inline void init() {
            for(int i = 1; i <= maxn; ++i)
                Fa[i] = i;
        }

        inline int Find(int x) {
            return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);
        }

        inline void Marge(int u, int v) {
            int x = Find(u), y = Find(v);
            if(x == y) return;
            Fa[x] = Fa[y];
        }
}S;

int ans[maxn];

inline void Dfs(int Fa, int x) {
    ans[x] = Fa;
    for(int i = Es.head[x]; i; i = Es.N(i)) {
        pair <int, int> p = Es.Get(i);
        if(!ans[p.second])
            Dfs(x, p.second);
    }
}

pair <int, int> Search[maxm];
int cnt;

signed main() {
    n = read(), m = read();

    S.init();

    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        int x = S.Find(u), y = S.Find(v);
        if(x == y) {
            Search[++cnt].first = u, Search[cnt].second = v;
            continue;
        }
        S.Marge(x, y);
        Es.Add_edge(u, v);
        Es.Add_edge(v, u);
        Es.Mark(i);
    }

    for(int i = 1; i <= cnt; ++i) {
        int u = Search[i].first, v = Search[i].second;
        if(ans[u])
            continue;
        Dfs(u, v);
    }
    
    for(int i = 1; i <= n; ++i)
        if(!ans[i]) {
            puts("NIE");

            #ifndef ONLINE_JUDGE
                getchar();
            #endif
            return 0;
        }

    puts("TAK");

    for(int i = 1; i <= n; ++i)
        cout << ans[i] << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
