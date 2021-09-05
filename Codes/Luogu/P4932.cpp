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

const int maxn = 1e7 + 1;

int n, a, b, c, d;
int X[maxn];

inline bool Judge(int x) {
    x = x ^ (x >> 1);
    x = x ^ (x >> 2);
    x = x ^ (x >> 4);
    x = x ^ (x >> 8);
    x = x ^ (x >> 16);
    return x & 1;
}

inline void print(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

signed main() {
    n = read(), a = read(), b = read(),
    c = read(), d = read(), X[0] = read();

    a %= d, b %= d, c %= d;

    for(int i = 1; i <= n; ++i)
        X[i] = (((a % d) * (X[i - 1] % d) * (X[i - 1] % d)) % d +
        (b * X[i - 1]) % d + c % d + d) % d;
    
    int ans1 = 0, ans2 = 0;
    for(int i = 1; i <= n; ++i)
            ans1 += Judge(X[i]), ans2 += !Judge(X[i]);

    print(ans1 * ans2);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}