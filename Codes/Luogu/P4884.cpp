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

const int maxn = 1e7 + 1;

int A, B, C;

int a[maxn];

map <int, int> M;

inline int Power(int x, int a) {
    int base = x, ans = 1;
    while(a) {
        if(a & 1)
            ans = (__int128)(ans * base) % C;
        base = (__int128)(base * base) % C;
        a >>= 1;
    }
    return ans % C;
}

signed main() {
    
    B = read(), C = read(), A = 10 % C;
    B = (__int128)(B * 9 + 1) % C;
    int m = ceil(sqrt(C)), smul = B;

    for(int i = 0; i <= m; ++i) {
        M[smul] = i;
        smul = (__int128)((smul % C) * (A % C) % C);
    }

    B = smul = (__int128)Power(A, m);

    for(int i = 1; i <= m; ++i) {
        if(M.count(smul)) {
            printf("%lld\n", ((__int128)(i * m) * 1ll) - M[smul]);
            return 0;
        }
        smul = (__int128)((smul * B) % C);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}