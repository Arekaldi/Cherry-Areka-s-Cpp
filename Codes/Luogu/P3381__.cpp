#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1, inf = 0x7f7f7f7f;

bool inq[maxn], vis[maxn];
int head[maxn], cur[maxn], to[maxn], nxt[maxn],
    val[maxn], cst[maxn], dis[maxn];
int n, m, s, t, tot = -1;

inline void Add_edge(int u, int v, int w, int c) {
    to[++tot] = v, nxt[tot] = head[u];
    val[tot] = w, cst[tot] = c;
    head[u] = tot;
}

queue <int> q;
inline bool Bfs() {
    q.push(s);
    memset(inq, false, sizeof(inq));
    memset(dis, 0x7f, sizeof(dis));
    inq[s] = true, dis[s] = 0;
    while(!q.empty()) {
        int x = q.front();
        // cout << x << endl;
        q.pop();
        inq[x] = false;
        for(int i = head[x]; i > -1; i = nxt[i]) {
            int v = to[i];
            if(val[i] and dis[v] > dis[x] + cst[i]) {
                dis[v] = dis[x] + cst[i];
                if(!inq[v])
                    q.push(v), inq[v] = true;
            }
        }
    }
    // cout << dis[t] << endl;
    return dis[t] < inf;
}

inline int Dfs(int x, int t, int vals) {
    if(x == t)
        return vals;
    vis[x] = true;
    int rest = vals;
    for(int i = cur[x]; i > -1 and rest; i = nxt[i]) {
        int v = to[i];
        cur[x] = i;
        if(!rest or vis[v] or !val[i] or dis[v] != dis[x] + cst[i])
            continue;
        int f = Dfs(v, t, min(val[i], rest));
        val[i] -= f, val[i ^ 1] += f, rest -= f;
    }
    // if(rest)
    //     dis[x] = 0;
    vis[x] = false;
    return vals - rest;
}

int F, C;

inline void Dinic() {
    while(Bfs()) {
        memcpy(cur, head, sizeof(cur));
        int k = Dfs(s, t, inf);
        F += k, C += k * dis[t];
    }
}

signed main() {
    memset(head, -1, sizeof(head));
    n = read(), m = read(), s = read(), t = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read(), c = read();
        Add_edge(u, v, w, c);
        Add_edge(v, u, 0, -c);
    }
    
    Dinic();

    cout << F << " " << C;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
