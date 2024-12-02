#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cmath>

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

const int maxn = 1 << 11;

int dataIndex[maxn], a[maxn];

int main() {
    int n = read();
    int l = log2(n);
    for(int i = 0; i < n; ++i)
        a[i] = read();
    for(int i = 0; i < n; ++i)
        dataIndex[i] = dataIndex[i >> 1] >> 1 | ((i & 1) << (l - 1));
    for(int i = 0; i < n; ++i)
        printf("%d ", a[dataIndex[i]]);
    return 0;
}