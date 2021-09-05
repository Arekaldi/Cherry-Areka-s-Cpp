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
int a[maxn], b[maxn], n;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read();
        b[i] = a[i] - a[i - 1];
    }

    int f1 = 0, f2 = 0;
    for(int i = 2; i <= n; ++i) {
        if(b[i] > 0)
            f1 += b[i];
        else
            f2 += -b[i];
    }

    printf("%lld\n%lld\n", max(f1, f2), abs(f1 - f2) + 1);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
