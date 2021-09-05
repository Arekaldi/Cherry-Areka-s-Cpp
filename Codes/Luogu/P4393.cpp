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

int n, ans, lst;
int a[maxn];

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    for(int i = 2; i <= n; ++i)
        ans += max(a[i - 1], a[i]);
    
    cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
