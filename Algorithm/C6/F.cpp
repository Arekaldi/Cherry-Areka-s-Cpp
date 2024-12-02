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

const int maxn = 1e4 + 1;

class Point {
    public :
        int x, y;
}P[maxn];

inline int Cpro(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int n;

signed main() {
    n = read();

    int ans = 0;

    for(int i = 1 ; i <= n; ++i) {
        scanf("%lld%lld", &P[i].x, &P[i].y);
        if(i != 1)
            ans += Cpro(P[i - 1], P[i]);
    }
    
    ans += Cpro(P[n], P[1]);

    int w = ans;

    printf("%lld\n", w);
    
    return 0;
}