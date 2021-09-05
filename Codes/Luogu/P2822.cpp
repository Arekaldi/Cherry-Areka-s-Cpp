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

const int maxn = 2e3 + 1, p = 1e9 + 7;

int n, m, T, k, fac[maxn];
int c[maxn][maxn], dp[maxn][maxn];

inline void Get_Catlan() {
    c[1][0] = c[1][1] = 1;
    for(int i = 2; i < maxn; ++i) {
        c[i][0] = 1;
        for(int j = 1; j < maxn; ++j) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            if(!c[i][j])
                dp[i][j]++;
        }
        dp[i][i + 1] = dp[i][i];
    }
}

signed main() {
    T = read(), k = read();
    Get_Catlan();
    while(T--) {
        int n = read(), m = read();
        printf("%lld\n", m > n ? dp[n][n] : dp[n][m]);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
