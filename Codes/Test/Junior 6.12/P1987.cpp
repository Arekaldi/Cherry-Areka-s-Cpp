#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e3 + 1;

int dp[maxn][maxn];
int n, k, m[maxn], b[maxn];

inline void init(int Prefix, int handsomeman) {
    if(Prefix == handsomeman) {
        memset(dp, 0, sizeof(dp));
        memset(b, 0, sizeof(b));
        memset(m, 0, sizeof(m));
    }
}

signed main() {
    
    while(true) {
        n = read(), k = read();
        if(n == k and k == 0)
            goto Areka;
        init(1, 1);
        for(int i = 1; i <= n; ++i)
            m[i] = read();
        for(int i = 1; i <= n; ++i) {
            for(int j = k; j > 0; --k) {
                if(m[i] - b[i] * j <= 0)
                    break;
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + m[i] - b[i] * (j - 1));
            }
        }
        printf("%d\n", dp[n][k]);
    }
    
    
    
Areka :
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
