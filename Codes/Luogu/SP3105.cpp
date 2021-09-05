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

map <int, int> M;

inline int Power(int x, int a, int Mod) {
    int ans = 1;
    while(a) {
        if(a & 1)
            ans = (ans * x) % Mod;
        x = (x * x) % Mod;
        a >>= 1;
    }
    return ans;
}

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline void exBSGS(int x, int y, int Mod) {
    if(y == 1) {
        puts("0");
        return;
    }
    int g = gcd(x, Mod), res = 1, ans = 0;
    while(g != 1ll) {
        if(y % g) {
            puts("No Solution");
            return;
        }
        y /= g, Mod /= g, res = (res * x / g) % Mod, ++ans;
        if(res == y) {
            printf("%lld\n", ans);
            return;
        }
        g = gcd(x, Mod);
    }
    // 递归转迭代

    M.clear();
    int C = Mod, B = y, A = x;
    int m = ceil(sqrt(C)), smul = B;

    for(int i = 0; i <= m; ++i) {
        M[smul] = i;
        smul = (smul * A) % C;
    }

    B = Power(A, m, C), smul = res;

    for(int i = 1; i <= m; ++i) {
        smul = (smul * B) % C;
        if(M.count(smul)) {
            printf("%lld\n", i * m - M[smul] + ans);
            // system("pause");
            return;
        }
    }
    puts("No Solution");
    return;
}

int x, y, Mod;
int mod;

signed main() {
    
    while(1) {
        x = read(), Mod = read(), y = read();
        if(x == y and y == Mod and Mod == 0)
            break;
        x %= Mod, y %= Mod;
        exBSGS(x, y, Mod);
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
