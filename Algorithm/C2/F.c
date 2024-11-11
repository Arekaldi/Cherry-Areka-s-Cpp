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

int nextRand() {
    static unsigned int rnd_num = 0x80000001;
    static int mod = 1e5 + 3;

    rnd_num ^= rnd_num >> 10;
    rnd_num ^= rnd_num << 9;
    rnd_num ^= rnd_num >> 25;
    return rnd_num % mod;
}

i64 a[5000010];
i64 t[100010], m[100010];

int main() {
    int T = read();
    while(T--) {
        int n = read();
        memset(t, 0, sizeof(t));
        memset(m, 0, sizeof(m));
        for(int i = 1; i <= n; ++i)
            a[i] = nextRand(), t[a[i]]++;
            // a[i] = read(), t[a[i]]++;
        for(int i = 0; i < 100010; ++i)
            m[i] = m[i - 1] + t[i];
        i64 ans = 0;
        for(int i = 1; i <= n; ++i)
            ans += ((1ll + m[a[i] - 1]) * a[i]);
        write(ans), putchar('\n');
    }
}