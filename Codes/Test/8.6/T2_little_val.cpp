#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1;

int k[maxn], b[maxn];
int n, m;

inline int Ask(int l, int r, int x) {
    if(l == r)
        return k[l] * x + b[l];
    if(r == l + 1) {
        if(k[l] > k[r]) {
            if(x > (b[r] - b[l]) / (k[l] - k[r]))
                return k[l] * x + b[l];
            else
                return k[r] * x + b[r];
        }
        else if(k[l] == k[r])
            return k[l] * x + max(b[l], b[r]);
        else {
            if(x < (b[r] - b[l]) / (k[l] - k[r]))
                return k[l] * x + b[l];
            else
                return k[r] * x + b[r];
        }
    }
    int mid = (l + r) >> 1;
    int res1 = Ask(l, mid, x), res2 = Ask(mid + 1, r, x);
    return res1 > res2 ? res1 : res2;
}

signed main() {
    #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("w.txt", "w", stdout);
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
            printf("%d\n", Ask(L, R, x));
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
