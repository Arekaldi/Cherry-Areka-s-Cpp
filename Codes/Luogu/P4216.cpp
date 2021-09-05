#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1;

int to[maxn], nxt[maxn], sz[maxn], head[maxn],
	son[maxn], top[maxn], fa[maxn], dep[maxn],
	str[maxn], ans1[maxn], ans2[maxn];
int n, m, tot;

class Query {
	public:
		int id, tp, x;
		Query() {}
		Query(int a, int b, int c) : id(a), tp(b), x(c) {}
};

vector <Query> v[maxn];

class Tree_Array {
	private:
		int t[maxn];
		inline int lowbit(int x) {
			return x & (-x);
		}
	public:
		inline void Add(int pos, int v) {
			while(pos <= n) {
				t[pos] += v;
				pos += lowbit(pos);
			}
		}
		inline int Ask(int pos) {
			int res = 0;
			while(pos) {
				res += t[pos];
				pos -= lowbit(pos);
			}
			return res;
		}
};

Tree_Array T;

inline void Add_edge(int u, int v) {
	to[++tot] = v, nxt[tot] = head[u];
	head[u] = tot;
}

inline void Dfs1(int x, int f) {
	sz[x] = 1, dep[x] = dep[f] + 1;
	fa[x] = f;
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

inline int Lca(int u, int v) {
	int x = u, y = v;
	while(top[x] ^ top[y]) {
		if(dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y])
		return y;
	return x;
}

inline void Dfs3(int x, int f) {
	if(str[x] != 0)
		T.Add(str[x], 1);
	for(int v, i = head[x]; i; i = nxt[i]) {
		if((v = to[i]) ^ f)
			Dfs3(v, x);
	}
	for(int i = 0; i < v[x].size(); ++i) {
		int id = v[x][i].id, xx = v[x][i].x, tp = v[x][i].tp;
		if(xx == 0)
			continue;
		ans2[id] += tp * T.Ask(xx - 1);
	}
	if(str[x] != 0)
		T.Add(str[x], -1);
}

int rt, cnt;
signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		int ff = read();
		Add_edge(ff, i), Add_edge(i, ff);
		(ff == 0) and (rt = i);
	}
	Dfs1(rt, 0), Dfs2(rt, 0);
	
	int q = read();
	for(int i = 1; i <= q; ++i) {
		int k = read();
		if(k == 1) {
			int x = read(), y = read(), c = read();
			int ff = Lca(x, y), fff = fa[ff];
			cnt++;
			ans1[cnt] = dep[x] + dep[y] - dep[ff] - dep[fff];
			if(i < c)
				continue;
			v[x].push_back(Query(cnt, 1, i - c));
			v[y].push_back(Query(cnt, 1, i - c));
			v[ff].push_back(Query(cnt, -1, i - c));
			v[fff].push_back(Query(cnt, -1, i - c));
		}
		else {
			int x = read();
			str[x] = i;
		}
	}
	
	Dfs3(rt, 0);
	for(int i = 1; i <= cnt; ++i)
		printf("%d %d\n", ans1[i], ans2[i]);
}
