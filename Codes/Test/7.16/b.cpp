#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

inline double readd() {
    register double x;
    scanf("%lf", &x);
    return x;
}

const int maxn = 105;

double a[maxn][maxn];
double b[maxn][maxn];
double f[maxn];

int n, m;

inline void Gauss(int n) {
    for(int i = 1; i <= n; ++i) { // 从第i行开始，在第i列中选择主元
        int Nw = i;
        
        for(int j = i + 1; j <= n; ++j) //在第i及以下行中选择系数最大的未知数做主元
            if(fabs(a[j][i]) > fabs(a[Nw][i]))
                Nw = j;
        // 找到xi的最大系数
        
        for(int j = i; j <= n + 1; ++j)
            swap(a[Nw][j], a[i][j]); // 交换第Nw行的第i行


        for(int j = 1; j <= n; ++j) {
            //枚举j行，将其他的xi消掉
            if(j == i)
                continue;
            double Temp = a[j][i] / a[i][i];
            for(int k = i; k <= n + 1; ++k)
                // 做差，将第j行的xi消掉
                a[j][k] -= a[i][k] * Temp;
                //保证方程的正确性
        }
    }
    
    for(int i = 1; i <= n; ++i)
        f[i] = a[i][n + 1] / a[i][i];
        // printf("%.8f\n", a[i][n + 1] / a[i][i]);
        // 最后方程会化为 a[i][i] * x_i = a[i][n + 1] 的形式
    
}

double P[maxn];
// pi -> \Sum j != i b[i][j]
char q[maxn];

signed main() {

    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);

    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            b[i][j] = readd();
            if(j != i)
                P[i] += b[i][j];
        }

    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(j != i)
                a[i][j] = -b[i][j];
            else 
                a[i][j] = (n - 1 - P[i]);
        }
    }
    for(int j = 1; j <= n + 1; ++j)
        a[n][j] = 1;

    // for(int i = 1; i <= n; ++i)
    //     printf("%.8f\n", f[i]);

    Gauss(n);

    for(int i = 1; i <= m; ++i) {
        cin >> (q + 1);
        double ans = 0;
        for(int j = 1; q[j]; ++j)
            if(q[j] == '1')
                ans += f[j];
        printf("%.5f\n", ans);
    }

    // #ifndef ONLINE_JUDGE
    //     getchar();
    // #endif
    return 0;
}
