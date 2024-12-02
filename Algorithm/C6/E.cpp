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

inline int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

signed main() {
    int T = 1;
    while(T--) {
        int a = read(), b = read(), c = 1;
        int d = gcd(a, b);
        if(c % d) {
            puts("-1");
            continue;
        }
        int x, y;
        Exgcd(a, b, x, y);
        int x1 = x * c / d, y1 = y * c / d;
        int dx = b / d, dy = a / d;
        double xx1 = x1, ddx = dx, yy1 = y1, ddy = dy;
        double smm = (1.0 - xx1) / ddx, smmm = (yy1 - 1.0) / ddy;
        int smin = ceil(smm), smax = floor(smmm);
        int xmin = x1 + dx * smin;
        int ymin = y1 - dy * smax;
        printf("%lld\n", xmin);
    }
    
    return 0;
}