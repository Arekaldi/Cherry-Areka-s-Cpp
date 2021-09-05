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

inline int Count(int n) {
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
    return n;
}

signed main() {
    #define Areka
    #ifdef Areka
        freopen("flowers.in", "r", stdin);
        freopen("flowers.out", "w", stdout);
    #endif
    int T = read();
    while(T--) {
        int a = read(), b = read(), n = read();
        int res = 0, now = b;
        for(int i = 1; i <= n; ++i) {
            now += a;
            res += Count(now);
        }
        printf("%lld\n", res);
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
