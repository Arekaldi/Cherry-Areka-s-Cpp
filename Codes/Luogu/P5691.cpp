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

const int maxn = 4e6 + 1;

int tota, totb;
int m, n, k[maxn], p[maxn], a[maxn], b[maxn];

map <int, int> M;

inline int Power(int x, int a) {
    int ans = 1;
    while(a) {
        if(a & 1)
            ans *= x;
        a >>= 1;
        x *= x;
    }
    return ans;
}

inline void Dfs(int up, int x, int now, int opt) {
    if(x > up)
        return;
    for(int i = 1; i <= m; ++i) {
        int s = Power(i, p[x]);
        if(opt == 1 and x == up)
            a[++tota] = now + s * k[x];
        else if(x == up)
            b[++totb] = now + s * k[x];
        Dfs(up, x + 1, now + s * k[x], opt);
    }
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        k[i] = read(), p[i] = read();

    
    Dfs((n >> 1), 1, 0, 1);
    Dfs(n, (n >> 1) + 1, 0, 0);

    for(int i = 1; i <= tota; ++i)
        M[a[i]]++;

    int res = 0;
    for(int i = 1; i <= totb; ++i)
        res += M[-b[i]];
    
    printf("%lld\n", (long long)(res * 1ll));
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
