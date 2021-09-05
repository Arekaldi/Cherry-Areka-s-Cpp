#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1, maxa = 30;

int a[maxn], c[maxn][maxa], n, m;
int sz[maxn], son[maxn];
long long nans, mc, Son, ans[maxn];

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


int dep[maxn];

inline void Dfs1(int x, int fas) {
	dep[x] = dep[fas] + 1;
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

vector < pair<int, int> > Q[maxn];

inline void Add(int x, int fa, int k) {
	c[dep[x]][a[x]] += k;
	for(int i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fa or y == Son)
			continue;
		Add(y, x, k);
	}
	return;
}

inline void Dfs2(int x, int fa, int opt) {
	for(int i = head[x]; i; i = E[i].nxt) {
		int y = E[i].to;
		if(y == fa or y == son[x])
			continue;
		Dfs2(y, x, 0);
	}
	if(son[x])
		Dfs2(son[x], x, 1), Son = son[x];

    Add(x, fa, 1);

    for(int i = 0; i < Q[x].size(); ++i) {
        int u = Q[x][i].first, v = Q[x][i].second;
        int cnt = 0;
        
        for(int j = 0; j < 26; ++j)
            cnt += (c[u][j] & 1);

        if(cnt > 1)
            ans[v] = 1;
    }

    Son = 0;

	if(opt == 0)
		Add(x, fa, -1), nans = 0, mc = 0;
	return;
}

signed main() {
//	#define Areka
	#ifdef Areka
		freopen("", "r", stdin);
		freopen("", "w", stdout);
	#endif
	
	n = read(), m = read();
		
	for(int i = 2; i <= n; ++i) {
        int fa = read();
        Add_edge(i, fa), Add_edge(fa, i);
	}
	
	for(int i = 1; i <= n; ++i)
		a[i] = getchar() - 'a';

    for(int i = 1; i <= m; ++i) {
        int a = read(), k = read();
        Q[a].push_back(make_pair(k, i));
    }
	
	Dfs1(1, 0);
	Dfs2(1, 0, 1);

	for(int i = 1; i <= m; ++i)
		puts(ans[i] ? "No" : "Yes");

	return 0;
}
