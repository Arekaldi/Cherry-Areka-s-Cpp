#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline ll read() {
    register ll x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int p[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

int g[32], c[32];
ll b[32];

ll ans;
int num = 1;
int n;

inline void Dfs(int x) {
    if(b[x - 1] > n)
        return;
    c[x] = 1, b[x] = b[x - 1] * p[x], g[x] = g[x - 1] << 1;
    while(c[x] <= c[x - 1] and b[x] <= n) {
        if(num < g[x])
            ans = b[x], num = g[x];
        else if(num == g[x])
            ans = min(ans, b[x]);
        Dfs(x + 1);
        c[x]++;
        b[x] *= p[x];
        g[x] += g[x - 1];
    }
}

signed main() {
    n = read();

    c[0] = 32, b[0] = 1, g[0] = 1;
    
    Dfs(1);

    cout << ans;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
