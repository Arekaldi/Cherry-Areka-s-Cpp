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

long long A[210][210], B[210][210];
long long C[210][210], ans[210][210], res[210][210];

const long long mod = 1e9 + 7;

void mul(long long n, long long m) {
    memset(ans, 0, sizeof(ans));
    for(int i = 1; i <= n; ++i)
        ans[i][i] = 1;
    while(m) {
        if(m & 1) {
            memset(res, 0, sizeof(res));
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= n; ++j)
                    for(int k = 1; k <= n; ++k) {
                        res[i][j] %= mod;
                        res[i][j] = (res[i][j] + ans[i][k] * C[k][j]) % mod;
                    }
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= n; ++j)
                    ans[i][j] = res[i][j];
        }

        memset(res, 0, sizeof(res));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                for(int k = 1; k <= n; ++k)
                    res[i][j] = (res[i][j] + C[i][k] * C[k][j]) % mod;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                C[i][j] = res[i][j];
        m >>= 1ll;
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            write(ans[i][j]), putchar(' ');
        putchar('\n');
    }
}

int main() {
    int T = read();
    while(T--) {
        long long n = read(), m = read();
        memset(C, 0, sizeof(C));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                A[i][j] = read();
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                B[i][j] = read();
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                for(int k = 1; k <= n; ++k)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
        mul(n, m);
    }
    return 0;
}