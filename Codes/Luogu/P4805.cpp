#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 401;

int n, ans;
int dp[maxn][maxn];

signed main() {
    n = read();

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            dp[i][j] = -1;

    for(int i = 1; i <= n; ++i)
        dp[i][i] = read(), ans = max(ans, dp[i][i]);

    for(int len = 1; len <= n; ++len)
        for(int l = 1; l + len <= n; ++l) {
            int r = l + len;
            
            for(int k = l; k < r; ++k) {
                if(dp[l][k] == dp[k + 1][r] and dp[l][k] != -1)
                    dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }

            for(int k1 = l; k1 < r; ++k1) {
                for(int k2 = r; k2 - 1 > k1; --k2) {
                    if(dp[l][k1] == dp[k2][r] and dp[k2][r] != -1 and dp[k1 + 1][k2 - 1] != -1)
                        dp[l][r] = max(dp[l][r], dp[l][k1] + dp[k1 + 1][k2 - 1] + dp[k2][r]);
                }
            }

            ans = max(ans, dp[l][r]);
        }
    
    printf("%d\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
