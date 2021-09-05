#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e3 + 1;

int f[maxn];

int n, m;

signed main() {
    n = read(), m = read();
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}