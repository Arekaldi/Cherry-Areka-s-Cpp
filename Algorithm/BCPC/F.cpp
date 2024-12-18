#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>

#define int long long

int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
        (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

const int MOD = 1e9 + 7;
const int Maxn = 2e5 + 10;

int dp[Maxn][4], a[Maxn], n;

int countSubsequences() {
    dp[1][a[1] % 4] = 1;
    
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < 4; ++j) {
            dp[i][j] = dp[i - 1][j];
            dp[i][(j * a[i]) % 4] = (dp[i][(j * a[i]) % 4] + dp[i - 1][j]) % MOD;
        }
        dp[i][a[i] % 4] = (dp[i][a[i] % 4] + 1) % MOD;
    }
    
    return dp[n][0];
}

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    printf("%lld\n", countSubsequences());
    return 0;
}