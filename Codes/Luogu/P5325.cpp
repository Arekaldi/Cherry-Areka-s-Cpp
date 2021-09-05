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

const int Mod = 1e9 + 7;
const int maxn = 6e5 + 1;

int n, T, pri[maxn], Sf[maxn], Sg[maxn], Sh[maxn], tot;
int m, w[maxn], id1[maxn], id2[maxn], g[maxn], h[maxn], s[maxn];
bool isp[maxn];

inline void Pri() {
    for(int i = 2; i <= T; ++i) {
        if(!isp[i]) {
            pri[++tot] = i; //记录 n 以内的素数个数
            Sf[tot] = (Sf[tot - 1] + (i * (i - 1)) % Mod) % Mod;
            // 题意 f(p^k) = p^k * (p^k - 1)
            Sg[tot] = (Sg[tot - 1] + (i * i) % Mod) % Mod;
            Sh[tot] = (Sh[tot - 1] + i) % Mod;
            // Sg - Sh = Sf
        }
        for(int j = 1; j <= tot and i * pri[j] <= T; ++j) {
            isp[i * pri[j]] = 1;
            if(!(i % pri[j]))
                break;
        }
    }
}

inline int Id(int x) {
    return x <= T ? id1[x] : id2[n / x];
}

inline int S(int x, int y) {
    if(x < pri[y])
        return 0;
    int ans = ((g[Id(x)] - Sf[y - 1]) % Mod + Mod) % Mod;
    if(y > tot or pri[y] * pri[y] > x)
        return ans;
    int res;
    for(int i = y; i <= tot and pri[i] * pri[i] <= x; ++i) {
        res = pri[i];
        for(int j = 1; res * pri[i] <= x; ++j) {
            ans = (ans + ((res * pri[i]) % Mod) * ((res * pri[i] - 1ll) % Mod) % Mod + (((res % Mod) * ((res - 1) % Mod) % Mod) * S(x / res, i + 1)) % Mod) % Mod;
            res *= pri[i];
        }
    }
    return ans % Mod;
}

// #define prime pri
// #define mod Mod
// #define sum_f Sf
// #define sum_h Sh
// #define sum_g Sg

signed main() {
    n = read(), T = sqrt(n);
    // 分块
    Pri(); // 亚线性筛素数

    int j;
    for(int i = 1; i <= n; i = j + 1) {
        w[++m] = n / i, j = n / w[m];
        // 整除分块
        if(w[m] <= T)
            id1[w[m]] = m;
        else
            id2[j] = m; // 数组存不下！
        g[m] = (((((w[m] * ((((w[m] +1 ) % Mod) * (( 2 * w[m] + 1) % Mod)) % Mod)) % Mod) * 166666668) % Mod) + Mod - 1) % Mod;
		h[m] = ((((w[m] - 1) % Mod) * ((w[m] + 2) % Mod)) % Mod * 500000004) % Mod; 
    }
    
    int lim;
    for(int i = 1; i <= tot; ++i) {
        lim = pri[i] * pri[i];
        for(int j = 1; lim <= w[j]; ++j) {
			g[j] = (g[j] - ((pri[i] * pri[i]) % Mod) * ((g[Id(w[j] / pri[i])] - Sg[i-1]) % Mod)) % Mod;
			h[j] = (h[j] - (pri[i] * ((h[Id(w[j] / pri[i])] - Sh[i-1]) % Mod)) % Mod) % Mod;
        }
    }

    for(int i = 1; i <= m; ++i)
        g[i] = (g[i] - h[i] + Mod) % Mod;

    printf("%lld\n", (S(n, 1) + 1) % Mod);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
