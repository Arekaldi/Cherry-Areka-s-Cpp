#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n = 1e5, m = 1e5;
signed main() {

    #define Areka
    #ifdef Areka
        // freopen("", "r", stdin);
        freopen("1.txt", "w", stdout);
    #endif

    cout << n << " " << m << endl;
    
    for(int i = 1; i <= n; ++i)
        cout << m << endl;

    for(int i = 1; i <= m; ++i)
        cout << 1 << " " << n << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
