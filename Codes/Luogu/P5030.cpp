#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int Inf = 0x7fffffff;
const int maxn = 100001, maxm = 90000001;

struct edge {
    int to, val, next;
}E[maxm];

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];
int n, m, s, t, K;

void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    memset(dis, 0, sizeof(dis));

    Q.push(s); dis[s] = 1;

    while(!Q.empty()) {
        int x = Q.front(); Q.pop();
        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(!dis[v] and E[i].val) {
                dis[v] = dis[x] + 1;
                Q.push(v);
            }
        }
    }

    return dis[t];
}

int Dfs(int x, int flew, int t) {
    if(x == t) return flew;

    int rest = flew;

    for(int i = cur[x]; i > -1 && rest; i = E[i].next) {
        int v = E[i].to, f = E[i].val;

        cur[x] = i;

        if(!f or dis[v] != dis[x] + 1) continue;

        int k = Dfs(v, min(rest, f), t);
        E[i].val -= k, E[i ^ 1].val += k;
        rest -= k;

        if(!k) dis[v] = 0;
    }
    return flew - rest;
}

int Dinic(int s, int t) {
    int ans = 0, k;
    while(Bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        while(k = Dfs(s, INT_MAX, t))
            ans += k;
    }
    return ans;
}

bool un[201][201];
int id(int x, int y) {
    return (x - 1) * m + y;
}

int gx[] = {1, 1, -1, -1, 3, 3, -3, -3};
int gy[] = {3, -3, 3, -3, 1, -1, 1, -1};



signed main() {
    n = read(), m = read(), K = read();
    memset(head, -1, sizeof(head));

    for(int i = 1; i <= K; ++i) {
        int x = read(), y = read();
        un[x][y] = 1;
    }

    s = 0, t = (n * m * 2) + 1;
    int ww = n * m;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j)  {
            if(un[i][j]) continue;
            Add_edge(s, id(i, j), 1), Add_edge(id(i, j), s, 0);
            Add_edge(id(i + ww, j + ww), t, 1), Add_edge(t, id(i + ww, j + ww), 0);       
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            for(int k = 0; k < 8; ++k) {
                int x = i + gx[k], y = j + gy[k];
                if(x < 1 or y < 1 or x > n or y > m) continue;
                if(un[x][y]) continue;
                Add_edge(id(x + ww, y + ww), id(i, j), 0), Add_edge(id(i, j), id(x + ww, y + ww), Inf);
            }
        }
    }

// n * m - K - 
    //23
    int ans = Dinic(s, t) / 2;

    printf("%d\n", n * m - K - ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif

    return 0;
}
