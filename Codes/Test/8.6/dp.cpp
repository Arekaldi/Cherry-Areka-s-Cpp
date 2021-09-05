#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e2 + 1;

double f[maxn][maxn], g[maxn][maxn],
a[maxn], b[maxn], c[maxn];
int n, m, t, K, p; 

inline void Init() {
    memset(f, 0, sizeof(f));
    // i 次机会， 现在有 j 个没糖，最多多少糖
    memset(g, 0, sizeof(g));
    // i 个盒子， j 个有， 概率
    memset(a, 0, sizeof(a));
    // K 有 i 个糖的概率
    memset(b, 0, sizeof(b));
    // T 有 i 个糖的概率
}

signed main() {
    #define Areka
    #ifdef Areka
        freopen("dp.in", "r", stdin);
        freopen("dp.out", "w", stdout);
    #endif
    int T = read();
    while(T--) {
        Init();
        n = read(), m = read(), t = read(), K = read(), p = read();
        for(int i = 0; i < t; ++i)
            c[i] = min(1.0 * p + i, 100.0) / 100.0;
        // 预处理出 T 个盒子中第 i 个盒子有糖的概率
        
        for(int i = 0; i < (1 << t); ++i) {
            double P = 1;
            int num = 0;
            for(int j = 0; j < t; ++j)
                if((i >> j) & 1)
                    num++, P *= c[j];
                else
                    P *= (1.0 - c[j]);
            b[num] += P;
        }
        
        // 预处理出概率
        g[0][0] = 1;
        for(int i = 1; i <= K; ++i) {
            for(int j = 0; j <= i; ++j) {
                g[i][j] = g[i - 1][j] * (100.0 - p) / 100.0;
                if(j)
                    g[i][j] += g[i - 1][j - 1] * p / 100.0;
            }
        }

        for(int i = 0; i <= K; ++i)
            a[i] = g[K][i];
        
        for(int i = 1; i <= m; ++i) {
            for(int j = 0; j <= n; ++j) {
                double res = 0;
                int s = max(K, j);
                for(int k = 0; k <= K; ++k)
                    res += (f[i - 1][s - k] + j - s + k) * a[k];
                f[i][j] = max(f[i][j], res);
            }
            for(int j = 0; j <= n; ++j) {
                double res = 0;
                int s = max(j, t);
                for(int k = 0; k <= t; ++k)
                    res += (f[i - 1][s - k] + j - s + k) * b[k];
                f[i][j] = max(f[i][j], res);
            }
        }
        printf("%.5f\n", f[m][n]);
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
