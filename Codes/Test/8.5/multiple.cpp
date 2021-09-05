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

const int maxn = 1e6 + 1, Mod = 998244353;

int a[maxn], n, m, q;

signed main() {

    #define Areka
    #ifdef Areka
        freopen("multiple.in", "r", stdin);
        freopen("multiple.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();
    
    for(int i = 1; i <= m; ++i) {
        int p = read(), x = read();
        for(int j = 1; j <= n / p; ++j) {
            a[p * j] = (a[p * j] + x * j) % Mod;
        }
    }

    for(int i = 1; i <= q; ++i) {
        int k = read();
        int res = 0;
        for(int j = 1; j <= n / k; ++j)
            res = (res + j * a[k * j]) % Mod;
        printf("%lld\n", res);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
