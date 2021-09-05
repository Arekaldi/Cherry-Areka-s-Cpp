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

int n, Mod;

const int p[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
const int maxn = 5e2 + 1;

class Node {
    public:
        int val, hge, smal;
        inline void Init() {
            int n1 = val;
            hge = -1;
            for(int i = 1; i <= 8; ++i) {
                if(n1 % p[i])
                    continue;
                smal |= 1 << (i - 1);
                while(n1 % p[i] == 0)
                    n1 /= p[i];
                if(n1 == 1)
                    break;
            }
            if(n1 != 1)
                hge = n1;
        }

        inline bool operator < (const Node &g) {
            return g.hge > hge;
        }
};

Node a[maxn];

int f[maxn][maxn];
int f1[maxn][maxn], f2[maxn][maxn];

signed main() {
    n = read(), Mod = read();
    for(int i = 2; i <= n; ++i)
        a[i - 1].val = i, a[i - 1].Init();
    sort(a + 1, a + n);

    // for(int i = 1; i < n; ++i)
    //     cout << a[i].hge << endl;

    f[0][0] = 1;
    for(int i = 1; i < n; ++i) {
        if(i == 1 or a[i].hge != a[i - 1].hge or a[i].hge == -1) {
            memcpy(f1, f, sizeof(f1));
            memcpy(f2, f, sizeof(f2));
        }

        for(int j = (1 << 8) - 1; j >= 0; --j) {
            for(int k = (1 << 8) - 1; k >= 0; --k) {
                if(j & k)
                    continue;
                if((a[i].smal & j) == 0)
                    f2[j][k | a[i].smal] = (f2[j][k | a[i].smal] + f2[j][k]) % Mod;
                if((a[i].smal & k) == 0)
                    f1[j | a[i].smal][k] = (f1[j | a[i].smal][k] + f1[j][k]) % Mod;
            }
        }

        if(i == n - 1 or a[i].hge != a[i + 1].hge or a[i].hge == -1)
            for(int j = 0; j < (1 << 8); ++j)
                for(int k = 0; k < (1 << 8); ++k) {
                    if(j & k)
                        continue;
                    f[j][k] = (f1[j][k] + f2[j][k] - f[j][k] + Mod) % Mod;
                }
    }

    int res = 0;
    for(int j = 0; j < (1 << 8); ++j)
        for(int k = 0; k < (1 << 8); ++k)
            if((j & k) == 0 and f[j][k])
                res = (res + f[j][k]) % Mod;
    printf("%lld\n", res);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
