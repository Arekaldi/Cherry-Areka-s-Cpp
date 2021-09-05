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

const int maxn = 1e6 + 1;

int n, m, ans, a[maxn];

vector <int> v1, v2;

inline void Dfs(int l, int r, int now, int opt) {
    if(now > m)
        return;
    if(l > r) {
        if(opt)
            v1.push_back(now);
        else
            v2.push_back(now);
    }
    else {
        Dfs(l + 1, r, now + a[l], opt);
        Dfs(l + 1, r, now, opt);
    }
}

signed main() {
    n = read(), m = read();
    
    for(int i = 1; i <= n; ++i)
        a[i] = read();

    Dfs(1, (n >> 1), 0, 1);
    Dfs((n >> 1) + 1, n, 0, 0);

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    for(auto it = v2.begin(); it != v2.end(); ++it)
        ans += upper_bound(v1.begin(), v1.end(),
            m - *it) - v1.begin();
    
    cout << ans;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
