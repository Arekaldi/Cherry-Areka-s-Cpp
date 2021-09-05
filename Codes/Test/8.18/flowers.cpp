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

int a, b, n;

inline int Ct(int x, int y) {
    int res = 0;
    for(int i = 1; i <= x; ++i)
        if((b + a * i) % y < y / 2)
            i = min(x, i + (y / 2 - (b + a * i) % y - 1) / a);
        else {
            int c = min(x, i + (y - (b + a * i) % y - 1) / a);
            res += c + 1 - i;
            i = c;
        }
    return res;
}

signed main() {
    #define Areka
    #ifdef Areka
        freopen("flowers.in", "r", stdin);
        freopen("flowers.out", "w", stdout);
    #endif
    int T = read();
    while(T--) {
        int res = 0;
        a = read(), b = read(), c = read();
        for(int i = 2; i <= 2 * b + 2 * a * n; i *= 2) {
            if(n / i)
                res += n / i + Ct(i, i);
            res += Ct(n % i, i);
        }
        printf("%lld\n", res)
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
