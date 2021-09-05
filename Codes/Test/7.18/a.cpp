#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

inline int Get_d(int x) {
    int ans = 0;
    for(int i = 1; i <= x; ++i)
        if(x % i == 0)
            ans++;
    return ans;
}

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

inline int f(int x) {
    int ans = 0;
    for(int i = 1; i <= x; ++i) {
        if(x % i == 0)
            ans += Get_d(i);
    }
    return ans;
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif

    int n = read(), ans = 0;

    // for(int i = 1; i <= n; ++i) {
    //     for(int j = 1; j <= n; ++j) {
    //         int p = f(gcd(i, j)), o = f(lcm(i, j));
    //         ans += p * o;
    //     }
    // }
    
    // cout << ans << endl;

    int toi = pow(n, 0.34);
    while(toi * toi * toi > n)
        toi--;
    
    for(int i = 1; i <= toi; ++i)
        for(int j = i; j <= sqrt(n / i); ++j)
            ans += (n / i / j) - j + 1;

    ans *= 6;
    
    for(int i = 1; i * i <= n; ++i)
        ans -= (n / i / i) * 3;
    
    ans -= (toi * 2);

    printf("%llu\n", ans * ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
