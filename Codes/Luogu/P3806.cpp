#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1, Mod = 201314;

int n, m, tot;
int top[maxn], to[maxn], dep[maxn], head[maxn],
	son[maxn], fa[maxn], sz[maxn], nxt[maxn];

inline void Dfs1(int x, int f) {
	sz[x] = 1, fa[x] = f;
	dep[x] = dep[f] + 1;
	for(int v, i = head[x]; i; i = nxt[i]) {
		if((v = to[i]) ^ f) {
			Dfs1(v, x);
			sz[x] += sz[v];
			if(sz[v] > sz[son[x]])
				son[x] = v;
		}
	}
}

inline void Dfs2(int x, int f) {
	if(!top[x])
		top[x] = x;
	top[son[x]] = top[x];
	for(int v, i = head[x]; i; i = nxt[i]) {
		if((v = to[i]) ^ f)
			Dfs2(v, x);
	}
}

inline int lca(int u, int v) {
	int x = u, y = v;
	while(top[x] ^ top[y]) {
		if(dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y])
		swap(x, y);
	return dep[u] + dep[v] - (dep[x] << 1);
}

inline void Add_edge(int u, int v) {
	to[++tot] = v, nxt[tot] = head[u];
	head[u] = tot;
}

signed main() {
	n = read(), m = read();
	for(int i = 1; i < n; ++i) {
		int u = read(), v = read();
		Add_edge(u, v), Add_edge(v, u);
	}
	Dfs1(1, 0);
	Dfs2(1, 0);
	for(int i = 1; i <= m; ++i) {
		int k = read();
		bool flag = false;
		for(int j = 1; j <= n; ++j) {
			for(int p = j + 1; p <= n; ++p) {
				if(lca(j, p) == k)
					puts("AYE"), flag = true;
			}
		}
		if(!flag)
			puts("NAY");
	}
}
