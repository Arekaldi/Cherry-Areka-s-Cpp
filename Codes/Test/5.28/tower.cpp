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

const int Mod = 998244353;

int n, T;

inline int Pow(int a, int x) {
    if(x == 0)
        return 1;
    int sum = 1;
    while(x) {
        if(x & 1ll)
            sum *= a, sum %= Mod;
        x >>= 1;
        a *= a, a %= Mod;
    }
    return sum;
}

signed main() {
	freopen("tower.in", "r", stdin);
	freopen("tower.out", "w", stdout);
	
    T = read();
    
    while(T--)
        n = read(), printf("%lld\n", n <= 2 ? (n == 1 ? 1 : 3) : ((Pow(2, n - 2) % Mod) * ((n + 1) % Mod)) % Mod);
    
//    while(T--) 
//    	n = read(), printf("%d\n", dis[n]);
    return 0;
}

// (n + 2) * 2 ^ (n - 1)
// (n + 1) * 2 ^ (n - 2)