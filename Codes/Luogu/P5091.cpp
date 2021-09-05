#include <bits/stdc++.h>

using namespace std;

#define int long long

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
    return b == 0 ? a : gcd(b, a % b);
}

int phi, prime[1000100]; 
int a, b, m;
inline void Get_Phi() {
    int n = m;
    phi = n;
    for(int i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            phi = phi / i * (i - 1);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1)
            phi = phi / n * (n - 1);
}

inline int get_b_mod() {
    register int x = 0, f = 1;
    register char ch = getchar();
    while(ch < '0' or ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' and ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        if(x >= phi) {x %= phi; f = 0;}
        ch = getchar();
    }
    return f ? x : x + phi;
}

int get_xr(int a, int b, int p) {
    int ans = 1;
    for(; b; b >>= 1, a = a * a % p)
        if(b & 1) ans = ans * a % p;
    return ans % p;
}

signed main() {
    a = read(), m = read();
    Get_Phi();
    b = get_b_mod();
    
    printf("%lld\n", get_xr(a, b, m));
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
