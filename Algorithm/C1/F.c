#include <stdio.h>

#define int long long

struct Node {
    int mul, num;
};

struct Node a[100010], b[100010], c[100010];

int Node_tot = 0;

int n, m, t;

int main() {
    scanf("%lld", &t);
    while(t--) {
        Node_tot = 0;
        scanf("%lld", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%lld", &a[i].mul);
        for(int i = 1; i <= n; ++i)
            scanf("%lld", &a[i].num);
        scanf("%lld", &m);
        for(int i = 1; i <= m; ++i)
            scanf("%lld", &b[i].mul);
        for(int i = 1; i <= m; ++i)
            scanf("%lld", &b[i].num);
        Node_tot = 0;
        int i = 1, j = 1;
        while(i <= n && j <= m) {
            while(i <= n && a[i].num < b[j].num)
                c[++Node_tot] = a[i++];
            while(j <= m && b[j].num < a[i].num)
                c[++Node_tot] = b[j++];
            if(i <= n && j <= m && a[i].num == b[j].num) {
                c[++Node_tot] = (struct Node){a[i].mul + b[j].mul, a[i].num};
                i++, j++;
            }
        }
        if(i > n && j <= m) {
            while(j <= m)
                c[++Node_tot] = b[j++];
        }
        if(j > m && i <= n) {
            while(i <= n)
                c[++Node_tot] = a[i++];
        }
        int ans = 0;
        for(int i = 1; i <= Node_tot; ++i)
            ans += c[i].mul != 0;
        printf("%lld\n", ans);
        for(int i = 1; i <= Node_tot; ++i) {
            if(c[i].mul != 0)
                printf("%lld ", c[i].mul);
        }
        puts("");
        for(int i = 1; i <= Node_tot; ++i) {
            if(c[i].mul != 0)
                printf("%lld ", c[i].num);
        }
        puts("");
    }
}