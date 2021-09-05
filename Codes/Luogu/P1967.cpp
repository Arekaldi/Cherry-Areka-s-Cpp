//Written by Areka
#include <bits/stdc++.h>

using namespace std;

inline int read() {
	int x, f = 1;
	char ch;
	while(!isdigit(ch = getchar()))
		(ch == '-') and (f = -1);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
	return x * f;
}

const int maxn = 1e6 + 1;

class Edge {
	public:
		int to, nxt;
		Edge() {}
		Edge(int a, int b) : to(a), nxt(b) {}
};

class Edges {
	public:
		int u, v, w;
		inline bool operator < (const Edges &g) const {
			return g.w < w;
		}
};

Edge E[maxn];
Edges ee[maxn];

int n, m, tot, head[maxn], dep[maxn], val[maxn],
	sz[maxn], son[maxn], top[maxn], fff[maxn];

inline void Add_edge(int u, int v) {
	E[++tot] = Edge(v, head[u]);
	head[u] = tot;
}

inline void Dfs1(int x, int ffa) {
	sz[x] = 1, dep[x] = dep[ffa] + 1;
	fff[x] = ffa;
	for(int v, i = head[x]; i; i = E[i].nxt) {
		if((v = E[i].to) ^ ffa) {
			Dfs1(v, x);
			sz[x] += sz[v], (sz[v] > sz[son[x]]) and (son[x] = v);
		}
	}
}

inline void Dfs2(int x, int ffa) {
	if(!top[x])
		top[x] = x;
	top[son[x]] = top[x];
	for(int v, i = head[x]; i; i = E[i].nxt) {
		if((v = E[i].to) ^ ffa)
			Dfs2(v, x);
	}
}

int fa[maxn], cnt;

inline int Lca(int x, int y) {
	while(top[x] ^ top[y]) {
		if(dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = fff[top[x]];
	}
	if(dep[x] > dep[y])
		swap(x, y);
	return x;
}


inline int Find(int x) {
	if(fa[x] == 0)
		return fa[x] = x;
	else
		return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

signed main() {
	n = read(), m = read();
	for(int i = 1; i <= m; ++i)
		ee[i].u = read(), ee[i].v = read(), ee[i].w = read();
	sort(ee + 1, ee + m + 1);
	cnt = n;
	for(int i = 1; i <= m; ++i) {
		int u = ee[i].u, v = ee[i].v, w = ee[i].w;
		int fu = Find(u), fv = Find(v);
		if(fu == fv)
			continue;
		Add_edge(fu, ++cnt), Add_edge(fv, cnt);
		Add_edge(cnt, fu), Add_edge(cnt, fv);
		fa[fu] = fa[fv] = cnt, val[cnt] = w;
	}
	Dfs1(cnt, 0), Dfs2(cnt, 0);
	int q = read();
	for(int i = 1; i <= q; ++i) {
		int x = read(), y = read();
		int fx = Find(x), fy = Find(y);
		if(fx != fy) {
			puts("-1");
			continue;
		}
		printf("%d\n", val[Lca(x, y)]);
	}
}