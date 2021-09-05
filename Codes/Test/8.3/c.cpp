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

int a, b, k;

inline int Gt(int x) {
    return (b / a + 1) * ((x + 2) * (x + 1) >> 1);
}

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
    #endif

    a = read(), b = read(), k = read();

    if(a > b)
        swap(a, b);
    
    int up = a * b - a - b;
    int dn = up % b;

    int nk = ((a - 1) * (b - 1) >> 1) - k + 1;

    

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
