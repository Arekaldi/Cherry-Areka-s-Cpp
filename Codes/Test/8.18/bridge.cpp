#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, m;

const int maxn = 1e2 + 1;

int f[maxn][maxn][2];

signed main() {
    #define Areka
    #ifdef Areka
        freopen("bridge.in", "r", stdin);
        freopen("bridge.out", "w", stdout);
    #endif
    n = read(), m = read();
    
    f[1][1][0] = f[1][1][1] = 1;
    
    for(int i = 1; i <= n; ++i) {
        f[i + 1][1][0] += f[i][0][1] + f[i][0][0];
        f[i + 1][1][1] += f[i][0][1] + f[i][0][0];
        for(int j = 1; j <= min((m >> 1), i); ++j) {
            f[i + 1][j + 1][1] += f[i][j][1];
            f[i + 1][j - 1][1] += f[i][j][1];
            f[i + 1][j + 1][0] += f[i][j][0];
            f[i + 1][j - 1][0] += f[i][j][0];
        }
    }

    cout << f[n][0][1] + f[n][0][0] << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
