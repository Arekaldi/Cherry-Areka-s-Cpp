#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef long long i64;

i64 read(void) {
    i64 x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(i64 x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

i64 sum[10000100];

const i64 mod = 1000000007;

int main() {
    i64 n = read(), k = read(), l = read(), r = read();
    sum[0] = 1ll;
    for(int i = 1; i < l; ++i)
        sum[i] = 1ll;
    int ll = l - r, rr = 0;
    i64 cnt = 2ll;
    for(int i = l; i <= n + 10; ++i) {
        sum[i] = cnt % mod;
        ll++, rr++;
        if(ll > 0) {
            sum[ll - 1] %= mod;
            i64 ii = (sum[ll - 1] * k) % mod;
            cnt = (cnt - ii + mod) % mod;
        }
        sum[rr] %= mod;
        i64 ii = (sum[rr] * k) % mod;
        cnt = (cnt + ii) % mod;
    }
    i64 summ = 0;
    for(int i = 0; i <= n; ++i)
        summ = (summ + sum[i]) % mod;
    write(summ);
    return 0;
}