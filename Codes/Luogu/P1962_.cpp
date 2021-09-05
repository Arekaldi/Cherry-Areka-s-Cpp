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

int n;
const int p = 1e9 + 7;

struct Martix {
    int f[3][3];

    Martix() {
        memset(f, 0, sizeof(f));
    }

    friend Martix operator * (const Martix &a, const Martix &b) {
        Martix c;
        for(int i = 1; i <= 2; ++i) 
            for(int j = 1; j <= 2; ++j) 
                for(int k = 1; k <= 2; ++k)
                    c.f[i][j] += a.f[i][k] * b.f[k][j], c.f[i][j] %= p;
        return c;
    }
}A, B;

void init() {
    A.f[1][1] = A.f[1][2] = A.f[2][1] = 1;
    B.f[1][1] = B.f[1][2] = 1;
}

void Get_xr(int b) {
    while(b) {
        if(b & 1) B = B * A;
        A = A * A;
        b >>= 1;
    }
}

signed main() {
    n = read();
    init();
    
    if(n <= 2) 
        puts("1");

    else
        Get_xr(n - 2), printf("%lld\n", B.f[1][1] % p);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
