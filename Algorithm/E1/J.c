#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define int long long

int T;

signed main() {
    scanf("%lld", &T);
    while(T--) {
        int p, q;
        scanf("%lld %lld", &p, &q);
        if(q == 1)
            printf("%lld %lld\n", 1ll, p + 1);
        else if(q == 2)
            printf("%lld %lld\n", q, p);
        else if(p < q)
            printf("%lld %lld\n", q, q - p);
        else {
            int num = p / q;
            printf("%lld %lld\n", q, 2ll * (num) * q + q - p);
        }
    }
}