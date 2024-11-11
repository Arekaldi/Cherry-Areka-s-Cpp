#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long read(void) {
    long long x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(long long x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

#define int long long

int pri[10010];
int dp[10010];
int road[10010];

int max2(int a, int b) {
    return a > b? a : b;
}

int cnt;
int out[10010];
void printRoad(int n, int k) {
    if(road[n] == n) {
        out[++cnt] = k;
        return;
    }
    printRoad(k, road[k]);
    printRoad(n - k, road[n - k]);
}

signed main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        pri[i] = read();
    for(int i = 1; i <= n; ++i)
        dp[i] = pri[i], road[i] = i;
    for(int i = 2; i <= n; ++i) {
        for(int k = 1; k < i; ++k) {
            if(dp[k] + dp[i - k] > dp[i]) {
                road[i] = k;
                dp[i] = dp[k] + dp[i - k];
            }
        }
    }
    write(dp[n]);
    printRoad(n, road[n]);
    printf("\n%d\n", cnt);
    for(int i = 1; i <= cnt; ++i)
        printf("%d ", out[i]);
    return 0;
}