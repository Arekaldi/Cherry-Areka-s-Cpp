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

int f[maxn][maxn];

signed main() {
    // #define Areka
    #ifdef Areka
        freopen("bridge.in", "r", stdin);
        freopen("bridge.out", "w", stdout);
    #endif
    n = read(), m = read();
    
    f[1][1] = 1;
    for(int i = 2; i <= m; ++i)
        for(int j = 0; j <= n; ++j)
            f[i][j] += f[i - 1][j + 1] + ((j != 0) and f[i - 1][j - 1]);
    
    cout << f[m][0] * 2 << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
