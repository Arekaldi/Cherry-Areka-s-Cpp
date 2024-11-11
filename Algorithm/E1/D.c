#include <assert.h>
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

int a[100010];

int main() {
    int t = read();
    while(t--) {
        memset(a, 0, sizeof(a));
        int n = read();
        for(int i = 1; i <= n; ++i)
            a[i] = read();
        qsort(a + 1, n, sizeof(int), cmp);
        int a1 = a[1], a2 = a[1];
        for(int i = 2; i <= n; ++i) {
            if(a[i] != a1 && a[i] % a1 != 0) {
                a2 = a[i];
                break;
            }
        }
        int flag = 0;
        for(int i = 1; i <= n; ++i) {
            if(a[i] % a1 == 0 || a[i] % a2 == 0)
                continue;
            flag = 1;
            break;
        }
        if(flag)
            puts("No");
        else
            puts("Yes");
    }
    return 0;
}