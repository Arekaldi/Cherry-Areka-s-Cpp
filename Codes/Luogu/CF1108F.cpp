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

int fa[maxn], n, m;

class Edge {
    public:
        int frm, to, val;
        inline bool operator < (const Edge &e) const {
            return e.val > val;
        }
};

Edge E[maxn];

inline int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

map <int, bool> M;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i)
        fa[i] = i, E[i].frm = read(),
        E[i].to = read(), E[i].val = read();

    sort(E + 1, E + m + 1);

    int p = 1, q = 2, ans = 0;
    while(p <= m) {
        int sum = 0;
        while(E[p].val == E[q].val)
            q++;
        for(int i = p; i < q; ++i) {
            int fu = Find(E[i].frm), fv = Find(E[i].to);
            if(fu != fv)
                sum++;
        }
        for(int i = p; i < q; ++i) {
            int fu = Find(E[i].frm), fv = Find(E[i].to);
            if(fu != fv)
                sum--, fa[fu] = fv;
        }
        p = q;
        ans += sum;
    }

    printf("%d\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
