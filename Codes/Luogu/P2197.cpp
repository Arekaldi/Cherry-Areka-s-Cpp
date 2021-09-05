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
    int T = read();

    while(T--) {
        int n = read(), ans = read();
        for(int i = 2; i <= n; ++i) {
            int x = read();
            ans ^= x;
        }
        if(ans)
            puts("Yes");
        else
            puts("No");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
