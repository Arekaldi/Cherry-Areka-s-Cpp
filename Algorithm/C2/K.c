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


int a[100010];

struct Query {
    int l, r, id, ans;
};

int cmp(const void *a, const void *b) {
    struct Query *p = (struct Query *)a,
                 *q = (struct Query *)b;
    if(p->l != q->l)
        return p->l - q->l;
    else
        return p->r - q->r;
}

int cmp2(const void *a, const void *b) {
    struct Query *p = (struct Query *)a,
                 *q = (struct Query *)b;
    return p->id - q->id;
}

struct Query ques[100010];

int main() {
    int T = read();
    while(T--) {
        memset(ques, 0, sizeof(ques));
        int n = read(), q = read();
        for(int i = 1; i <= n; ++i)
            a[i] = read();
        for(int i = 1; i <= q; ++i)
            ques[i].l = read(), ques[i].r = read(),
            ques[i].id = i;
        qsort(ques + 1, q, sizeof(struct Query), cmp);
        int res = 0;
        int l = ques[1].l, r = ques[1].r;
        for(int i = l; i <= r; ++i)
            res ^= a[i];
        ques[1].ans = res != 0;
        for(int i = 2; i <= q; ++i) {
            int ll = ques[i].l, rr = ques[i].r;
            while(l < ll)
                res ^= a[l++];
            while(r < rr)
                res ^= a[++r];
            ques[i].ans = res != 0;
        }
        qsort(ques + 1, q, sizeof(struct Query), cmp2);
        for(int i = 1; i <= q; ++i)
            printf(ques[i].ans ? "YES\n" : "NO\n");
    }
}