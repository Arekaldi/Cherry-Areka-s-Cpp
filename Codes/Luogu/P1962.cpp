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
    // Martix() {}
    friend Martix operator * (const Martix &a, const Martix &b) {
        Martix c;
        for(int i = 1; i <= 2; ++i) 
            for(int j = 1; j <= 2; ++j) 
                for(int k = 1; k <= 2; ++k) 
                    c.f[i][j] += a.f[i][k] * b.f[k][j], c.f[i][j] %= p;
        return c;
    }
}Base, Ans;

void Get_xr(int b) {
    while(b) {
        if(b & 1) Ans = Ans * Base;
        // cout << "Ans\n";
        // for(int i = 1; i <= 2; ++i) {
        //     for(int j = 1; j <= 2; ++j) {
        //         cout << Ans.f[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        Base = Base * Base;
        // cout << "Base\n";
        // for(int i = 1; i <= 2; ++i) {
        //     for(int j = 1; j <= 2; ++j) {
        //         cout << Base.f[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        b >>= 1;
    }

}
// 1 1 2 3 5

signed main() {
    int n = read();

    Base.f[1][1] = Base.f[1][2] = Base.f[2][1] = 1;
    Ans.f[1][1] = Ans.f[1][2] = 1;

    if(n <= 2) {
        cout << 1 << endl;
        return 0;
    }

    Get_xr(n - 2);
    cout << Ans.f[1][1] % p << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
