#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define int long long

int C[4000][4000];

const int mod = 1e9 + 7;

int pow(int x, int n) {
    int res = 1;
    while(n) {
        if(n & 1)
            res = (res * x) % mod;
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}

signed main() {
    int t;
    scanf("%lld", &t);
    C[0][0] = 1;
    C[0][1] = C[1][1] = 1;
    for(int i = 2; i <= 3000; ++i) {
        C[0][i] = 1,  C[1][i] = i, C[i - 1][i] = i, C[i][i] = 1;
        for(int j = 2; j < i - 1; ++j) {
            C[j][i] = (C[j - 1][i - 1] + C[j][i - 1]) % mod;
        }
    }
    while(t--) {
        int n, m, k;
        scanf("%lld%lld%lld", &n, &m, &k);
        // printf("%lld\n", C[n][m]);
        if(m - (k << 1) < 0 || n - k < 0) {
            printf("0\n");
            continue;
        }
        int a = pow(2, m - k * 2) % mod;
        a = (a * C[k][n]) % mod;
        a = (a * C[m - k * 2][n - k]) % mod;
        printf("%lld\n", a);
    }
    return 0;
}