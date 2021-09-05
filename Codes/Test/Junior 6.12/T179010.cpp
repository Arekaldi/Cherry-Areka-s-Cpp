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

int dp[maxn], a[maxn], n;

signed main() {
    n = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read(), dp[i] = 1;
    
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            if(a[j] < a[i])
                dp[i] = max(dp[j] + 1, dp[i]);
    
    int ans = 0;

    for(int i = 1; i <= n; ++i)
        ans = max(ans, dp[i]);
        
    cout << ans << endl;
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
