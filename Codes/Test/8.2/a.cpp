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

const int maxl = 1e3 + 1;

int n, a, t[maxl], f[maxl];
int res;

inline int C(int n, int m) {
    int res1 = 1, res2 = 1, res3 = 1;
    if(n < m)
        return 0;
    if(n == m)
        return 1;
    for(int i = n - m + 1; i <= n; ++i)
        res1 *= i;
    for(int i = 2; i <= m; ++i)
        res3 *= i;
    int res = (res1) / (res2 * res3);
    return res;
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; ++i) 
        t[a = read()]++;

    for(int i = 1; i <= 1000; ++i)
        f[i] = f[i - 1] + t[i];
    
    for(int i = 1; i <= 1000; ++i) {
        if(!t[i])
            continue;
        if(t[i] >= 2) {
            int Up = i << 1, Dn = i;
            Up = min(Up, 1001 * 1ll);
            int fk = f[Up - 1] - f[Dn];
            res += C(t[i], 2) * fk;
            if(t[i] >= 3)
                res += C(t[i], 3);
        }
        for(int j = i + 1; j <= 1000; ++j) {
            if(!t[j])
                continue;
            if(t[j] >= 2)
                res += C(t[j], 2) * t[i];
            int Up = i + j, Dn = j;
            Up = min(Up, 1001 * 1ll);
            int fk = f[Up - 1] - f[Dn];
            res += t[i] * t[j] * fk;
        }
    }

    printf("%lld\n", res);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
