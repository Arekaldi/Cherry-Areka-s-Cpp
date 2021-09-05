#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = (1 << 10) + 1, maxn = 1e2 + 1;

inline int Count(int n) {
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
    return n;
}

int n, m, cnt;
int dp[2][maxm][maxm], st[maxm];
int Map[maxn];

inline bool Check(int x) {
    return (x & (x >> 1)) || (x & (x >> 2));
}

inline bool Judge(int i, int x) {
    return Map[i] & st[x];
}

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) {
        string ss;
        getline(cin, ss);
        for(int j = 0; j < m; ++j) {
            char ch = ss[j];
            Map[i] = ch == 'P' ? (Map[i] << 1) : ((Map[i] << 1) | 1);
        }
    }
    
    for(int i = 0; i < (1 << m); ++i)
        if(!Check(i))
            st[++cnt] = i;

    for(int i = 1; i <= cnt; ++i)
        if(!Judge(1, i))
            dp[0][i][0] = Count(st[i]);
    
    for(int i = 1; i <= cnt; ++i) 
        for(int j = 1; j <= cnt; ++j)
            if(!Judge(2, i) && !(st[j] & st[i]))
                dp[1][i][j] = max(dp[1][i][j], dp[0][j][0] + Count(st[i]));

    int t = 0;
    for(int i = 3; i <= n; ++i, t ^= 1)
        for(int j = 1; j <= cnt; ++j)
            if(!Judge(i, j))
                for(int k = 1; k <= cnt; ++k)
                    if(!Judge(i - 1, k) and !(st[j] & st[k]))
                        for(int l = 1; l <= cnt; ++l)
                            if(!Judge(i - 2, l) and !(st[j] & st[l]) and !(st[k] & st[l]))
                                dp[t][j][k] = max(dp[t][j][k], dp[t ^ 1][k][l] + Count(st[j]));

    int ans = -1;

    for(int i = 1; i <= cnt; ++i)
        if(!Judge(n, i))
            for(int j = 1; j <= cnt; ++j)
                if(!Judge(n - 1, j) and !(st[i] & st[j]))
                    ans = max(ans, dp[n & 1 ^ 1][i][j]);

    printf("%d\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

