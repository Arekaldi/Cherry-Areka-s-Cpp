#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e3 + 5;
const double inf = 1e17 + 5;
int n, m, v, e, c[MAXN][2], mp[305][305];
double k[MAXN], dp[MAXN][MAXN][2], ans;
inline int read() {
    char ch = getchar(); int u = 0, f = 1;
    while (!isdigit(ch)) {if (ch == '-')f = -1; ch = getchar();}
    while (isdigit(ch)) {u = u * 10 + ch - 48; ch = getchar();}return u * f;
}
int main(){
    memset(mp, 63, sizeof(mp));
    n = read(); m = read(); v = read(); e = read();
    for (register int i = 1; i <= n; i++)c[i][0] = read();
    for (register int i = 1; i <= n; i++)c[i][1] = read();
    for (register int i = 1; i <= n; i++)scanf("%lf", &k[i]);
    for (register int i = 1; i <= e; i++){
        int x = read(), y = read(), w = read();
        mp[x][y] = mp[y][x] = min(mp[x][y], w);
    }
    for (register int k = 1; k <= v; k++)
        for (register int i = 1; i <= v; i++)
            for (register int j = 1; j <= v; j++)
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
    for (register int i = 1; i <= v; i++)mp[i][i] = mp[i][0] = mp[0][i] = 0;
    for (register int i = 0; i <= n; i++)
        for (register int j = 0; j <= m; j++)dp[i][j][0] = dp[i][j][1] = inf;
    dp[1][0][0] = dp[1][1][1] = 0;
    for (register int i = 2; i <= n; i++){
        dp[i][0][0] = dp[i - 1][0][0] + mp[c[i - 1][0]][c[i][0]];
        for (register int j = 1; j <= min(i, m); j++){
            int C1 = c[i - 1][0], C2 = c[i - 1][1], C3 = c[i][0], C4 = c[i][1];
            dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][0] + mp[C1][C3], dp[i - 1][j][1] + mp[C1][C3] * (1 - k[i - 1]) + mp[C2][C3] * k[i - 1]));
            dp[i][j][1] = min(dp[i][j][1], min(dp[i - 1][j - 1][0] + mp[C1][C3] * (1 - k[i]) + mp[C1][C4] * k[i], dp[i - 1][j - 1][1] + mp[C2][C4] * k[i] * k[i - 1] + mp[C2][C3] * k[i - 1] * (1 - k[i]) + mp[C1][C4] * (1 - k[i - 1]) * k[i] + mp[C1][C3] * (1 - k[i - 1]) * (1 - k[i])));
        }
    }
    ans = inf;
    for(int i = 0; i <= m and i <= n; ++i)
        printf("%d %.2f %.2f\n", i, dp[n][i][0], dp[n][i][1]);
    for (register int i = 0; i <= m; i++)ans = min(ans, min(dp[n][i][0], dp[n][i][1]));

    printf("%.2lf", ans);
    return 0;
}