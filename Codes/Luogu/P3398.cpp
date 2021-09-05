#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1;

int top[maxn], to[maxn], nxt[maxn], dep[maxn], head[maxn],
	fa[maxn], sz[maxn], son[maxn], n, m, s, tot;

inline void Add_edge(int u, int v) {
	to[++tot] = v, nxt[tot] = head[u];
	head[u] = tot;
}

inline void Dfs1(int x, int f) {
	sz[x] = 1, son[x] = 0;
	dep[x] = dep[f] + 1;
	fa[x] = f;
	for(int v, i = head[x]; i; i = nxt[i]) {
		if((v = to[i]) != f) {
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
	for(int v, i = head[x]; i; i = nxt[i])
		if((v = to[i]) != f)
			Dfs2(v, x);
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
	return x;
}
class Node {
    public:
        int dep, v;
        Node() {}
        Node(int d, int p) : dep(d), v(p) {}
        inline bool operator < (const Node &a) const {
            return a.dep < dep;
        }
};

vector <Node> vs;

signed main() {
    // #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("w.txt", "w", stdout);
    #endif
	n = read(), m = read();
	for(int i = 1; i < n; ++i) {
		int u = read(), v = read();
		Add_edge(u, v), Add_edge(v, u);
	}
	Dfs1(1, 0);
	Dfs2(1, 0);
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read();
        int x = read(), y = read();
		int p1 = lca(u, x), p2 = lca(u, y), p3 = lca(v, x), p4 = lca(v, y);
        vs.clear();
        vs.push_back(Node(dep[p1], p1)), vs.push_back(Node(dep[p2], p2)),
        vs.push_back(Node(dep[p3], p3)), vs.push_back(Node(dep[p4], p4));
        sort(vs.begin(), vs.end());
        int p = vs[0].v, q = vs[1].v;
        if(p != q) {
            puts("Y");
            continue;
        }
        else {
            int mm = lca(u, v), nn = lca(x, y);
            vs.clear();
            vs.push_back(Node(dep[mm], mm)), vs.push_back(Node(dep[nn], nn));
            sort(vs.begin(), vs.end());
            int st = vs[0].dep;
            if(dep[p] < st)
                puts("N");
            else
                puts("Y");
            continue;
        }
	}
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}