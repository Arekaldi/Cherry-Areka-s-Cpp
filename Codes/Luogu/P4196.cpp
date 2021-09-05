#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const long double eps = 1e-8, Pi = acos(-1);
const int maxn = 1e5 + 1;

double S = 0;
double Up = 1e3;


class Point {
    public:
        double x, y;
        Point(double X = 0, double Y = 0) : x(X), y(Y) {}
}sta[maxn], p[maxn];
inline Point operator + (Point x, Point y) {return Point(x.x + y.x, x.y + y.y);}
inline Point operator - (Point x, Point y) {return Point(x.x - y.x, x.y - y.y);}
inline Point operator * (Point x, double Lemda) {return Point(x.x * Lemda, x.y * Lemda);}

class Line {
    public:
        Point x, y;
        double angle;
        Line() {}
        Line(Point X, Point Y) : x(X), y(Y), angle(atan2(Y.y - X.y, Y.x - X.x)) {}
}L[maxn], q[maxn];

namespace P {
    inline int Ceps(double x) {
        return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);
    }
    //检验符号
    inline Point Rot(Point x, double angle) {
        return Point(x.x * cos(angle) - x.y * sin(angle), x.x * sin(angle) + x.y * cos(angle));
    }
    //旋转
    inline double Crop(Point x, Point y, bool Type) {
        if(Type) {
            printf("X: %.9lf %.9lf Y: %.9lf %.9lf\n", x.x, x.y, y.x, y.y);
        }
        return x.x * y.y - x.y * y.x;
    }
    //叉乘
    inline double Dot(Point x, Point y) {
        return x.x * y.x + x.y * y.y;
    }
    //点乘
    inline bool nsin(Point x, Line y) {
        return Crop(x - y.x, y.y - y.x, 0) > 0;
    }
    //判断点在线的哪一侧
    inline double Len(Point x) {
        return sqrt(x.x * x.x + x.y * x.y);
    }
    inline Point Cross_Point(Line a, Line b) {
        Point v = a.y - a.x, u = b.y - b.x, w = a.x - b.x;
        // u, v 分别是单位向量
        // w是两线端点连线的单位向量
        double t = Crop(w, u, 0) / Crop(u, v, 0);
        return a.x + v * t;
        //公式
    }
    //求交点
    inline bool Camp(Line a, Line b) {
        return a.angle == b.angle ? nsin(b.x, a) : a.angle < b.angle;
        // 按极角排序
    }
    //排序函数
}

int n, m, tot;

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        m = read();
        for(int j = 1; j <= m; ++j)
            scanf("%lf%lf", &p[j].x, &p[j].y);
        for(int j = 1; j < m; ++j)
            L[++tot] = Line(p[j], p[j + 1]);
        L[++tot] = Line(p[m], p[1]);
    }
    Point a = Point(-Up, Up), b = Point(-Up, -Up), c = Point(Up, -Up), d = Point(Up, Up);
    //a, b, c, d组成大坐标系的边界（雾

    L[++tot] = Line(a, b), L[++tot] = Line(b, c), L[++tot] = Line(c, d), L[++tot] = Line(d, a);

    sort(L + 1, L + tot + 1, P::Camp);

    int l = 1, r = 1;
    //栈顶，栈底
    q[1] = L[1];
    //q 是凸包里的线
    //sta 是栈，栈里存的是交点

    for(int i = 2; i <= tot; ++i) {
        if(P::Ceps(L[i].angle - L[i - 1].angle) == 0)
            continue;
        //线有重复
        while(l < r and P::nsin(sta[r - 1], L[i]))
            r--;
        //栈顶不合格，在栈顶出栈
        while(l < r and P::nsin(sta[l], L[i]))
            l++;
        //同理
        q[++r] = L[i];
        //入栈
        if(l < r)
            sta[r - 1] = P::Cross_Point(q[r], q[r - 1]);
    }
    
    while(l < r and P::nsin(sta[r - 1], q[l]))
        r--;
    //检查最后新加入的点有没有产生冲突
    while(l < r and P::nsin(sta[l], q[r]))
        l++;
    //同理
    sta[r] = P::Cross_Point(q[l], q[r]);
    for(int i = l + 1; i < r; ++i) {
        double x = P::Crop(sta[i] - sta[l], sta[i + 1] - sta[l], 0);
        S += x;
    }
        //利用叉乘求面积
    printf("%.3lf", (S / 2.0));
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
