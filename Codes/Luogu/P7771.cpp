#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e6 + 1;

class Edge {
    public:
        int to, nxt;
        Edge() {}
        Edge(int a, int b) : to(a), nxt(b) {}
};

Edge E[maxn];
int n, m, tot, top, cnt, sta[maxn], du[maxn],
    dd[maxn], head[maxn], dx[maxn], cur[maxn];
bool vis[maxn];

class Node {
    public:
        int to, id;
        inline bool operator < (const Node &g) const {
            return g.to > to;
        }
        Node() {}
        Node(int a, int b) : to(a), id(b) {}
};

Node ss[maxn];
int pp;

inline void Add_Edge(int u, int v) {
    E[++tot] = Edge(v, head[u]);
    head[u] = tot;
}


inline void Dfs(int x) {
    while(dd[x]) {
        int minnid = cur[x], minnv = E[cur[x]].to;
        cur[x] = E[cur[x]].nxt;
        if(minnid == 0) {
            sta[++top] = x;
            return;
        }
        vis[minnid] = true, cnt++, dd[x]--, Dfs(minnv);
    }
    sta[++top] = x;
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        Add_Edge(u, v);
        dd[u]++, du[v]++;
    }

    int ff = 0, s = 0, t = 0;
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        if(dd[i] != du[i]) {
            cnt++;
            if(dd[i] == du[i] + 1)
                s = i;
            if(dd[i] == du[i] - 1)
                t = i;
        }
    }
    
    if(cnt != 2 and cnt != 0) {
        puts("No");
        return 0;
    }


    for(int i = 1; i <= n; ++i) {
        pp = 0;
        for(int e = head[i]; e; e = E[e].nxt)
            ss[++pp] = Node(E[e].to, e);
        sort(ss + 1, ss + pp + 1);
        // 将 i 连到的所有边取出并排序
        head[i] = ss[1].id;
        int p = head[i];
        for(int j = 2; j <= pp; ++j)
            E[p].nxt = ss[j].id, p = E[p].nxt;
        E[p].nxt = 0;
        // 进行 nxt 指针的打乱，注意最后的 nxt 要指到 0
    }

    memcpy(cur, head, sizeof(cur));
    // 初始的当前弧为 head

    if(!s)
        s = 1;
    Dfs(s);
    for(int i = top; i >= 1; --i)
        printf("%d ", sta[i]);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
