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

inline void exgcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    int z = x;
    x = y, y = z - y * (a / b);
}

inline void solve_one() {
    int a = read(), c = read(), d = read();
    int b, y;
    int gd = gcd(a, d);
    a /= gd, c /= gd, d /= gd;
    exgcd(a, d, b, y);
    int ans = ((b % d + d) % d);
    printf("%lld\n", ans == 0 ? d : ans);
}

inline void solve_two() {
    int a = read(), b = read(), d = read();
    int ans = a * b % d;
    printf("%lld\n", ans == 0 ? d : ans);
}

/*
    a * b - k * d = c
    k * d = a * b - c
*/
inline void solve_thr() {
    int a = read(), b = read(), c = read();
    int p = a * b - c;
    for(int i = 2; i * i < p; ++i) {
        if(p % i == 0) {
            printf("%lld\n", p);
            return;
        }
    }
    printf("%lld\n", p);
}

int n;

signed main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	
	// n = read();
	// for(int i = 1; i <= n; ++i) {
	// 	int opt = read();
	// 	if(opt == 1) solve_one();
	// 	if(opt == 2) solve_two();
	// 	if(opt == 3) solve_thr();
	// }
    
    return 0;
}