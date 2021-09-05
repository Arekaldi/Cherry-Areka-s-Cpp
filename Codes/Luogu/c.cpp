#include <bits/stdc++.h>

using namespace std;

#define int long long

const int mod = 7777777;

inline int read() {
    register int x = 0, f = 1;
    register char ch = getchar();
    while(ch < '0' or ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' and ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
   return x * f;
}

int g[1010][1010], dp[1010][1010], n;

signed main() {
    n = read();
    dp[1][0] = 1;
    for(int i = 2; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j + 1] * (j + 1) + dp[i - 1][j] * (i - j - 2) + g[i - 1][j + 1] * j + g[i - 1][j] * (i - j - 1);
            dp[i][j] %= mod;
            if(j) {
                g[i][j] = 2 * dp[i - 1][j - 1] + g[i - 1][j] + g[i - 1][j - 1];
                g[i][j] %= mod;
            }
        }
    }
    
    printf("%lld\n", dp[n][0]);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
