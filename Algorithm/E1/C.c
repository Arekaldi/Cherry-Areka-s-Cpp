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


int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int a[1010], b[1010];

int main() {
    int n = read(), k = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    qsort(a + 1, n, sizeof(int), cmp);
    for(int i = 1; i <= n; ++i)
        b[i] = b[i - 1] + a[i];
    int p1 = 1, p2 = 1, ans = 0;
    while(p1 <= n) {
        while(a[p2] - a[p1] <= k && p2 <= n)
            p2++;
        p2--;
        if(ans < b[p2] - b[p1 - 1])
            ans = b[p2] - b[p1 - 1];
        p1++;
    }
    write(ans);
    puts("");
    return 0;
}