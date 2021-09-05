#include <bits/stdc++.h>

using namespace std;

#define int __int128

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, Mod, ans, p1, a1, flag;

inline int Mul(int n, int m, int p) {
    int res = 0;
    while(m) {
        if(m & 1)
            res = (res + n) % p;
        m >>= 1;
        n = (n + n) % p;
    }
    return res;
}

inline int Exgcd(int a, int b, int &x, int &y) {
    if(!b) {
        x = 1, y = 0;
        return a;
    }
    int d = Exgcd(b, a % b, x, y), c = x;
    x = y, y = c - (a / b) * y;
    return d;
}

signed main() {
    n = read(), Mod = read(), ans = read();
    for(int i = 2; i <= n; ++i) {
        p1 = read(), a1 = read();
        int x, y, c = (a1 - ans % p1 + p1) % p1, d = Exgcd(Mod, p1, x, y);
        if(c % d == 0) {
            ans += Mul(x, c / d, p1 / d) * Mod;
            Mod *= p1 / d;
            ans = (ans % Mod + Mod) % Mod;
        }
        else {
            puts("-1");
            goto Areka;
        }
    }

    cout << (long long)(ans % Mod) << endl;
    
    Areka:;
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
