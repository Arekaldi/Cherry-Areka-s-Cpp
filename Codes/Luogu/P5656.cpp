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

inline void Exgcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1, y = 0;
        return;
    }
    Exgcd(b, a % b, x, y);
    int z = x;
    x = y, y = z - (a / b) * y;
    return;
}

signed main() {
    int T = read();
    while(T--) {
        int a = read(), b = read(), c = read();
        int d = __gcd(a, b);
        if(c % d) {
            puts("-1");
            continue;
        }
        int x, y;
        Exgcd(a, b, x, y);
        int x1 = x * c / d, y1 = y * c / d;
        int dx = b / d, dy = a / d;
        int smin = ceil((1 - x1) / dx), smax = floor((y1 - 1) / dy);
        int xmin = x1 + dx * smin;
        int ymin = y1 - dy * smax;
        if(smin > smax)
            printf("%lld %lld\n", xmin, ymin);
        else {
            int xmax = x1 + smax * dx;
            int ymax = y1 - smin * dy;
            int ss = smax - smin;
            printf("%lld %lld %lld %lld %lld\n", ss, xmin, ymin, xmax, ymax);
        }
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
