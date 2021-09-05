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

const int maxn = 2e3 + 1, Mod = 1e9 + 7;

int f[maxn][maxn];
int n, s, t;

signed main() {
    n = read(), s = read(), t = read();
    
    f[1][1] = 1;
    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            if(i == s or i == t)
                // 填 s / t 时要特判，加入连续段和开心段不需要费用
                f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
            else
                f[i][j] = f[i - 1][j + 1] * j + f[i - 1][j - 1] * (j - ((i > s ? 1 : 0) + (i > t ? 1 : 0)));
            f[i][j] %= Mod;
        }

    printf("%lld\n", f[n][1]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
