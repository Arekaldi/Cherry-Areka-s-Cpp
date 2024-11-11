#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

struct Node {
    int s, t;
};

Node c[100010];

int cmp(Node a, Node b) {
    if(a.t != b.t)
        return a.t < b.t;
    return a.s > b.s;
}

int main() {
    int T = read();
    while(T--) {
        int n = read();
        for(int i = 1; i <= n; i++)
            c[i].s = read(), c[i].t = read() + c[i].s;
        sort(c + 1, c + n + 1, cmp);
        int nowtime = c[1].t, ans = 1;
        for(int i = 2; i <= n; i++) {
            if(c[i].s >= nowtime) {
                nowtime = c[i].t;
                ans++;
            }
        }
        write(ans), putchar('\n');
    }
}