#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

#define int long long

const int maxn = 2e4 + 1, maxm = 5e7 + 1, Inf = LLONG_MAX;

struct edge {
    int to, val, next, cost;
}E[maxm];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxn];

void Add_edge(int u, int v, int w, int c) {
    E[++tot].to = v, E[tot].val = w, E[tot].next = head[u], E[tot].cost = c;
    head[u] = tot;
    swap(u, v);
    E[++tot].to = v, E[tot].val = 0, E[tot].next = head[u], E[tot].cost = -c;
    head[u] = tot;
}

deque <int> Q;
bool vis[maxn];
bool Inq[maxn];

bool Spfa(int s, int t) {
    for(int i = s; i <= t; ++i)
    	dis[i] = LLONG_MAX;
    
    Q.push_back(s); dis[s] = 0;
    Inq[s] = true;
    
    while(!Q.empty()) {
        int x = Q.front(); Q.pop_front();
        Inq[x] = false;
        for(int i = head[x]; i > -1; i = E[i].next) {
            int v = E[i].to;
            if(dis[v] > dis[x] + E[i].cost and E[i].val) {
                dis[v] = dis[x] + E[i].cost;
                if(!Inq[v]) {
                    if(!Q.empty() and dis[v] < dis[Q.front()]) 
                        Q.push_front(v), Inq[v] = true;
                    else
                        Q.push_back(v), Inq[v] = true;
                }
            }
        }
    }
    
    return dis[t] < Inf;
}

int Dfs(int x, int flew, int t) {
    if(x == t) 
        return flew;
    vis[x] = true;
    
    int rest = flew;
    
    for(int i = cur[x]; i > -1 && rest; i = E[i].next) {
        int v = E[i].to, f = E[i].val;
        
        cur[x] = i;
        
        if(vis[v] or !f or dis[v] != dis[x] + E[i].cost) continue;
        
        int k = Dfs(v, min(rest, f), t);
        E[i].val -= k, E[i ^ 1].val += k;
        rest -= k;
        
        if(!k) dis[v] = 0;
    }
    
    vis[x] = false;
    return flew - rest;
}

int F, C;

inline void Dinic(int s, int t) {
    int k;
    while(Spfa(s, t)) {
        memcpy(cur, head, sizeof(head));
        k = Dfs(s, INT_MAX, t);
        C += dis[t] * k;
        F += k;
    }
}

int R[maxn];
int N;
int p, fk, fm;

signed main() {
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	
    memset(head, -1, sizeof(head));

    N = read();
    s = 0, t = N + N + 1;
    for(int i = 1; i <= N; ++i) {
    	R[i] = read();
        Add_edge(s, i, R[i], 0);
        Add_edge(i + N, t, R[i], 0);
	}


    p = read(), m = read(), fk = read(), n = read(), fm = read();

    for(int i = 1; i <= N; ++i) {
        Add_edge(s, i + N, Inf, p);
        if(i + m <= N) Add_edge(i, i + m + N, Inf, fk);
        if(i + n <= N) Add_edge(i, i + n + N, Inf, fm);
        if(i + 1 <= N) Add_edge(i, i + 1, Inf, 0);
    }

    Dinic(s, t);

    cout << C << endl;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

