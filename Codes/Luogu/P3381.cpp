#include <bits/stdc++.h>

using namespace std;

#define RE register
const int maxn = 5e3 + 1, maxm = 5e6 + 10, Inf = 0x7fffffff;
#define int long long

inline int read() {
	RE int x = 0, f = 1;
	RE char ch = getchar();
	while(ch < '0' or ch > '9') {
		f = ch == '-' ? -1 : f;
		ch = getchar();
	}
	while(ch >= '0' and ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^48);
		ch = getchar();
	}
	return x * f;
}

struct edge {
	int to, val, next, cost;
}E[maxm];

int n, m, s, t;

int tot = -1, dis[maxn], head[maxn];
int cur[maxm];

void Add_edge(int u, int v, int w, int c) {
	E[++tot].to = v, E[tot].val = w, E[tot].next = head[u], E[tot].cost = c;
	head[u] = tot;
}

deque <int> Q;
bool vis[maxn];

bool Spfa(int s, int t) {
	memset(dis, 0x7f, sizeof(dis));
	memset(vis, false, sizeof(vis));
	
	Q.push_back(s); dis[s] = 0;
	vis[s] = true;
	
	while(!Q.empty()) {
		int x = Q.front(); Q.pop_front();
		vis[x] = false;
		for(int i = head[x]; i > -1; i = E[i].next) {
			int v = E[i].to;
			if(dis[v] > dis[x] + E[i].cost and E[i].val) {
				dis[v] = dis[x] + E[i].cost;
				if(!vis[v])
					if(!Q.empty() and dis[v] < dis[Q.front()])
						Q.push_front(v), vis[v] = true;
					else
						Q.push_back(v), vis[v] = true;
			}
		}
	}
	
	return dis[t] < Inf;
}

int Dfs(int x, int flew, int t) {
	vis[x] = true;
	if(x == t) 
		return flew;
	
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
	return flew - rest;
}

int F, C;

inline int Dinic(int s, int t) {
	int ans = 0, mc = 0, k;
	while(Spfa(s, t)) {
		memcpy(cur, head, sizeof(head));
		k = Dfs(s, INT_MAX, t);
		C += dis[t] * k;
		F += k;
	}
	return C;
}

int x[maxn];
int sum, aver;

signed main() {
    memset(head, -1, sizeof(head));
    n = read();
    s = 0, t = n + 1;
    
    for(int i = 1; i <= n; ++i) 
        x[i] = read(), sum += x[i];
    
    aver = sum / n;
    
    for(int i = 1; i <= n; ++i)
    	x[i] -= aver;

    for(int i = 1; i <= n; ++i) {
    	if(x[i] > 0)
    		Add_edge(s, i, x[i], 0), Add_edge(i, s, 0, 0);
    	else if(x[i] < 0)
    		Add_edge(i, t, -x[i], 0), Add_edge(t, i, 0, 0);
    	if(i != 1)
    		Add_edge(i, i - 1, Inf, 1), Add_edge(i - 1, i, 0, -1);
    	if(i != n)
    		Add_edge(i, i + 1, Inf, 1), Add_edge(i + 1, i, 0, -1);
    }
    Add_edge(1, n, Inf, 1), Add_edge(n, 1, 0, -1);
    Add_edge(n, 1, Inf, 1), Add_edge(1, n, 0, -1);
    
    
    cout << Dinic(s, t) << endl;
  
  	return 0;
}

// 17-9-14-16-4-17
