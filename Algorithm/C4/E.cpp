#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define int long long

using namespace std;

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

int f[301][301];
int n, m, q;

int min2(int a, int b) {
    return a < b ? a : b;
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            f[i][j] = (1ll << 50);
    for(int i = 1; i <= n; ++i)
        f[i][i] = 0;
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read();
        f[u][v] = min2(f[u][v], w);
    }
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                f[i][j] = min2(f[i][j], f[i][k] + f[k][j]);
    q = read();
    for(int i = 1; i <= q; ++i) {
        int u = read(), v = read();
        if(f[u][v] < (1ll << 50))
            write(f[u][v]), putchar('\n');
        else
            puts("-1");
    }
    return 0;
}