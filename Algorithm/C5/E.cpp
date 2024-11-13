#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <assert.h>
#include <cmath>

const double eps = 1e-9;

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
    Node P; P.x = xx, P.y = yy;
    double r = distBetweenTwoPoints(A, P);
    double r2 = distBetweenTwoPoints(C, P);
    if(std :: abs(r - r2) > eps)
        assert(0);
    double dist = 0.0;
    if(D.x == E.x)
        dist = std :: abs(xx - D.x);
    else {
        double a = (D.y - E.y) / (D.x - E.x);
        double b = D.y - a * D.x;
        dist = ((a * xx + b - yy) / std :: sqrt(a * a + 1.0));
        if(dist < 0.0)
            dist = -dist;
    }
    if(dist - r2 < eps)
        return 0.0;
    else
        return dist - r2;
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        for(int i = 1; i <= 5; i++) {
            scanf("%lf%lf", &nodes[i].x, &nodes[i].y);
        }
        double ans = distBetweenCircleandLine(nodes[1], nodes[2], nodes[3], nodes[4], nodes[5]);
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
                    double dist = distBetweenCircleandLine(nodes[i], nodes[j], nodes[k], nodes[d], nodes[e]);
                    if(dist > ans)
                        ans = dist;
                }
            }
        }
        printf("%.3lf\n", ans);
    }
}