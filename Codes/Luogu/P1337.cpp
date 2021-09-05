#include <bits/stdc++.h>

using namespace std;

#define nR ((rand() << 1) - RAND_MAX)

inline double Swi(int x) {
    double e1 = (double)x * 1.0;
    return e1;
}

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return Swi(x * f);
}

const double delta = 0.996;
const int maxn = 1e4 + 1, Inf = (1 << 30);

double n, x_b, y_b;
double ans_x, ans_y;
double min_ans;
class Node {
    public :
        double x, y, w;
}P[maxn];

inline double dis(double x, double y, double x0, double y0) {
    double e1 = (x - x0), e2 = (y - y0);
    return sqrt(e1 * e1 + e2 * e2);
}

inline double Ans(double x, double y) {
    double a = 0.0;
    for(int i = 1; i <= n; ++i)
        a += (dis(x, y, P[i].x, P[i].y) * P[i].w);
    printf("%.3lf\n", a);
    // Sleep(10);
    return a;
}

inline void Sa() {
    double T = 3050, T0 = 1e-15;
    double x = ans_x, y = ans_y;
    double ans = min_ans;
    while(T > T0) {
        double now_x = x + nR * T, now_y = y + nR * T;
        double now_ans = Ans(now_x, now_y);
        double E = now_ans - min_ans;
        if(E < 0) 
            min_ans = now_ans, x = now_x, y = now_y;
        else if(exp(-E / T) * RAND_MAX > rand())
            x = now_x, y = now_y;
        T *= delta;
    }

    if(ans > min_ans) 
        min_ans = ans, ans_x = x, ans_y = y;

    return;
}

signed main() {
    srand(20051003);
    n = read();
    
    for(int i = 1; i <= n; ++i) {
        P[i].x = read(), P[i].y = read(), P[i].w = read();
        x_b += P[i].x, y_b += P[i].y;
    }
    
    ans_x = x_b, ans_y = y_b;
    min_ans = Ans(x_b, y_b);
    
    // clock();
    Sa(); Sa(); Sa(); Sa(); Sa(); Sa();
    
    printf("%.3lf %.3lf", ans_x, ans_y);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
