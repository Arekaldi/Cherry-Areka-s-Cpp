#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch = getchar();
    while(ch < '0' or ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' and ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
   return x * f;
}

inline int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

int n, ans;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        int x = read();
        ans = gcd(abs(x), ans);
    }
    
    printf("%d\n", ans);
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
