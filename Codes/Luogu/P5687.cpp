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

const int maxn = 3e5 + 1;

int a[maxn], b[maxn];
int n, m;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    for(int i = 1; i <= m; ++i)
        b[i] = read();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    int ans = 0, c1 = 1, c2 = 1;
    ans += a[1] * (m - c2) + b[1] * (n - c1);
    int p1 = 2, p2 = 2;
    while(p1 <= n and p2 <= m) {
        if(a[p1] <= b[p2])
            ans += a[p1++] * (m - c2), c1++;
        else
            ans += b[p2++] * (n - c1), c2++;
    }
    
    printf("%lld\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
