#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <math.h>

#define int long long

int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
        (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

int T, n;

struct Node {
    int x, y;
    bool operator < (const Node &b) {
        return x == b.x ? y < b.y : x < b.x;
    }
};

double distBetNodes(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

Node a[100010];

signed main() {
    T = read();
    while(T--) {
        int x1, x2, y1, y2, xA, yA;
        double x1d, x2d, y1d, y2d, xAd, yAd;
        xA = read(), yA = read();
        xAd = xA, yAd = yA;
        x1 = read(), y1 = read();
        x1d = x1, y1d = y1;
        x2 = read(), y2 = read();
        x2d = x2, y2d = y2;
        if((xA - x1) * (y2 - y1) == (yA - y1) * (x2 - x1)) {
            if(xA >= std :: min(x1, x2) && xA <= std :: max(x1, x2) && yA >= std :: min(y1, y2) && yA <= std :: max(y1, y2)) {
                puts("0.000");
                continue;
            }
            double dis = std :: min(distBetNodes(xAd, yAd, x1d, y1d), distBetNodes(xAd, yAd, x2d, y2d));
            printf("%.3lf\n", dis);
        }
        else if(x2 == x1 || y2 == y1) {
            if(x2 == x1) {
                if(yA >= std :: min(y1, y2) && yA <= std :: max(y1, y2)) {
                    double dis = std ::abs(xAd - x1d);
                    printf("%.3lf\n", dis);
                }
                else {
                    double dis1 = distBetNodes(xAd, yAd, x1d, y1d), dis2 = distBetNodes(xAd, yAd, x2d, y2d);
                    double dis = std :: min(dis1, dis2);
                    printf("%.3lf\n", dis);
                }
            }
            if(y2 == y1) {
                if(xA >= std :: min(x1, x2) && xA <= std :: max(x1, x2)) {
                    double dis = std ::abs(yAd - y1d);
                    printf("%.3lf\n", dis);
                }
                else {
                    double dis1 = distBetNodes(xAd, yAd, x1d, y1d), dis2 = distBetNodes(xAd, yAd, x2d, y2d);
                    double dis = std :: min(dis1, dis2);
                    printf("%.3lf\n", dis);
                }
            }
        }
        else {
            double a = (y2d - y1d) / (x2d - x1d), b = y1d - a * x1d;
            double x0 = (xAd - a * b + a * yAd) / (a * a + 1), y0 = a * x0 + b;
            if(x0 >= std :: min(x1, x2) && x0 <= std :: max(x1, x2) && y0 >= std :: min(y1, y2) && y0 <= std :: max(y1, y2)) {
                double dis = (a * xAd - yAd + b) / sqrt(a * a + 1);
                if(dis < 0)
                    dis = -dis;
                printf("%.3lf\n", dis);
            }
            else {
                double dis1 = distBetNodes(xAd, yAd, x1d, y1d), dis2 = distBetNodes(xAd, yAd, x2d, y2d);
                double dis = std :: min(dis1, dis2);
                printf("%.3lf\n", dis);
            }
        }
    }
    return 0;
}