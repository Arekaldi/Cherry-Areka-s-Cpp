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

class Edge {
    public:
        int to, nxt;
        Edge() {}
        Edge(int a, int b) : to(a), nxt(b) {}
};

Edge E[maxn];
int tot, n, m, top, cnt, top_ans, head[maxn], cur[maxn], sta[maxn],
    ss[maxn], vis[maxn], u[maxn], v[maxn], cannot[maxn],
    ans[maxn];

inline void Add_edge(int u, int v) {
    E[++tot] = Edge(v, head[u]);
    head[u] = tot;
}

inline bool Camp(int a, int b) {
    return E[a].to < E[b].to;
}

inline void Dfs(int x, int fa) {
    sta[++top] = x;
    vis[x] = true, cnt++;
    for(int i = cur[x]; i; i = E[i].nxt) {
        if(vis[E[i].to] or cannot[i])
            continue;
        cur[x] = i;
        Dfs(E[i].to, x);
    }
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        u[i] = read(), v[i] = read();
        Add_edge(u[i], v[i]), Add_edge(v[i], u[i]);
    }
    

    for(int i = 1; i <= n; ++i) {
        top = 0;
        for(int j = head[i]; j; j = E[j].nxt)
            ss[++top] = j;
        sort(ss + 1, ss + top + 1, Camp);
        head[i] = ss[1];
        int p = ss[1];
        for(int j = 2; j <= top; ++j)
            p = E[p].nxt = ss[j];
        E[p].nxt = 0;
    }
    
    memcpy(cur, head, sizeof(cur));

    top = 0;

    if(m == n - 1) {
        Dfs(1, 0);
        for(int i = 1; i <= top; ++i)
            cout << sta[i] << " ";
    }

    else {
        ans[1] = n + 1;
        memset(ans, 0x3f, sizeof(ans));
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j)
                cur[j] = head[j], vis[j] = false;
            cnt = top = 0;
            int e;
            for(e = head[u[i]]; e; e = E[e].nxt) {
                if(E[e].to == v[i]) {
                    cannot[e] = true;
                    break;
                }
            }
            int e1;
            for(e1 = head[v[i]]; e1; e1 = E[e1].nxt) {
                if(E[e1].to == u[i]) {
                    cannot[e1] = true;
                    break;
                }
            }
            Dfs(1, 0);
            if(cnt == n) {
                for(int j = 1; j <= top; ++j) {
                    if(ans[j] < sta[j])
                        break;
                    else if(ans[j] > sta[j]) {
                        swap(ans, sta);
                        top_ans = top;
                        break;
                    }
                }
            }
            cannot[e] = cannot[e1] = false;
        }
        for(int i = 1; i <= top_ans; ++i)
            cout << ans[i] << " ";
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}