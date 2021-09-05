#include <bits/stdc++.h>

using namespace std;

#define read(n) scanf("%lf", &(n))

double n;
double a[15];

const double Inf = (1 << 30) * 1.0;

class Point {
    public :
        double X[15];
}P[15];

const double delta = 0.996;

inline double DD(double x, double y) {
    double E = x - y;
    return E * E;
}

double Ds[15];

inline double F_dat() {
    double k = 0;
    for(int i = 1; i <= n + 1; ++i)
        k += Ds[i];
    
    k /= (n + 1);

    double an = 0;
    bool flag = false;
    for(int i = 1; i <= n + 1; ++i)
        an += DD(Ds[i], k), flag = (Ds[i] * Ds[i]) > 20000 ? true : flag;

    return flag ? Inf : an;
}

inline double Dis() {
    memset(Ds, 0, sizeof(Ds));

    for(int i = 1; i <= n + 1; ++i) 
        for(int j = 1; j <= n; ++j) 
            Ds[i] += DD(a[j], P[i].X[j]);

    for(int i = 1; i <= n + 1; ++i)
        Ds[i] = sqrt(Ds[i]);
    
    double ans = F_dat();

    return ans;
}

double min_ans;

inline void Sa() {
    double T = 3010, T0 = 1e-15;
    double ans = min_ans;

    while(T > T0) {
        int now_x = (int)(rand() * T) % (int)n + 1;
        double p = a[now_x];
        double now_y = (double)(((rand() << 1) - RAND_MAX) * T) + p;
        a[now_x] = now_y;
        double now_ans = Dis();
        double E = now_ans - ans;
        if(E < 0) 
            ans = now_ans;
        else if(exp(-E / T) * RAND_MAX <= rand())
            a[now_x] = p;
        T *= delta;
    }

    if(ans < min_ans)
        min_ans = ans;

    return;
}

// #define ONLINE_JUDGE

signed main() {
    read(n);

    for(int i = 1; i <= n + 1; ++i) {
        for(int j = 1; j <= n; ++j)
            read(P[i].X[j]), a[j] += P[i].X[j];
    }

    for(int i = 1; i <= n; ++i)
        a[i] /= (n + 1);

    min_ans = Dis();

    while(clock() / CLOCKS_PER_SEC <= 0.75)
        Sa();

    for(int i = 1; i <= n; ++i)
        printf("%.3lf ", a[i]);

    #ifndef ONLINE_JUDGE
        getchar(), getchar();
    #endif
    return 0;
}
