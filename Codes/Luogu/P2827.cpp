#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 7e7 + 1;

class Node {
    public:
        int num, str, tru;
        Node() {}
        Node(int a, int b, int c) : num(a), str(b), tru(c) {}
        inline bool operator < (const Node &g) const {
            if(g.tru > 0 and tru > 0)
                return g.tru > tru;
            else if(g.tru > 0 and tru <= 0)
                return true;
            else if(g.tru < 0 and tru >= 0)
                return false;
            else if(g.tru < 0 and tru < 0)
                return abs(tru) > abs(g.tru);
            else if(g.tru == 0 and tru >= 0)
                return false;
            else if(g.tru == 0 and tru < 0)
                return true;
            return true;
        }
};

priority_queue <Node> Q;
double u, v;
int t, n, m, ad, p, q;
int a[maxn];
int mx;

int tot, sta[maxn];

inline bool Camp(int a, int b) {
    return a > b;
}

signed main() {
    // #define Areka
    #ifdef Areka
        // freopen("1.txt", "r", stdin);
        freopen("w.out", "w", stdout);
    #endif
    n = read(), m = read(), q = read();
    int u1 = read(), v1 = read(), t = read();
    u = u1 * 1.0, v = v1 * 1.0;
    u /= v;

    for(int i = 1; i <= n; ++i)
        a[i] = read(), (a[i] > mx) and (mx = a[i]);

    if(m == 0) {
        sort(a + 1, a + n + 1, Camp);
        puts("");
        for(int i = t; i <= n; i += t)
            printf("%lld ", a[i]);
        return 0;
    }

    bool flag = false;
    for(int i = 1; i <= n; ++i) {
        if(flag or a[i] != mx)
            Q.push(Node(a[i], 0, a[i]));
        if(a[i] == mx)
            flag = true;
    }

    if(t == 1)
        printf("%lld ", mx);
    double mxx = mx * 1.0;
    double ul = floor(mxx * u);
    int np = ul;
    Q.push(Node(np, q, np - q)), Q.push(Node(mx - np, q, mx - np - q));
    mx = Q.top().num + q, Q.pop();
    ad = q;

    for(int i = 2; i <= m; ++i) {
        if(i % t == 0)
            printf("%lld ", mx);
        double mxx = mx * 1.0;
        double ul = floor(mxx * u);
        int n1 = ul, n2 = mx - n1;
        Q.push(Node(n1, ad + q, n1 - ad - q)), Q.push(Node(n2, ad + q, n2 - ad - q));
        ad += q;
        mx = Q.top().num - Q.top().str + ad, Q.pop();
    }

    puts("");

    sta[++tot] = mx;
    while(!Q.empty())
        sta[++tot] = Q.top().tru + ad, Q.pop();

    sort(sta + 1, sta + tot + 1, Camp);

    for(int i = t; i <= tot; i += t)
        printf("%lld ", sta[i]);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
