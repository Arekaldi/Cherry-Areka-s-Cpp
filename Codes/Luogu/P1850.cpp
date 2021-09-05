#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e3 + 1, maxv = 3e2 + 1;

int x[maxn], y[maxn];
int n, m, v, e;
double k[maxn], dis[maxv][maxv], f[maxn][maxn][2];

signed main() {
    n = read(), m = read(), v = read(), e = read();
    for(int i = 1; i <= n; ++i)
        x[i] = read();
    for(int i = 1; i <= n; ++i)
        y[i] = read();
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &k[i]);

    for(int i = 1; i <= v; ++i)
        for(int j = 1; j <= v; ++j)
            dis[i][j] = 1e9;

    for(int i = 1; i <= e; ++i) {
        int a = read(), b = read(), w = read();
        dis[a][b] = dis[b][a] = min(dis[a][b], w * 1.0);
    }

    for(int i = 1; i <= v; ++i)
        dis[i][i] = 0.0;

    for(int k = 1; k <= v; ++k)
        for(int i = 1; i <= v; ++i)
            for(int j = 1; j <= v; ++j)
                if(dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j], dis[j][i] = dis[i][j];

    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= m; ++j)
            f[i][j][0] = f[i][j][1] = 1e9;
    f[1][0][0] = f[1][1][1] = 0.0;
    for(int i = 2; i <= n; ++i)
        f[i][0][0] = f[i - 1][0][0] + dis[x[i]][x[i - 1]];

    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= m and j <= i; ++j) {
            f[i][j][0] = min(f[i - 1][j][0] + (double)(dis[x[i]][x[i - 1]] * 1.0), f[i - 1][j][1] + (double)(1.0 * k[i - 1] * dis[x[i]][y[i - 1]]) + (double)((1.0 - k[i - 1]) * dis[x[i]][x[i - 1]]));
            f[i][j][1] = f[i - 1][j - 1][0] + (double)(1.0 * k[i] * dis[y[i]][x[i - 1]]) + (double)((1.0 - k[i]) * dis[x[i]][x[i - 1]]);
            // 上次成，这次没成
            // double a = k[i - 1] * (1 - k[i]) * (1.0 * dis[y[i - 1]][x[i]]);
            // 上次成，这次成
            // double b = k[i - 1] * k[i] * (1.0 * dis[y[i - 1]][y[i]]);
            // 上次没成，这次没成
            // double c = (1.0 - k[i - 1]) * (1.0 - k[i]) * (1.0 * dis[x[i - 1]][x[i]]);
            // 上次没成，这次成
            // double d = (1.0 - k[i - 1]) * k[i] * (1.0 * dis[x[i - 1]][y[i]]);
            f[i][j][1] = min(f[i][j][1], f[i - 1][j - 1][1] + k[i - 1] * (1 - k[i]) * (1.0 * dis[y[i - 1]][x[i]]) + k[i - 1] * k[i] * (1.0 * dis[y[i - 1]][y[i]]) + (1.0 - k[i - 1]) * (1.0 - k[i]) * (1.0 * dis[x[i - 1]][x[i]]) + (1.0 - k[i - 1]) * k[i] * (1.0 * dis[x[i - 1]][y[i]]));
        }
    
    double ans = 2e9;
    // for(int i = 0; i <= m and i <= n; ++i)
    //     printf("%d %.2f %.2f\n", i, f[n][i][0], f[n][i][1]);
    for(int i = 0; i <= m and i <= n; ++i)
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    printf("%.2f", ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}