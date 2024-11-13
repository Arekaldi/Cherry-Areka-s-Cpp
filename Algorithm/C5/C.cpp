#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

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

bool pointInLine(double x, double y, double x1, double y1, double x2, double y2) {
    return x >= std :: min(x1, x2) && x <= std :: max(x1, x2) && y >= std :: min(y1, y2) && y <= std :: max(y1, y2);
}

int main() {
    int T = read();
    while(T--) {
        double x1, y1, x2, y2;
        double x3, y3, x4, y4;
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        scanf("%lf %lf %lf %lf", &x3, &y3, &x4, &y4);
        if(x1 == x2 || x3 == x4) {
            if(x1 == x2 && x3 == x4) {
                if(pointInLine(x1, y1, x3, y3, x4, y4) || pointInLine(x2, y2, x3, y3, x4, y4))
                    puts("intersect");
                else
                    puts("parallel");
            }
            else {
                if(x1 == x2) {
                    double x0 = x1, y0 = ((y4 - y3) / (x4 - x3)) * (x0 - x3) + y3;
                    if(pointInLine(x0, y0, x1, y1, x2, y2))
                        puts("intersect");
                    else
                        puts("neither");
                }
                else {
                    double x0 = x3, y0 = ((y2 - y1) / (x2 - x1)) * (x0 - x1) + y1;
                    if(pointInLine(x0, y0, x3, y3, x4, y4))
                        puts("intersect");
                    else
                        puts("neither");
                }
            }
            continue;
        }
        double a1 = (y2 - y1) / (x2 - x1);
        double b1 = y1 - a1 * x1;
        double a2 = (y4 - y3) / (x4 - x3);
        double b2 = y3 - a2 * x3;
        double x = (b2 - b1) / (a1 - a2);
        double y = a1 * x + b1;
        if(a1 == a2) {
            if(pointInLine(x1, y1, x3, y3, x4, y4) || pointInLine(x2, y2, x3, y3, x4, y4))
                puts("intersect");
            else
                puts("parallel");
            continue;
        }
        double x0 = (b2 - b1) / (a1 - a2), y0 = x0 * a1 + b1;
        if(x0 >= std :: min(x1, x2) && x0 <= std :: max(x1, x2) && x0 >= std :: min(x3, x4) && x0 <= std :: max(x3, x4) && y0 >= std :: min(y1, y2) && y0 <= std :: max(y1, y2) && y0 >= std :: min(y3, y4) && y0 <= std :: max(y3, y4)) {
            puts("intersect");
            continue;
        }
        else
            puts("neither");
    }
}