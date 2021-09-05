#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e6 + 1;

int n, m, num, cnt, ans;

class Edge {
    public:
        int to, nxt, val, frm;
        Edge() {}
        Edge(int a, int b, int c, int d) : to(a), nxt(b), val(c), frm(d) {}
        inline bool operator < (const Edge &a) const {
            return a.val < val;
        }
}E[maxn];

int head[maxn], tot;
inline void Add_edge(int u, int v, int w) {
    E[++tot].to = v, E[tot].nxt = head[u], E[tot].val = w,
    E[tot].frm = u;
    head[u] = tot;
}

int fa[maxn];

inline int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

priority_queue <Edge> Q;

inline void Kruscal() {
	for(int i = 1; i <= n; ++i)
		fa[i] = i;
		
	cnt = 1, ans = 0, num = 0;
	
	while(!Q.empty()) {
		E[++num] = Q.top();
		Q.pop();
	}
	
    for(int i = 1; i <= num; ++i) {
        int u = E[i].to, v = E[i].frm;
        int fu = Find(u), fv = Find(v);
        if(fv != fu) {
            fa[fu] = fv;
            ans += E[i].val;
            cnt++;
            if(cnt == n)
                break;
        }
    }
    printf(cnt != n ? "-1\n" : "%d\n", ans);
    for(int i = 1; i <= num; ++i)
    	Q.push(E[i]);
}

signed main() {

    n = read(), m = read();
    
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        Add_edge(u, v, w), Add_edge(v, u, w);
        Q.push(Edge(v, head[u], w, u));
        Kruscal();
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
