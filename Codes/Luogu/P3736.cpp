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

const int maxn = 3e2 + 1, maxk = (1 << 8) + 1;

int dp[maxn][maxn][maxk];

int num[maxn], New[maxk], W[maxk];

int n, k, ans;

char ch;

signed main() {
    n = read(), k = read();

    memset(dp, 0xcf, sizeof(dp));

    for(int i = 1; i <= n; ++i) {
        while(ch = getchar()) {
            if(ch == '1' or ch == '0')
                break;
        }
        dp[i][i][ch - '0'] = 0;
    }
    
    for(int i = 0; i < (1 << k); ++i)
        New[i] = read(), W[i] = read();

    for(int i = 1; i < k; ++i)
        num[i] = i;

    for(int i = k; i <= n; ++i)
        num[i] = num[i - k + 1];
    
    for(int len = 1; len < n; ++len) {
        for(int l = 1; l + len <= n; ++l) {
            int r = l + len;
            int ll = num[r - l + 1];
            if(ll == 1)
                ll = k;
            for(int v = 0; v < (1 << ll); ++v) {
                for(int j = 1; j < ll; ++j) {
                    int kk = l;
                    while(++kk <= r and num[r - kk + 1] != j);
                    kk -= k - 1;
                    while((kk = kk + k - 1) <= r) {
                        if(ll != k) {
                            dp[l][r][v] = max(dp[l][r][v], dp[l][kk - 1][v >> j] + dp[kk][r][v & ((1 << j) - 1)]);
                            ans = max(ans, dp[l][r][v]);
                        }
                        else {
                            dp[l][r][New[v]] = max(dp[l][r][New[v]], dp[l][kk - 1][v >> j] + dp[kk][r][v & ((1 << j) - 1)] + W[v]);
                            ans = max(ans, dp[l][r][New[v]]);
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < (1 << k); ++i)
        ans = max(ans, dp[1][n][i]);

    printf("%lld\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
