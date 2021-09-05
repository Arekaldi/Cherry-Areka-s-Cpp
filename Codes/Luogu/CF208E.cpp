#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

vector < pair<int, int> > Q[maxn];

int Son;
int sz[maxn], son[maxn];
int c[maxn];
int n, ans[maxn];
int head[maxn], tot;
class Edge {
	public:
		int to, nxt;
}E[maxn << 1];

inline void Add_edge(int u, int v) {
	E[++tot].to = v, E[tot].nxt = head[u];
	head[u] = tot;
	return;
}
int fa[maxn][25], dep[maxn];

inline int Find_p(int a, int k) {
	int ans = a;
	int Up = log2(dep[a]);
	for(int i = Up; i >= 0; --i) {
		if(dep[ans] - dep[fa[ans][i]] <= k)
			k -= dep[ans] - dep[fa[ans][i]], ans = fa[ans][i];
	}
	return ans;
}

inline void Dfs1(int x, int fas) {
	dep[x] = dep[fas] + 1;
	fa[x][0] = fas;
	for(int i = 1; i <= 24; ++i)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	sz[x] = 1, son[x] = 0;
	for(int i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fas)
			continue;
		Dfs1(y, x);
		sz[x] += sz[y];
		if(sz[son[x]] < sz[y])
			son[x] = y;
	}
}

inline void Add(int x, int fas, int k) {
	c[dep[x]] += k;
	for(int i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fas or y == Son)
			continue;
		Add(y, x, k);
	}
}

inline void Dfs2(int x, int fas, int opt) {
	for(int i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fas or y == son[x])
			continue;
		Dfs2(y, x, 0);
	}
	if(son[x])
		Dfs2(son[x], x, 1), Son = son[x];
	Add(x, fas, 1);
	
//	if(x == 4) {
//		cout << dep[x + 1] << endl;
//	}
	
	for(int j = 0; j < Q[x].size(); ++j) {
		int u = Q[x][j].first, v = Q[x][j].second;
		ans[v] = c[dep[x] + u] - 1;
	}
	Son = 0;
	if(opt == 0)
		Add(x, fas, -1);
}

int Rt[maxn], tot1;

signed main() {
	
	memset(fa, -1, sizeof(fa));
	
	n = read();
	
	for(int i = 1; i <= n; ++i) {
		int p = read();
		if(p == 0) {
			Rt[++tot1] = i;
			continue;
		}
		Add_edge(i, p), Add_edge(p, i), fa[i][0] = p;
	}
	
	dep[0] = 1;
	for(int i = 1; i <= tot1; ++i)
		Dfs1(Rt[i], 0);
		
//	for(int i = 1; i <= n; ++i)
//		cout << dep[i] << endl;
	
	int q = read();
	for(int i = 1; i <= q; ++i) {
		int a = read(), k = read();
		int p = Find_p(a, k);
		if(p == 0) {
			ans[i] = -1;
			continue;
		}
		Q[p].push_back(make_pair(k, i));
	}
	
//	Dfs2(0, -1, 1);
	for(int i = 1; i <= tot1; ++i)
		Dfs2(Rt[i], 0, 0);
	
	for(int i = 1; i <= q; ++i)
		printf("%d ", ans[i] == -1 ? 0 : ans[i]);
}
