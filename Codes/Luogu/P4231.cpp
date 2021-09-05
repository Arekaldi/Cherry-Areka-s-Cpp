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

const int maxn = 1e7 + 1;

int a[maxn], b[maxn], c[maxn];

signed main() {
    int n = read(), m = read();

    for(int i = 1; i <= m; ++i) {
        int l = read(), r = read(), s = read(), e = read();
        int d = (e - s) / (r - l);
        b[l] += s, b[l + 1] += d - s, b[r + 1] -= e + d, b[r + 2] += e;
    }

    for(int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + b[i];

    for(int i = 1; i <= n; ++i)
        c[i] = c[i - 1] + a[i];

    swap(b, c);

    
    int res, ans;
    res = ans = b[1];
    for(int i = 2; i <= n; ++i)
        res ^= b[i], ans = max(ans, b[i]);
    
    cout << res << " " << ans << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
