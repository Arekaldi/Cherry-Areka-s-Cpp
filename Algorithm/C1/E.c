#include <stdio.h>

#define int long long

const int mod = 10007ll;

int m, n, q;
int a[30100], b[30100];

int pow(int x, int n) {
    int res = 1ll;
    while (n > 0) {
        if(n & 1ll)
            res = (res * x) % mod;
        x = (x * x) % mod;
        n >>= 1ll;
    }
    return res % mod;
}

int main() {
    scanf("%lld", &n);
    for(int i = 0; i <= n; ++i)
        scanf("%lld", &a[i]);
    scanf("%lld", &m);
    for(int i = 0; i <= m; ++i)
        scanf("%lld", &b[i]);
    scanf("%lld", &q);
    for(int i = 1; i <= q; ++i) {
        int x, y;
        scanf("%lld%lld", &x, &y);
        int res1 = 0, res2 = 0;
        int resx = 1;
        for(int j = 0; j <= n; ++j) {
            int xx = (a[j] * resx) % mod;
            resx = (resx * x) % mod;
            res1 = (res1 + xx) % mod;
        }
        int resy = 1;
        for(int j = 0; j <= m; ++j) {
            int yy = (b[j] * resy) % mod;
            resy = (resy * y) % mod;
            res2 = (res2 + yy) % mod;
        }
        printf("%lld\n", (res1 * res2) % mod);
    }
    return 0;
}