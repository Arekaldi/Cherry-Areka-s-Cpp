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

int gcd(int x, int y) {
    return y ? gcd(y, x % y) : x;
}

int main() {
    int T = read();
    while(T--) {
        int x = read(), y = read(), ans = 0;
        for(int i = x + 1; i < y; ++i) {
            ans = std :: max(ans, gcd(x, i) + gcd(y, i));
        }
        printf("%d\n", ans);
    }
}