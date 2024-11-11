#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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


int n, q;
int a[1000010];

int cmp(const void *a1, const void *b1) {
    int a2 = *(int*)a1;
    int b = *(int*)b1;
    return a2 - b;
}

int main() {
    n = read(), q = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    qsort(a + 1, n, sizeof(int), cmp);
    for(int i = 1; i <= q; ++i) {
        int d = read(), k = read();
        if(a[1] / d > k) {
            write(0);
            putchar('\n');
            continue;
        }
        if(a[n] / d < k) {
            write(0);
            putchar('\n');
            continue;
        }
        if(a[1] / d == k && a[n] / d == k) {
            write(n);
            putchar('\n');
            continue;
        }
        int l = 1, r = n, mid, ans1 = -1, ans2 = -1;
        while(l <= r) {
            mid = (l + r) >> 1;
            if(a[mid] / d == k)
                r = mid - 1, ans1 = mid;
            else if(a[mid] / d < k)
                l = mid + 1;
            else if(a[mid] / d > k)
                r = mid - 1;
        }
        l = 1, r = n;
        while(l <= r) {
            mid = (l + r) >> 1;
            if(a[mid] / d == k)
                l = mid + 1, ans2 = mid;
            else if(a[mid] / d < k)
                l = mid + 1;
            else if(a[mid] / d > k)
                r = mid - 1;
        }
        if(ans1 == -1 && ans2 == -1) {
            write(0);
            putchar('\n');
            continue;
        }
        write(ans2 - ans1 + 1);
        putchar('\n');
        // printf("%lld %lld\n", ans1, ans2);
    }
}