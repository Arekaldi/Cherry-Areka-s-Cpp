#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long read(void) {
    long long x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

#define int long long

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

int dp[1000010][2];
int n, m, k;
int barrier[1000010];
const int mod = 998244353;

signed main() {
    n = read(), m = read(), k = read();
    for(int i = 1; i <= m; i++) {
        int x = read();
        barrier[x] = 1;
    }
    // dp i_0 for case 1 ~ k - 1
    // dp i_1 for case k
    dp[1][0] = k - 1, dp[1][1] = barrier[1] ? 0 : 1;
    for(int i = 2; i <= n; ++i) {
        dp[i][0] = (dp[i - 1][0] * (k - 2)) % mod;
        dp[i][0] = (dp[i][0] + dp[i - 1][1] * (k - 1)) % mod;
        if(barrier[i])
            dp[i][1] = 0;
        else
            dp[i][1] = (dp[i - 1][0]) % mod;
    }
    int ans = (dp[n][0] + dp[n][1]) % mod;
    write(ans);
    return 0;
}