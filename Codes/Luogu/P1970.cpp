#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int n, ans, h[maxn], f[maxn][2];

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        h[i] = read();

    f[1][0] = f[1][1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(h[i] > h[i - 1])
            f[i][0] = f[i - 1][1] + 1;
        else
            f[i][0] = f[i - 1][0];
        if(h[i] < h[i - 1])
            f[i][1] = f[i - 1][0] + 1;
        else
            f[i][1] = f[i - 1][1];
    }

    cout << max(f[n][0], f[n][1]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
