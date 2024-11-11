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

int Tree_Array[400010];

int n;

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int val) {
    if(x == 0)
        return;
    while(x <= n) {
        Tree_Array[x] += val;
        x += lowbit(x);
    }
    return;
}

int query(int x) {
    int sum = 0;
    while(x > 0) {
        sum += Tree_Array[x];
        x -= lowbit(x);
    }
    return sum;
}

int a[100010], lst[100010], pos[100010];
int ansl = -1, ansr;
int k;

int All_Kind(int len) {
    int now = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = now; j <= i + len - 1; ++j) {
            if(lst[j])
                add(lst[j], -1);
            add(j, 1);
        }
        now = i + len;
        int cnt = query(i + len - 1) - query(i - 1);
        if(cnt == k) {
            ansl = i, ansr = i + len - 1;
            return 1;
        }
    }
    return 0;
}

int main() {
    int T = read();
    while(T--) {
        n = read(), k = read();
        memset(Tree_Array, 0, sizeof(Tree_Array));
        memset(pos, 0, sizeof(pos));
        memset(lst, 0, sizeof(lst));
        for(int i = 1; i <= n; ++i)
            a[i] = read();
        for(int i = 1; i <= n; ++i) {
            if(pos[a[i]] == 0) {
                pos[a[i]] = i;
            }
            else {
                lst[i] = pos[a[i]];
                pos[a[i]] = i;
            }
        }
        int l = 1, r = k, now = 1;
        ansl = -1, ansr = -1;
        while(r <= n) {
            for(int j = now; j <= r; ++j) {
                if(lst[j])
                    add(lst[j], -1);
                add(j, 1);
            }
            now = r + 1;
            int cnt = query(r) - query(l - 1);
            if(cnt == k) {
                if(r - l + 1 < ansr - ansl + 1 || ansl == -1)
                    ansl = l, ansr = r;
                else if(r - l + 1 == ansr - ansl + 1 && ansl > l)
                    ansl = l, ansr = r;
                l++;
                if(r - l + 1 < k)
                    r++;
            }
            else if(cnt < k) {
                r++;
            }
            else {
                l++;
            }
        }
        if(ansl == -1)
            printf("N0\n");
        else
            printf("%d %d\n", ansl, ansr);
    }
}