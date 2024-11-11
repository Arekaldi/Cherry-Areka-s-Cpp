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

int dp[100010];
const int mod = 998244353;

signed main() {
    int T = read();
    while(T--) {
        int n = read();
        if(n & 1)
            puts("0");
        else {
            if(dp[n]) {
                write(dp[n]);
                putchar('\n');
            }
            else {
                int p = 2;
                dp[0] = 1, dp[2] = 3;
                for(int i = 4; i <= n; i += 2) {
                    dp[i] = (dp[i - 2] << 1) % mod;
                    dp[i] = (dp[i - 2] + dp[i]) % mod;
                    dp[i] = (dp[i] + dp[i - 4]) % mod;
                    dp[i] = (dp[i] + dp[i - 4]) % mod;
                    // dp[i] = dp[i - 2] * 3 + dp[i - 4] * 2;
                }
                write(dp[n]);
                putchar('\n');
            }
        }
    }
}