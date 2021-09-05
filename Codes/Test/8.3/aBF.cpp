#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int K, A, B, ans;

int dp[600][600][600];

inline void Dfs(int nk, int na, int nm) {
    if(nk < 0)
        return;
    if(nk == 0) {
        ans = max(ans, na);
        return;
    }
    if(dp[nk][na][nm])
        return;
    Dfs(nk - 1, na + 1, nm);
    dp[nk - 1][na + 1][nm] = 1;
    if(na >= A) {
        Dfs(nk - 1, na - A, nm + 1);
        dp[nk - 1][na - A][nm + 1] = 1;
    }
    if(nm >= 1) {
        Dfs(nk - 1, na + B, nm - 1);
        dp[nk - 1][na + B][nm - 1] = 1;
    }
}

signed main() {
    K = read(), A = read(), B = read();
    
    Dfs(K, 1, 0);
    
    printf("%d\n", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
