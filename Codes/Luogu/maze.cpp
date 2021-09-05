#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2000010;
#define P pair <int, int>
#define mk make_pair

int n, m, tot, ans = INT_MAX;
int head[maxn], dis[2][maxn];

struct Node {
	int val, to, next;
}E[maxn];

bool vis[maxn];

void Add_edge(int u, int v, int w) {
	E[++tot].to = v;
	E[tot].next = head[u];
	head[u] = tot;
	E[tot].val = w;
}

priority_queue <P, vector<P>, greater<P> > Q;

int g(int x){return x == 0 ? 1 : n;}

void Dij(int Type) {
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; ++i) 
		dis[Type][i] = INT_MAX;
	Q.push(mk(0, Type == 0 ? 1 : n));
	dis[Type][g(Type)] = 0;
	
	while(!Q.empty()) {
		P tp = Q.top(); Q.pop();
		int u = tp.second;
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = E[i].next) {
			int v = E[i].to;
			int &d = dis[Type][u], &l = dis[Type][v];
			if(l > d + E[i].val) {
				l = d + E[i].val;
				Q.push(mk(l, v));
			}
		}
	}
}

signed main() {
//	freopen("maze.in", "r", stdin);
//	freopen("maze.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		Add_edge(u, v, w);
		Add_edge(v, u, w);
	}
	Dij(0); Dij(1);
//	for(int i = 1; i <= n; ++i) 
//		cout << dis[0][i] << " " << dis[1][i] << endl;
	
	for(int i = 1; i <= n; ++i) {
		for(int e = head[i]; e; e = E[e].next) {
			int v = E[e].to;
			if(dis[0][i] + dis[1][v] + E[e].val > dis[0][n])
				ans = min(ans, dis[0][i] + dis[1][v] + E[e].val);
		}
	}
	
	cout << ans;
}
