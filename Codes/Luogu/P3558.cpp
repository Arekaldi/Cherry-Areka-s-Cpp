#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1, Inf = 1 << 29;

int a[maxn], dp[maxn][4];

int n;

signed main() {
    n = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();

    memset(dp, 0x7f, sizeof(dp));

    dp[1][a[1] + 1] = 0;
    for(int i = 2; i <= n; ++i) {
        if(a[i] == -1) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = Inf;
            dp[i][2] = dp[i - 1][2] + 2;
        }

        if(a[i] == 0) {
            dp[i][0] = dp[i - 1][0] + 1;
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
            dp[i][2] = dp[i - 1][2] + 1;
        }
        
        if(a[i] == 1) {
            dp[i][0] = dp[i - 1][0] + 2;
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1],dp[i - 1][2]));
        }
    }

    int ans = (1 << 30);

    for(int i = 0; i <= 2; ++i)
        ans = min(ans, dp[n][i]);
    
    printf(ans >= (1 << 28) ? "BRAK" : "%d\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
