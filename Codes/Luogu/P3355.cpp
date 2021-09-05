#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    // register int x = 0, f = 1;
    // register char ch = getchar();
    // while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    // for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    // return x * f;
    int x; cin >> x; return x;
}

const int Inf = 0x7fffffff;
const int maxn = 100010, maxm = 6000010, K = 1010;

struct edge {
    int to, val, next;
}E[maxm];

int tot = -1, dis[maxn], head[maxn];
int cur[maxm];
int n, m, s, t;



void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    for(int i = s; i <= t; ++i) dis[i] = -1;
    // memset(dis, -1, sizeof(dis));

    while(!Q.empty()) Q.pop();

    Q.push(s); dis[s] = 1;

    while(!Q.empty()) {
        int x = Q.front(); Q.pop();

        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(dis[v] == -1 and E[i].val) {
                dis[v] = dis[x] + 1;
                Q.push(v);
            }
        }
    }

    return dis[t] != -1;
}

int Dfs(int x, int flew, int t) {
    if(x == t) return flew;

    int rest = flew;

    for(int i = cur[x]; i > -1 and rest; i = E[i].next) {
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

bool un[K][K];
int id(int x, int y) {
    return (x - 1) * n + y;
}

int gx[] = {1, 1, -1, -1, 2, 2, -2, -2}, gy[] = {2, -2, 2, -2, 1, -1, 1, -1};



signed main() {
    scanf("%lld%lld", &n, &m);
    // memset(head, -1, sizeof(head));

    for(int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%lld%lld", &x, &y);
        un[x][y] = 1;
    }

    s = 0, t = n * n + 1;

    for(int i = s; i <= t; ++i) head[i] = -1;
    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)  {
            if(un[i][j]) continue;
            if((i + j) & 1) Add_edge(s, id(i, j), 1), Add_edge(id(i, j), s, 0);
            else Add_edge(id(i, j), t, 1), Add_edge(t, id(i, j), 0);       
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(((i + j) & 1) == 0) continue;
            for(int k = 0; k < 8; ++k) {
                int x = i + gx[k], y = j + gy[k];
                if(x < 1 or y < 1 or x > n or y > n) continue;
                if(un[x][y]) continue;
                Add_edge(id(x, y), id(i, j), 0), Add_edge(id(i, j), id(x, y), Inf);
            }
        }
    }

    // cout << 1 << endl;

    // cout << Bfs(s, t) << endl;

    int ans = n * n - m - Dinic(s, t);
    // cout << Dinic(s, t) << endl;

    printf("%lld\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif

    return 0;
}
