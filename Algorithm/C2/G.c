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

i64 sum[1000010];

const i64 mod = 1000000007;

int main() {
    int n = read(), k = read(), l = read(), r = read();   
    sum[0] = 1;
    for(int i = l; i <= n; ++i) {
        i64 tot = 0;
        for(int j = i - r < 0 ? 0 : i - r; j <= i - l; ++j)
            tot = (tot + sum[j] * k) % mod;
        write(tot); putchar(' ');
        sum[i] = tot;
    }
    printf("%lld\n", sum[n]);
    return 0;
}