#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const double eps = 1e-6, feps = 1e-7;

const int maxn = 1e3 + 1;

double d[maxn], s[maxn];
int n;
double t;

inline double check(double x) {
    double alt = 0;
    for(int i = 1; i <= n; ++i) {
        if(s[i] + x < 0)
            return 1;
        alt += d[i] / (s[i] + x);
    }
    return alt - t;
}

signed main() {
    while(scanf("%d%lf", &n, &t) != EOF) {

        for(int i = 1; i <= n; ++i)
            scanf("%lf%lf", &d[i], &s[i]);
        
        double l = -(0x7f7f7f7f) * 1.0, r = 0x7f7f7f7f * 1.0;
        double ans;
        while(r - l > eps) {
            double mid = (l + r) / 2.0;
            double amid = check(mid);

            if(amid < 0)
                r = mid;
            else if(amid != 0)
                l = mid;
            ans = l;
        }

        printf("%.10f\n", ans);
    
    }
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
