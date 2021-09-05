#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e2 + 1;
const int Inf = (1 << 30);

int f[maxn][maxn][2], a[maxn];
bool fh[maxn][maxn];

signed main() {
    int n = read();
    for(int i = 1; i <= (n << 1); ++i)
        for(int j = 1; j <= (n << 1); ++j)
            f[i][j][0] = -Inf, f[i][j][1] = Inf;
        
    char ch;
    for(int i = 1; i <= (n << 1); ++i) {
        if(i & 1) {
            cin >> ch;
            if(i == 1)
                fh[1][n] = fh[n][1] = (ch == 't'), fh[0][1] = fh[1][0] = (ch == 't');
            else
                fh[(i >> 1)][(i + 1) >> 1] = fh[(i + 1) >> 1][i >> 1] = (ch == 't');
        }
        else
            f[(i >> 1)][(i >> 1)][0] = read(), f[(i >> 1)][(i >> 1)][1] = f[(i >> 1)][(i >> 1)][0];
    }

    n <<= 1;
    int n1 = (n >> 1);
    for(int i = (n >> 1) + 1; i <= n; ++i)
        f[i][i][0] = f[i][i][1] = f[i - n1][i - n1][0],
        fh[i - 1][i] = fh[i][i - 1] = fh[i - 1 - n1][i - n1];
    int ans = 0;
    for(int len = 1; len <= n; ++len) {
        for(int l = 1; l + len <= n; ++l) {
            int r = l + len;
            for(int k = l; k < r; ++k) {
                int maxl = f[l][k][0], maxr = f[k + 1][r][0],
                    minl = f[l][k][1], minr = f[k + 1][r][1];
                if(fh[k][k + 1]) {
                    f[l][r][0] = max(f[l][r][0], maxl + maxr);
                    f[l][r][1] = min(f[l][r][1], minl + minr);
                }
                else {
                    int res1 = max(maxl * maxr, maxl * minr);
                    int res2 = max(minl * maxr, minl * minr);
                    f[l][r][0] = max(f[l][r][0], max(res1, res2));
                    int ans1 = min(maxl * maxr, maxl * minr);
                    int ans2 = min(minl * maxr, minl * minr);
                    f[l][r][1] = min(f[l][r][1], min(ans1, ans2));
                }
            }

            if(len == (n >> 1) - 1)
                ans = max(ans, f[l][r][0]);
        }
    }

    cout << ans << endl;

    for(int i = 1; i <= (n >> 1); ++i)
        if(f[i][i + (n >> 1) - 1][0] == ans)
            printf("%d ", i);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}