#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

double Number[100];

int main() {
    int n = read();
    double sum = 0;
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &Number[i]), sum += Number[i];
    double average = sum / n;
    double ans = 0;
    for(int i = 1; i <= n; ++i)
        ans += (Number[i] - average) * (Number[i] - average);
    double xx = n * (n - 1) * 1.0;
    ans /= xx;
    ans = sqrt(ans);
    printf("%lf\n", ans);
    return 0;
}