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
        // freopen("trees.in", "r", stdin);
        freopen("trees.in", "w", stdout);
    #endif
    srand(time(0));
    int n = 1e3, K = rand() % n + 1;
    cout << n << " " << K << endl;
    for(int i = 1; i <= n; ++i)
        printf("%d\n", rand() << 14 | rand());
    return 0;
}
