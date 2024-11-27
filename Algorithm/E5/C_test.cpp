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
int a[maxn], dp[maxn], sum_dp[maxn];
int lst[maxn], nxt[maxn];
int vis[maxn], idx[maxn];

signed main() {
    n = read(), m = read();
    l = read(), r = read();
    dp[0] = 1, sum_dp[0] = 1;
    for(int i = 1; i <= m + 1; ++i)
        a[i] = i == m + 1 ? n : read(), vis[a[i]] = 1, idx[a[i]] = i;
    vis[0] = 1;
    int lastIndex = 0;
    for(int i = 1; i <= n; ++i) {
        if(vis[i])
            lastIndex = idx[i];
        lst[i] = lastIndex;
    }
    lastIndex = m + 1;
    for(int i = n - 1; i >= 0; --i) {
        if(vis[i])
            lastIndex = idx[i];
        nxt[i] = lastIndex;
    }
    std :: sort(a + 1, a + m + 2);
    for(int i = 1; i <= m + 1; ++i) {
        
    }
    printf("%lld\n", dp[m + 1]);
}