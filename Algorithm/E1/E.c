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

double f[100010][52];

int main() {
    int n = read(), p = read();
    double nn = n * 1.0, pp = p * 1.0;
    f[1][0] = pp / 100, f[1][1] = (100 - pp) / 100;
    for(int i = 2; i < 100010; ++i) {
        double sum = 1.0 - f[i - 1][n];

        // for(int j = 0; j < n; ++j)
        //     sum += f[i - 1][j];
        
        for(int j = 0; j <= n; ++j) {
            if(j == 0)
                f[i][j] = sum * pp / 100 + f[i - 1][n];
            else if(j > i)
                break;
            else
                f[i][j] = f[i - 1][j - 1] * (100 - pp) / 100;
        }
    }
    printf("%.3lf", f[100009][0]);
    return 0;
}