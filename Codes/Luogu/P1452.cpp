#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;
const double eps = 1e-15;

int n;
double ans;

class Point {
    public :
        double x, y;
        Point(int a = 0, int b = 0) : x(a), y(b) {}
}P[maxn];

Point S[maxn], O; //栈

inline double Crop(Point a1, Point a2, Point b1, Point b2) {
    Point Na, Nb;
    Na.x = a2.x - a1.x, Na.y = a2.y - a1.y;
    Nb.x = b2.x - b1.x, Nb.y = b2.y - b1.y;
    return Na.x * Nb.y - Na.y * Nb.x;
}
//叉积

inline double Dis(Point a, Point b, bool Type) {
    double D = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    return Type ? D : sqrt(D);
}
//两点间的距离

inline bool Camp(Point a, Point b) {
    double Temp = Crop(P[1], a, P[1], b);
    if(Temp > 0) //不共线，且a点靠左
        return true;
    if(fabs(Temp) <= eps and Dis(P[1], a, 0) < Dis(P[1], b, 0)) //共线，但a点更近
        return true;
    return false;
}

inline int Get_TuBao() {
    sort(P + 2, P + n + 1, Camp); // 将剩余的点进行排序

    S[1] = P[1]; // 最低点肯定在凸包里

    int cnt = 1; // 指栈顶
    for(int i = 2; i <= n; ++i) {
        while(cnt > 1 and Crop(S[cnt - 1], S[cnt], S[cnt], P[i]) <= 0)
            /*
                设栈顶为 A 点，栈中点为 B 点
                则判断 BA 向量 与 AP 向量是否呈 >2π 的关系
                若是，则出栈。
                若找到一个符合条件的栈顶，直接退出循环，因为当前加入的点和之前的点没有关系
            */
            cnt--;
        cnt++, S[cnt] = P[i]; // 入队
    }

    S[cnt + 1] = P[1]; //最后一个点是凸包起点

    return cnt;
}

signed main() {
    n = read();

    for(int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        if((i != 1 and P[i].y < P[1].y) or (P[i].y == P[1].y and P[i].x < P[1].x))
            swap(P[1], P[i]);
    }
    
    int cnt = Get_TuBao();
    
    int j = 2; //寻找最远的点
    for(int i = 1; i <= cnt; ++i) {
        while(Crop(S[i], S[i + 1], S[i], S[j]) < Crop(S[i], S[i + 1], S[i], S[j + 1])) {
            j = (j + 1) % (cnt + 1);
            if(j == 0)
                j = 1;
        }
        // 叉积越小代表着夹角越大，两点之间也就越远
        // 双指针枚举两条边
        ans = max(ans, max(Dis(S[i - 1], S[j], 1), Dis(S[i], S[j], 1))); //比较面积哪个更优
    }
    
    printf("%.0lf\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
