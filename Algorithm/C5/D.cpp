#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <cmath>

const double eps = 1e-16;

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

struct Node {
    double x, y;
};

Node nodes[6];

double distBetweenTwoPoints(Node A, Node B) {
    return std :: sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double distBetweenCircleandLine(Node A, Node B, Node C, Node D, Node E) {
    // Node A, B, C for Circle, Node D, E for line
    double a = (A.x - B.x);
    double b = (A.y - B.y);
    double c = (A.x - C.x);
    double d = (A.y - C.y);
    double e = ((A.x * A.x - B.x * B.x) - (B.y * B.y - A.y * A.y)) / 2.0;
    double f = ((A.x * A.x - C.x * C.x) - (C.y * C.y - A.y * A.y)) / 2.0;
    double xx = (e * d - b * f) / (a * d - b * c);
    double yy = (a * f - e * c) / (a * d - b * c);
    Node P = Node{xx, yy};
    double r = distBetweenTwoPoints(A, P);
    double dist = 0.0;
    if(D.x == E.x)
        dist = std :: abs(xx - D.x);
    else {
        double a = (D.y - E.y) / (D.x - E.x);
        double b = D.y - a * D.x;
        dist = std :: abs(a * xx + b - yy) / std :: sqrt(a * a + 1);
    }
    if(dist - r < eps)
        return 0;
    else
        return dist - r;
}
int main() {
    int T = read();
    while(T--) {
        // printf("%.3lf\n", (double) 0);
        // continue;
        for(int i = 1; i <= 5; i++)
            nodes[i].x = read(), nodes[i].y = read();
        double ans = 1 << 30;
        for(int i = 1; i <= 5; ++i) {
            for(int j = i + 1; j <= 5; ++j) {
                for(int k = j + 1; k <= 5; ++k) {
                    int d = 0, e;
                    for(int l = 1; l <= 5; ++l) {
                        if(l == i || l == j || l == k)
                            continue;
                        else {
                            if(d == 0)
                                d = l;
                            else {
                                e = l;
                                break;
                            }
                        }
                    }
                    ans = std :: min(ans, distBetweenCircleandLine(nodes[i], nodes[j], nodes[k], nodes[d], nodes[e]));
                }
            }
        }
        printf("%.3lf\n", ans);
    }
}