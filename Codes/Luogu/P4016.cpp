#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}


const int maxM = 10000010, maxn = 210, Inf = 0x7ffffff;

struct edge {
    int to, val, next;
}E[maxM];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];


void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u];
    head[u] = tot;
}

queue <int> Q;
bool Bfs(int s, int t) {
    memset(dis, -1, sizeof(dis));

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
        k = Dfs(s, INT_MAX, t);
        ans += k;
    }
    return ans;
}

int x[maxn], sum, aver;

bool Judge(int i) {
    return x[i] > aver;
}

signed main() {
    memset(head, -1, sizeof(head));
    n = read();
    s = 0, t = n + 1;
    
    for(int i = 1; i <= n; ++i) {
        x[i] = read();
        sum += x[i];
    }

    aver = sum / n;

    for(int i = 1; i <= n; ++i) {
        if(x[i] == aver) continue;
        if(!Judge(i)) {
            Add_edge(s, i, aver - x[i]);
            Add_edge(i, s, 0);
            int xl = i - 1 == 0 ? n : i - 1, xr = i + 1 == n + 1 ? 1 : i + 1;
            if(Judge(xl)) Add_edge(i, xl, x[xl] - x[i]), Add_edge(n, i, 0);
            if(Judge(xr)) Add_edge(i, xr, x[xr] - x[i]), Add_edge(xr, i, 0);

        }
        else {
            Add_edge(i, t, x[i] - aver);
            Add_edge(t, i, 0);
            int xl = i - 1 == 0 ? n : i - 1, xr = i + 1 == n + 1 ? 1 : i + 1;
            if(!Judge(xl)) Add_edge(xl, i, Inf), Add_edge(i, xl, 0);
            if(!Judge(xr)) Add_edge(xr, i, Inf), Add_edge(i, xr, 0);
        } 
    }

    cout << Dinic(s, t) << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif

    return 0;
}