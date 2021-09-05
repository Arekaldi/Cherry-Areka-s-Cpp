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

const int maxn = 1e6 + 1, maxv = 1e3 + 1;

class Edge {
	public:
		int to, nxt, val;
		Edge() {}
		Edge(int a, int b, int c) : to(a), nxt(b), val(c) {}
};

Edge E[maxn];

int tot = -1, n, m, rep, vv[maxn], top[maxn],
	sz[maxn], son[maxn], fa[maxn],
	head[maxn], dep[maxn], w[maxn], ww[maxn];

inline void Add_edge(int u, int v, int w) {
	E[++tot] = Edge(v, head[u], w);
	head[u] = tot;
}

inline void Dfs1(int x, int ff) {
	fa[x] = ff, sz[x] = 1, dep[x] = dep[ff] + 1;
	for(int v, i = head[x]; i > -1; i = E[i].nxt) {
		if((v = E[i].to) ^ ff) {
            vv[v] = vv[x] + E[i].val;
			Dfs1(v, x);
			sz[x] += sz[v],
			(sz[son[x]] < sz[v]) and (son[x] = v);
		}
	}	
}

inline void Dfs2(int x, int ff) {
	if(!top[x])
		top[x] = x;
	top[son[x]] = top[x];
	for(int v, i = head[x]; i > -1; i = E[i].nxt)
		if((v = E[i].to) ^ ff)
			Dfs2(v, x);
}

inline int Lca(int x, int y) {
	while(top[x] ^ top[y]) {
		if(dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y])
		swap(x, y);
	return x;
}

class Query {
	public:
		int x, y, lca, val;
		inline bool operator < (const Query &g) const {
			return val > g.val;
		}
};

Query a[maxn];


inline int Dfs3(int x, int ff, int id) {
    int ss = w[x];
	for(int v, i = head[x]; i > -1; i = E[i].nxt)
		if((v = E[i].to) ^ ff)
            ss += Dfs3(v, x, i);
    ww[id] = ww[id ^ 1] = ss;
    return ss;
}

inline bool check(int x) {
	memset(ww, 0, sizeof(ww));
	memset(w, 0, sizeof(w));
	int cnt = 0;
	for(int i = 1; i <= m; ++i) {
		if(a[i].val <= x)
			break;
		w[a[i].lca] -= 2, w[a[i].x]++, w[a[i].y]++;
		cnt++;
	}
    if(cnt == 0)
        return true;
	Dfs3(1, 0, 0);
	for(int i = 0; i <= tot; ++i) {
		if(ww[i] == cnt) {
			if(a[1].val - E[i].val <= x)
				return true;
		}
	}
	return false;
}

signed main() {
	n = read(), m = read();
	
	memset(head, -1, sizeof(head));
	
	for(int i = 1; i < n; ++i) {
		int u = read(), v = read(), w = read();
		Add_edge(u, v, w);
		Add_edge(v, u, w);
	}
	
	Dfs1(1, 0), Dfs2(1, 0);

	for(int i = 1; i <= m; ++i) {
		a[i].x = read(), a[i].y = read(),
		a[i].lca = Lca(a[i].x, a[i].y), a[i].val = vv[a[i].x] + vv[a[i].y] - (vv[a[i].lca] << 1);
	}
	
	sort(a + 1, a + m + 1);
	int l = 0, r = a[1].val, res = r;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid))
			r = mid - 1, res = mid;
		else
			l = mid + 1;
	}
	
	printf("%d\n", res);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}