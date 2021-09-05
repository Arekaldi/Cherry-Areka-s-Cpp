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

class Point {
    public :
        double x, y;
}P[maxn];

inline double Cpro(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int n;

signed main() {
    n = read();

    double ans = 0;

    for(int i = 1 ; i <= n; ++i) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        if(i != 1)
            ans += Cpro(P[i - 1], P[i]);
    }
    
    ans += Cpro(P[n], P[1]);

    int w = ans;

    printf("%d\n", w >> 1);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
