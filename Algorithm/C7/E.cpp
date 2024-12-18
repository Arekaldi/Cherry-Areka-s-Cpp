#include <stdio.h>
#include <algorithm>

class Class{
    public:
        int l, r;
        bool operator < (const Class &b) {
            return r == b.r ? l > b.l : r < b.r;
        }
};

const int maxn = 1e5 + 1;
int n, k, T;

Class c[maxn];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &k);
        for(int i = 1; i <= k; ++i)
            scanf("%d %d", &c[i].l, &c[i].r);
        
        std :: sort(c + 1, c + k + 1);
        int now = 0, ans = 0;
        for(int i = 1; i <= k; ++i) {
            if(now < c[i].l)
                ans++, now = c[i].r;
        }
        printf("%d\n", ans);
    }
}