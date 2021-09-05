#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e3 + 1, maxm = 2e2 + 1, mod = 1e9 + 7;

int n, m, k;
int f[2][maxm][maxn][2];

char a[maxn], b[maxm];

signed main() {
    n = read(), m = read(), k = read();
    cin >> (a + 1) >> (b + 1);

    f[0][0][0][0] = f[1][0][0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        int t = i & 1;
        for(int j = 1; j <= m; ++j) {
            for(int p = 1; p <= k; ++p) {
                    f[t][j][p][0] = f[t ^ 1][j][p][0] + f[t ^ 1][j][p][1];
                if(a[i] == b[j])
                    f[t][j][p][1] = (f[t ^ 1][j - 1][p - 1][0] + f[t ^ 1][j - 1][p - 1][1] + f[t ^ 1][j - 1][p][1]) % mod;
                else
                    f[t][j][p][1] = 0;
            }
        }
    }
    
    printf("%lld\n", (f[n & 1][m][k][0] + f[n & 1][m][k][1]) % mod);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
