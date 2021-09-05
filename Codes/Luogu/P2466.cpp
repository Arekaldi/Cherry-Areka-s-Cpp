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

const int maxn = 1e3 + 5;

int n, x0, ss[maxn];
double f[maxn][maxn][2];
double sum[maxn][maxn];

class Node {
    public:
        int x, y, v, val;
        inline bool operator < (const Node &g) const {
            return g.x > x;
        }
};

Node p[maxn];

int res;

signed main() {

    n = read(), x0 = read();
    for(int i = 1; i <= n; ++i)
        p[i].x = read();
    for(int i = 1; i <= n; ++i)
        p[i].y = read(),
        res += p[i].y;
    for(int i = 1; i <= n; ++i)
        p[i].v = read();
    
    double ans = res / 1000.0;
    bool flag = false;
    for(int i = 1; i <= n; ++i)
        if(p[i].x == x0) {
            flag = true;
            break;
        }
    if(!flag)
        p[++n].x = x0, p[n].y = 0, p[n].v = 0;

    sort(p + 1, p + n + 1);

    for(int i = 1; i <= n; ++i)
        ss[i] = ss[i - 1] + p[i].v;

    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j)
            f[i][j][0] = f[j][i][0] = f[i][j][1] = f[j][i][1] = 2e10;

    for(int i = 1; i <= n; ++i) {
        if(p[i].x == x0) {
            f[i][i][0] = f[i][i][1] = 0;
            break;
        }
    }

    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            sum[i][j] = (ss[n] - (ss[j] - ss[i - 1])) / 1000.0;

    for(int len = 1; len <= n; ++len) {
        for(int l = 1; l + len <= n; ++l) {
            int r = l + len;
            f[l][r][0] = min(f[l][r][0], min(f[l + 1][r][0] + (p[l + 1].x - p[l].x) * sum[l + 1][r], f[l + 1][r][1] +(p[r].x - p[l].x) * sum[l + 1][r]));
            f[l][r][1] = min(f[l][r][1], min(f[l][r - 1][1] + (p[r].x - p[r - 1].x) * sum[l][r - 1], f[l][r - 1][0] + (p[r].x - p[l].x) * sum[l][r - 1]));
        }
    }

    long double ans1 = ans - min(f[1][n][0], f[1][n][1]);
    printf("%.3llf", ans1);

    #ifndef ONLINE_JUDGE
        getchar(); 
    #endif

    return 0;
}