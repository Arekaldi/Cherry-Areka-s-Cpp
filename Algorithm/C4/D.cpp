#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <queue>

#define int long long

using namespace std;

priority_queue <int, vector<int>, greater<int> > q;

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

int n;
int lenAll;
int len[200010], sum[200010];

int cmp(int a, int b) {
    return a > b;
}

signed main() {
    n = read();
    for(int i = 1; i <= n; i++)
        len[i] = read(), lenAll += len[i], q.push(len[i]);
    sort(len + 1, len + 1 + n, cmp);
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + len[i];
    int ans = 0;
    while(q.size() > 1) {
        int now1 = q.top();
        q.pop();
        int now2 = q.top();
        q.pop();
        ans += 2 * (now1 + now2);
        q.push(now1 + now2);
    }
    printf("%lld\n", ans);
    return 0;
}