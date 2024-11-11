#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int n, V;

int w[1010], v[1010];

int dp[2][1010];

int max(int a, int b) {
    return a > b? a : b;
}

int main() {
    int T = read();
    while(T--) {
        n = read(), V = read();
        for(int i = 1; i <= n; i++)
            w[i] = read(), v[i] = read();
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= V; ++j) {
                if(j < v[i])
                    dp[i & 1][j] = dp[(i - 1) & 1][j];
                else
                    dp[i & 1][j] = max(dp[(i - 1) & 1][j], dp[(i - 1) & 1][j - v[i]] + w[i]);
            }
        }
        int ans = 0;
        for(int i = 0; i <= V; ++i)
            ans = max(ans, dp[n & 1][i]);
        write(ans), putchar('\n');
    }
}