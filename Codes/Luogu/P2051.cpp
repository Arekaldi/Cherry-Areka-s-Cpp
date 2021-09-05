#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

#define int long long

const int maxn = 1e2 + 1, Mod = 9999973;

int n, m;
int dp[maxn][maxn][maxn];

signed main() {

    n = read(), m = read();

    dp[0][0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= m; ++j) {
            for(int k = 0; k + j <= m; ++k) {
                dp[i][j][k] = dp[i - 1][j][k];

                if(j >= 1)
                    dp[i][j][k] += dp[i - 1][j - 1][k] * (m - j - k + 1), dp[i][j][k] %= Mod;
                if(k >= 1)
                    dp[i][j][k] += dp[i - 1][j + 1][k - 1] * (j + 1), dp[i][j][k] %= Mod;

                if(j >= 2)
                    dp[i][j][k] += dp[i - 1][j - 2][k] * ((((m - j - k + 1) * (m - j - k + 2)) >> 1) % Mod), dp[i][j][k] %= Mod;
                if(k >= 1)
                    dp[i][j][k] += dp[i - 1][j][k - 1] * ((j * (m - k - j + 1)) % Mod);
                if(k >= 2)
                    dp[i][j][k] += dp[i - 1][j + 2][k - 2] * ((((j + 1) * (j + 2)) >> 1) % Mod), dp[i][j][k] %= Mod;

            }
        }
    }
    
    int ans = 0;
    for(int i = 0; i <= m; ++i)
        for(int k = 0; k + i <= m; ++k)
            ans = (ans + dp[n][i][k]) % Mod;
    
    printf("%lld\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
