#include <bits/stdc++.h>

using namespace std;

#define RE register
const int maxn = 5e4 + 1, maxm = 5e6 + 10, Inf = 0x7fffffff;
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
	E[++tot].to = u, E[tot].val = 0, E[tot].next = head[v], E[tot].cost = -c;
	head[v] = tot;
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

int F, C, k;

inline void Dinic(int s, int t) {
	int k;
	while(Spfa(s, t)) {
		memcpy(cur, head, sizeof(head));
		k = Dfs(s, INT_MAX, t);
		C += dis[t] * k;
//		cout << k << endl;
		F += k;
	}
	return;
}

inline int id(int i, int j, int k) {
	return (i - 1) * n + j + k * n * n;
}

signed main() {
    memset(head, -1, sizeof(head));
    n = read(), k = read();
    s = 0, t = n * n * 2 + 1;
    
    Add_edge(s, id(1, 1, 0), Inf, 0);
    
    for(int i = 1; i <= n; ++i) {
    	for(int j = 1; j <= n; ++j) {
    		int x = read();
    		
			Add_edge(id(i, j, 0), id(i, j, 1), 1, x);
			Add_edge(id(i, j, 0), id(i, j, 1), k - 1, 0);
    		
    		if(j < n)
    			Add_edge(id(i, j, 1), id(i, j + 1, 0), Inf, 0);
			if(i < n)
    			Add_edge(id(i, j, 1), id(i + 1, j, 0), Inf, 0);
		}
	}
	Add_edge(id(n, n, 1), t, Inf, 0);
	
    Dinic(s, t);
    
    cout << C << endl;
    
  	return 0;
}
