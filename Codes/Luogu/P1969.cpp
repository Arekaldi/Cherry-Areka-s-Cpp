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

const int maxn = 1e5 + 1;

int h[maxn];
int res, x, n;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        h[i] = read();
        if(h[i] >= x)
            x = h[i];
        else
            res += x - h[i], x = h[i];
    }
    cout << res + x;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
