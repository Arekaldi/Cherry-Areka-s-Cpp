#include <bits/stdc++.h>

using namespace std;

#define RE register
const int maxn = 5e6 + 10, maxm = 5e6 + 10, Inf = (1 << 30);
//#define int long long

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
	swap(u, v);
	E[++tot].to = v, E[tot].val = 0, E[tot].next = head[u], E[tot].cost = -c;
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

inline int gcd(int x, int y) {
	return y == 0 ? x : gcd(y, x % y);
}

int a, b;

signed main() {
	memset(head, -1, sizeof(head));
	
	a = read(), b = read();
	
	s = a - 1, t = b + b + 1;
	
	for(int i = a; i <= b; ++i)
		Add_edge(s, i, 1, 0), Add_edge(i + b, t, 1, 0);
	
	for(int y = a; y <= b; ++y) {
		for(int x = y + 1; x <= b; ++x) {
			if(x == y) continue;
			
			int w = sqrt(x * x - y * y), s = w * w;
			if(s == x * x - y * y and gcd(w, y) == 1) {
				Add_edge(y, x + b, 1, - x - y);
				Add_edge(x, y + b, 1, - x - y);
			}
		}
	}
	
	Dinic(s, t);
	
//	cout << C << endl;
	
	cout << (F >> 1) << " " << -(C >> 1) << endl;
}
