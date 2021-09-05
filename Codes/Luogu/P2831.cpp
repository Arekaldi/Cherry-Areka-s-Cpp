#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e6 + 1;
const double eps = 1e-9;

int tot, n, m, num[19][19], sta[maxn], f[maxn];
double x[19], y[19];

typedef pair < pair <double, double>, bool > ddb;
#define mp make_pair

inline bool operator == (const ddb &a, const ddb &b) {
    return (a.first.first - b.first.first < eps) and (a.first.second - b.first.second < eps)
            and (a.second == b.second);
}

inline ddb Judge(int i, int j) {
    // 判断 i、j 两蜘蛛是否在同一条直线上
    if(x[i] == x[j] and y[i] != y[j])
        return mp(mp(0, 0), false);
    double k1 = x[i] * x[i], k2 = x[i], y1 = y[i],
        k3 = x[j] * x[j], k4 = x[j], y2 = y[j];
    // 将方程化为 k1a + k2b = y1 k3a  + k4b = y2 的形式
    double ss = k1 / k3; k3 = k1, k4 *= ss, y2 *= ss;
    // k1a + k2b = y1, k1a + xb = y
    // (x - k2)b = y - y1
    double b = (y2 - y1) / (k4 - k2);
    double a = y1 - k2 * b;
    if(a < 0)
        return mp(mp(a, b), true);
    else
        return mp(mp(a, b), false);
}

signed main() {
    int T = read();
    while(T--) {
        memset(sta, 0, sizeof(sta));
        memset(num, 0, sizeof(num));
        tot = 0;
        n = read(), m = read();

        for(int i = 1; i <= n; ++i)
            scanf("%lf%lf", &x[i], &y[i]);

        for(int i = 0; i < (1 << n); ++i)
            sta[++tot] = i;
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(i == j)
                    continue;
                ddb p = Judge(i, j);
                if(!p.second)
                    continue;
                num[i][j] |= (1 << (i - 1)), num[i][j] |= (1 << (j - 1));
                for(int k = 1; k <= n; ++k) {
                    if(k == i or k == j)
                        continue;
                    ddb pp = Judge(i, k);
                    // cout << i << " " << j << " " << k << " " << p.first.first << " " << p.first.second << endl;
                    // cout << pp.first.first << " " << pp.first.second << " " << pp.second << " " << (pp == p) << endl;
                    if(pp == p)
                        num[i][j] |= (1 << (k - 1));
                }
            }
        }

        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        
        // for(int i = 1; i <= n; ++i) {
        //     for(int j = i + 1; j <= n; ++j) {
        //         cout << i << " " << j << " " << num[i][j] << endl;
        //     }
        // }

        for(int it = 1; it <= tot; ++it) {
            int i = sta[it];
            for(int j = 1; j <= n; ++j) {
                if(i & (1 << (j - 1)))
                    continue;
                bool flag = false;
                for(int k = 1; k <= n; ++k) {
                    if(x[j] == x[k] or Judge(j, k).second == false)
                        continue;
                    if(j == k)
                        continue;
                    flag = true;
                    f[i | num[j][k]] = min(f[i | num[j][k]], f[i] + 1);
                }
                if(flag == false)
                    f[i | (1 << (j - 1))] = min(f[i | (1 << (j - 1))], f[i] + 1);
            }
        }

        printf("%d\n", f[(1 << n) - 1]);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
