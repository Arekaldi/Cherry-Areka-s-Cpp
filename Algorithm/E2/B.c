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

int dp[1010][1010], num[1010][1010];
int n, m;

int max2(int a, int b) {
    return a > b? a : b;
}

signed main() {
    int T = read();
    while(T--) {
        n = read(), m = read();
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                num[i][j] = read();
        dp[1][1] = num[1][1];
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(i == 1 && j != 1)
                    dp[i][j] = dp[i][j - 1] + num[i][j];
                else if(j == 1 && i != 1)
                    dp[i][j] = dp[i - 1][j] + num[i][j];
                else
                    dp[i][j] = max2(dp[i - 1][j], dp[i][j - 1]) + num[i][j];
            }
        }
        printf("%lld\n", dp[n][m]);
    }
}