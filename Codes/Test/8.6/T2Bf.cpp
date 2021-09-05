#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1, maxx = 1e3 + 1;

int k[maxn], b[maxn];
int n, m;
vector <int> c[maxx];

signed main() {
    #define Areka
    #ifdef Areka
        freopen("data_struct.in", "r", stdin);
        freopen("data_struct.out", "w", stdout);
    #endif
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        k[i] = read();
    for(int i = 1; i <= n; ++i)
        b[i] = read();



    for(int i = 1; i <= m; ++i) {
        int opt = read();
        if(opt == 1) {
            int L = read(), R = read(), x = read();
            int maxx = -(1 << 30);
            for(int j = L; j <= R; ++j) {
                if(k[j] * x + b[j] >= maxx)
                    maxx = k[j] * x + b[j];
            }
            printf("%d\n", maxx);
        }
        else if(opt == 2) {
            int p = read(), v = read();
            k[p] += v;
        }
        else {
            int L = read(), R = read(), v = read();
            for(int j = L; j <= R; ++j)
                b[j] += v;
        }
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
