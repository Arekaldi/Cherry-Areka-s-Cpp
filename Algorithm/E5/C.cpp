#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <assert.h>

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

const int maxn = 1e6 + 1;
const int mod = 998244353;

int n, m, l, r;
int a[maxn], dp[maxn], sum_dp[maxn], vis[maxn];

signed main() {
    n = read(), m = read();
    l = read(), r = read();
    dp[0] = 1, sum_dp[0] = 1;
    for(int i = 1; i <= m + 1; ++i)
        a[i] = i == m + 1 ? n : read(), vis[a[i]] = 1;
    std :: sort(a + 1, a + m + 2);
    for(int i = 1; i <= n; ++i) {
        int ll = i - r, rr = i - l;
        int temp = sum_dp[rr] - (ll <= 0 ? 0 : sum_dp[ll - 1]);
        if(vis[i])
            dp[i] = (temp + mod) % mod;
        else
            dp[i] = 0;
        sum_dp[i] = (sum_dp[i - 1] + dp[i]) % mod;
    }
    printf("%lld\n", dp[n]);
}