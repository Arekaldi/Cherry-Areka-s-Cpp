#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

signed main() {
    #define Areka
    #ifdef Areka
        freopen("", "r", stdin);
        freopen("", "w", stdout);
    #endif
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
