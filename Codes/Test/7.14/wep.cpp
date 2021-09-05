#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

vector <int> V;

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

signed main() {
    // #define Areka
    #ifdef Areka
        freopen("wep.in", "r", stdin);
        freopen("wep.out", "w", stdout);
    #endif
    
    int n = read();

    int ans = 0;

    for(int i = 1; i <= n; ++i) {
        int w = log2(i);
        int Up = (1 << (w + 1)) - 1;
        for(int j = i + 1; j <= Up; ++j) {
            if((i ^ j) == gcd(i, j)) {
                ans++;
            }
        }
    }

    // for(int i = 1; i <= n; ++i) {
    //     int j = 1;
    //     while(i * j <= n) {
    //         int w = i * j;
    //         if((i xor w) == i)
    //             ans++, cout << i << " " << w << endl;
    //         j++;
    //     }
    // }

    cout << ans << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
