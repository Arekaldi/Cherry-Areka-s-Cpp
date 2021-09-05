#include <bits/stdc++.h>

using namespace std;

#define int long long

const int maxn = 1e6 + 1, p = 1e9 + 7;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x * 10 + (ch ^ 48)) % p);
    return x * f;
}

int n, m;
int a[maxn];

int ans[maxn], tot;

signed main() {
    n = read(), m = read();
    for(int i = 0; i <= n; ++i)
        a[i] = read();
    
    for(int i = 1; i <= m; ++i) {
        int res = a[n];
        for(int j = n - 1; j >= 0; --j)
            res = (res * i + a[j]) % p;
        if(res == 0)
            ans[++tot] = i;
    }
    
    printf("%d\n", tot);
    for(int i = 1; i <= tot; ++i)
        printf("%d\n", ans[i]);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}