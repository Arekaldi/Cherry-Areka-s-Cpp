#include <bits/stdc++.h>

using namespace std;

#define RE register
const int maxn = 5e3 + 10, maxm = 5e6 + 10, Inf = 0x7fffffff;
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
int cur[maxn];

void Add_edge(int u, int v, int w, int c) {
	E[++tot].to = v, E[tot].val = w, E[tot].next = head[u], E[tot].cost = c;
	head[u] = tot;
}

deque <int> Q;
bool vis[maxn];
bool Inq[maxn];

bool Spfa(int s, int t) {
	memset(dis, 0x7f, sizeof(dis));
	
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
	int ans = 0, mc = 0, k;
	while(Spfa(s, t)) {
		memcpy(cur, head, sizeof(head));
		k = Dfs(s, INT_MAX, t);
		C += dis[t] * k;
		F += k;
	}
}

signed main() {
	n = read(), m = read(), s = read(), t = read();
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read(), c = read();
		Add_edge(u, v, w, c);
		Add_edge(v, u, 0, -c);
	}
	
	Dinic(s, t);
	
	printf("%lld %lld\n", F, C);
  
  	return 0;
}
