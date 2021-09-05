#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int f[maxn][17];

signed main() {
    int n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        f[i][0] = read();

    int t = log(n) / log(2) + 1;
    for(int j = 1; j < t; ++j) {
        for(int i = 1; i + (1 << (j - 1)) <= n; ++i)
            f[i][j] = max(f[i + (1 << (j - 1))][j - 1], f[i][j - 1]);
    }
    
    for(int i = 1; i <= m; ++i) {
        int l = read(), r = read();
        int len = r - l + 1, ww = log(len) / log(2);
        printf("%d\n", max(f[l][ww], f[r - (1 << ww) + 1][ww]));
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
