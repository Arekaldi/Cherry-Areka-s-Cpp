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

const int maxn = 1e6 + 1;

int A, B, C;

int a[maxn];

map <int, int> M;

inline int Power(int x, int a) {
    int base = x, ans = 1;
    while(a) {
        if(a & 1)
            ans = (ans * base) % C;
        base = (base * base) % C;
        a >>= 1;
    }
    return ans % C;
}

signed main() {
    
    C = read(), A = read(), B = read();
    int m = ceil(sqrt(C)), smul = B;

    for(int i = 0; i <= m; ++i) {
        M[smul] = i;
        smul = (smul * A) % C;
    }

    B = smul = Power(A, m);

    for(int i = 1; i <= m; ++i) {
        if(M.count(smul)) {
            printf("%lld\n", i * m - M[smul]);
            system("pause");
            return 0;
        }
        smul = (smul * B) % C;
    }
    
    puts("no solution");

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}