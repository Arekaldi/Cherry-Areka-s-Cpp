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

int tot, d[maxn];
int n, m;

signed main() {

    #define Areka
    #ifdef Areka
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        d[u]++, d[v]++;
        if(d[u] >= 3)
            ++tot;
        if(d[v] >= 3)
            ++tot;
    }
    
    puts(tot >= 2 ? "YES" : "NO");
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
