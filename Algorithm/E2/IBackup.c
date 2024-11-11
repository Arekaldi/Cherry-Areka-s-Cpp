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

int n, p;
const int mod = 998244353;

int pow(int a, int n) {
    int res = 1;
    while(n) {
        if(n & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return res % mod;
}

const int inv_100 = 828542813;

signed main() {
    n = read(), p = read();
    int a1 = (p * inv_100) % mod; // pp / 100
    int a2 = (1 - a1 + mod) % mod;
    int a3 = pow(a2, n - 1);
    int a4 = (a3 * a1) % mod;
    int a5 = (1 - a4 + mod) % mod;
    int a6 = (1 - a1 + mod) % mod;
    int a7 = (a5 * a6) % mod;
    int a8 = (1 - a7 + mod) % mod;
    int inv_a8 = pow(a8, mod - 2); // q
    int r = (a1 * inv_a8) % mod;
    printf("%lld\n", r);
    return 0;
}