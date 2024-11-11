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

int n, vSum;
int v[510], w[510];
int f[2][250010];

int min2(int a, int b) {
    return a > b ? b : a;
}

signed main() {
    n = read(), vSum = read();
    for(int i = 1; i <= n; ++i)
        v[i] = read(), w[i] = read();
    for(int j = 1; j <= 250000; ++j)
        f[0][j] = 1e12 + 1;
    for(int i = 1; i <= n; ++i) {
        f[i & 1][0] = 0;
        for(int j = 1; j <= 250000; ++j) {
            if(j < w[i])
                f[i & 1][j] = f[(i & 1) ^ 1][j];
            else
                f[i & 1][j] = min2(f[(i & 1) ^ 1][j], f[(i & 1) ^ 1][j - w[i]] + v[i]);
        }
    }
    int ans = 0;
    for(int j = 250000; j >= 0; --j)
        if(f[n & 1][j] <= vSum) {
            ans = j;
            break;
        }
    write(ans);
    return 0;
}