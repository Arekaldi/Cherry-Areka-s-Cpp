#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

using namespace std;

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

int n, m, a[100010], vis[100010];

int main() {
    int t = read();
    while(t--) {
        n = read(), m = read();
        for(int i = 1; i <= n; i++)
            a[i] = read();
        sort(a + 1, a + n + 1);
        int p = n, ans = 0;
        for(int i = 1; i < p; ++i) {
            while(a[i] + a[p--] > m);
            p++;
            if(i == p)
                break;
            vis[i] = vis[p--] = 1;
            ans++;
        }
        for(int i = 1; i <= n; ++i)
            ans += !vis[i];
        write(ans), putchar('\n');
        memset(vis, 0, sizeof(vis));
    }
}