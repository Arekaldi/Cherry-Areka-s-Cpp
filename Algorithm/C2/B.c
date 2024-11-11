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

long long a[200010];
int n, T;
int max1, max2;

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    T = read();
    while(T--) {
        n = read();
        for(int i = 1; i <= n; i++)
            a[i] = read();
        qsort(a + 1, n, sizeof(long long), cmp);
        printf("%lld\n", a[n - 1] + a[n]);
    }
    return 0;
}