#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

#define int long long

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

int T, n;

struct Node {
    int x, y;
    bool operator < (const Node &b) {
        return x == b.x ? y < b.y : x < b.x;
    }
};

Node a[100010];

signed main() {
    T = read();
    while(T--) {
        n = read();
        for(int i = 1; i <= n; i++) {
            a[i].x = read();
            a[i].y = read();
        }
        int flag = 1;
        std :: sort(a + 1, a + n + 1);
        for(int i = 3; i <= n; ++i) {
            int x1 = a[i - 2].x, x2 = a[i - 1].x;
            int y1 = a[i - 2].y, y2 = a[i - 1].y;
            int x = a[i].x, y = a[i].y;
            if((x - x1) * (y2 - y1) != (y - y1) * (x2 - x1)) {
                puts("how?");
                flag = 0;
                break;
            }
        }
        if(flag)
            puts("boo how! boo how!");
    }
    return 0;
}