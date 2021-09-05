#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int n, m, v, res;
int a[maxn];
int opt[maxn], l[maxn], r[maxn];

signed main() {
    #define Areka
    #ifdef Areka
        freopen("birthday.in", "r", stdin);
        freopen("birthday.out", "w", stdout);
    #endif
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    for(int i = 1; i <= m; ++i) {
        opt[i] = read(), l[i] = read(), r[i] = read();
        res += (opt[i] == 1);
    }
    
    if(res == 0)
        return 0;
    
    for(int i = 1; i <= n; ++i) {
        if(opt[i] == 1) {
            int sum = 0;
            for(int j = l[i]; j <= r[i]; ++j)
                sum += a[j];
            puts(sum & 1 ? "No" : "Yes");
        }
        if(opt[i] == 2)
            for(int j = l[i]; j <= r[i]; ++j) {
                a[j] = ((a[j] * a[j]) % v * a[j] % v) % v;
            }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
