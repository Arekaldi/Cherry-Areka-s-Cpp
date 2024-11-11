#include <stdio.h>
#include <math.h>
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

char ans[10010][10010];

void Print(int n, int x, int y) {
    if(n == 1) {
        for(int i = x; i <= x + 2; ++i)
            for(int j = y; j <= y + 2; ++j)
                ans[i][j] = '#';
        ans[x + 1][y + 1] = '.';
        return;
    }
    else {
        int height = pow(3, n);
        int width = height;
        Print(n - 1, x, y);
        Print(n - 1, x, y + pow(3, n - 1));
        Print(n - 1, x, y + pow(3, n - 1) * 2);

        Print(n - 1, x + pow(3, n - 1), y);
        Print(n - 1, x + pow(3, n - 1), y + pow(3, n - 1) * 2);

        for(int i = pow(3, n - 1) + x; i <= x + pow(3, n - 1) * 2 - 1; ++i)
            for(int j = pow(3, n - 1) + y; j <= y + pow(3, n - 1) * 2 - 1; ++j)
                ans[i][j] = '.';

        Print(n - 1, x +  pow(3, n - 1) * 2, y);
        Print(n - 1, x +  pow(3, n - 1) * 2, pow(3, n - 1) + y);
        Print(n - 1, x +  pow(3, n - 1) * 2, y + pow(3, n - 1) * 2);
    }
}

int main() {
    int n = read();
    if(n == 0) {
        putchar('#');
        return 0;
    }
    Print(n, 1, 1);
    for(int i = 1; i <= pow(3, n); ++i) {
        for(int j = 1; j <= pow(3, n); ++j)
            putchar(ans[i][j]);
        putchar('\n');
    }
    return 0;
}