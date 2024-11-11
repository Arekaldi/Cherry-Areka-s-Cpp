#include <assert.h>
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

int n, pp;
const int mod = 998244353ll;

int pow2(int a, int n) {
    int res = 1ll;
    while(n) {
        if(n & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return res % mod;
}

signed main() {
    n = read(), pp = read();
    int inv_100 = pow2(100, mod - 2) % mod; // /100
    int p = (pp * inv_100) % mod; // pp / 100
    int a1 = (1 - p + mod) % mod; // 1 - p
    int a2 = pow2(a1, n + 1); // (1 - p) ^ n
    int q = (1 - a2 + mod) % mod;
    int inv_q = pow2(q, mod - 2) % mod; // 1 / q
    int r = (inv_q * p) % mod;

    printf("%lld\n", r);
    return 0;
}   