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

void write(long long x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

#define int long long

int n;
int dp[35];

signed main() {
    n = read();
    dp[1] = 1;
    for(int i = 2; i <= n; ++i) {
        int sum = 0;
        for(int j = 1; j < i; ++j)
            sum += dp[j] * dp[i - j];
        dp[i] = sum;
    }
    printf("n  : P(n)\n");
    for(int i = 1; i <= n; ++i)
        printf("%-3lld: %lld\n", i, dp[i]);
    return 0;
}