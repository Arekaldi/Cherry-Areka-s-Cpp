#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define int long long

int isdigit2(char ch) {
    return ch >= '0' && ch <= '9';
}

int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit2(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit2(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
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

int T, n, w;
int dp[1000010][2], a[1000010], sum[1000010];

int max2(int a, int b) {
    return a > b? a : b;
}

signed main() {
    T = read();
    while(T--) {
        n = read(), w = read();
        for(int i = 1; i <= n; i++)
            a[i] = read();
        dp[1][0] = a[1], dp[1][1] = a[1] - w;
        for(int i = 2; i <= n; ++i) {
            
        }
        // dp[1][1] = a[1], dp[2][2] = a[1] + a[2], dp[2][1] = dp[2][2] - w;
        // int ans = -1e18;
        // for(int i = 2; i <= n << 1; ++i) {
        //     int maxx = -1e18;
        //     for(int j = 2; j <= i; ++j) {
        //         if(i + 2 < 2 * j) {
        //             dp[i][j] = -1e9;
        //             continue;
        //         }
        //         dp[i][j] = dp[i - j + 1][j - 1] + a[i], maxx = max2(maxx, dp[i][j]);
        //     }
        //     dp[i][1] = maxx - w;
        //     if(i > n)
        //         ans = max2(ans, maxx);
        // }
        // for(int i = 3; i <= n << 1; i += 2) {

        // }
        // for(int i = 1; i <= n; ++i) {
        //     for(int j = 1; j <= i; ++j)
        //         printf("%lld ", dp[i][j]);
        //     printf("\n");
        // }
        // printf("%lld\n", ans);
    }
}