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

int n, W, k;
int dp[5010][5010], f[5010][5010];
int w[5010], v[5010];

int main() {
    int T = read();
    while(T--) {
        n = read(), W = read(), k = read();
        for(int i = 1; i <= n; i++)
            w[i] = read(), v[i] = read();
        memset(dp, 0, sizeof(dp));
        memset(f, 0, sizeof(f));
        for(int i = 1; i <= n; ++i) {
            dp[i][0] = dp[i - 1][0] + v[i];
            f[i][0] = f[i - 1][0] + w[i];
            for(int j = 1; j <= k; ++j) {

            }
        }
    }
}