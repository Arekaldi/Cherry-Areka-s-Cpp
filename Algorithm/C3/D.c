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

int w[100010];
int dp[100010];

int max2(int a, int b) {
    return a > b? a : b;
}

signed main() {
    int t = read();
    while(t--) {
        int n = read();
        for(int i = 1; i <= n; ++i)
            w[i] = read();
        for(int i = 1; i <= n; ++i) {
            dp[i] = max2(dp[i - 1], dp[i - 2] + w[i]);
        }
        write(dp[n]);
        putchar('\n');
    }
}