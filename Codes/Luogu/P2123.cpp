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

const int maxn = 2e4 + 1;

class Node {
    public:
        int a, b;
        inline bool operator < (const Node &g) const {
            if(min(a, g.b) == min(b, g.a))
                return a < g.a;
            else
                return min(a, g.b) < min(b, g.a);
        }
};

Node P[maxn];
int c[maxn], aa[maxn];

signed main() {
    int T = read();
    while(T--) {
        memset(c, 0, sizeof(c));
        memset(aa, 0, sizeof(aa));
        int n = read();
        for(int i = 1; i <= n; ++i)
            P[i].a = read(), P[i].b = read();
        sort(P + 1, P + n + 1);
        for(int i = 1; i <= n; ++i)
            aa[i] = aa[i - 1] + P[i].a;
        c[1] = P[1].a + P[1].b;
        for(int i = 2; i <= n; ++i)
            c[i] = max(c[i - 1], aa[i]) + P[i].b;
        printf("%lld\n", c[n]);
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
