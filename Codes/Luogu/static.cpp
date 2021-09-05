#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

static int a[] = {0, 1, 2, 3, 4};

signed main() {
    a[1] = 2;
    for(int i = 1; i <= 4; ++i)
        cout << a[i];
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
