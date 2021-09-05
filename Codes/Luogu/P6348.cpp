#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e7 + 1;

int head[maxn], nxt[maxn], dis[maxn], val[maxn],
    pos[maxn], to[maxn], n, m, s, cnt, tot;
bool vis[maxn];
inline void Add_edge(int u, int v, int w) {
    to[++tot] = v, nxt[tot] = head[u], val[tot] = w,
    head[u] = tot;
}

namespace SegMentTree {

    class SegMentt {
        public:
            int l, r;
    };
    SegMentt T[maxn * 4];

    inline void Build(int p, int l, int r, int opt) {
        T[p].l = l, T[p].r = r;
        if(l == r) {
            if(!opt)
                pos[l] = p;
            else
                Add_edge(p + 4 * n, p, 0);
            return;
        }
        int mid = (l + r) >> 1;
        Build(p << 1, l, mid, opt), Build((p << 1) | 1, mid + 1, r, opt);
        if(!opt)
            Add_edge(p << 1, p, 0),
            Add_edge((p << 1) | 1, p, 0);
        else
            Add_edge(p + 4 * n, (p << 1) + 4 * n, 0),
            Add_edge(p + 4 * n, (p << 1) + 4 * n + 1, 0);
        return;
    }
    inline void Change(int p, int l, int r, int v, int opt) {
        if(T[p].l >= l and T[p].r <= r) {
            if(!opt)
                Add_edge(p, v, 0);
            else
                Add_edge(v, p + 4 * n, 1);
            return;
        }
        int mid = (T[p].l + T[p].r) >> 1;
        if(l <= mid)
            Change(p << 1, l, r, v, opt);
        if(r > mid)
            Change((p << 1) | 1, l, r, v, opt);
    }
}

class Node {
    public:
        int x, dis;
        inline bool operator < (const Node g) const {
            return dis > g.dis;
        }
        Node() {}
        Node(int a, int b) : x(a), dis(b) {}
};

priority_queue <Node> Q;

inline void Dijkstra(int s) {
    memset(dis, 0x7f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    Q.push(Node(s, 0)), dis[s] = 0;
    while(!Q.empty()) {
        Node now = Q.top(); Q.pop();
        int x = now.x;
        if(vis[x])
            continue;
        vis[x] = true;
        for(int i = head[x]; i; i = nxt[i]) {
            int v = to[i];
            if(dis[v] > dis[x] + val[i]) {
                dis[v] = dis[x] + val[i];
                Q.push(Node(v, dis[v]));
            }
        }
    }
}

signed main() {
    n = read(), m = read(), s = read();
    SegMentTree :: Build(1, 1, n, 0),
    SegMentTree :: Build(1, 1, n, 1);
    cnt = n << 3;
    for(int i = 1; i <= m; ++i) {
        int a = read(), b = read(), c = read(), d = read();
        SegMentTree :: Change(1, a, b, ++cnt, 0),
        SegMentTree :: Change(1, c, d, cnt, 1),
        SegMentTree :: Change(1, c, d, ++cnt, 0),
        SegMentTree :: Change(1, a, b, cnt, 1);
    }

    Dijkstra(pos[s]);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", dis[pos[i]]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
