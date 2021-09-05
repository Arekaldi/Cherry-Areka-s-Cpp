/*
    'Cause we were both young when I have saw U
*/

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

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

signed main() {
    int T = read();
    while(T--) {
        int res = 0;
        int a0 = read(), a1 = read(), b0 = read(), b1 = read();
        for(int i = 0; i <= b1; ++i) {
            if(gcd(i, a0) == a1 and ((i * b0) / gcd(i, b0)) == b1)
                res++;
        }
        printf("%lld\n", res);
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}