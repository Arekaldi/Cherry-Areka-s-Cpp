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

int K, A, B, res;

signed main() {

    #define Areka
    #ifdef Areka
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif

    K = read(), A = read(), B = read();
    if(B <= (A + 2) or K <= A + 1)
        res = K + 1;
    else {
        int x = A + 1;
        K -= x;
        res = B;
        int w = res;
        while(K > 0) {
            x = (w / A);
            if(K > (x << 1)) {
                K -= (x << 1);
                w %= A;
                w += x * B;
            }
            else {
                int p = (K >> 1);
                K = K - (p << 1);
                w += p * (B - A);
                break;
            }
        }
        res = w + K;
    }

    printf("%lld\n", res);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
