#include <stdio.h>

int n, T;
int a[5010], b[5010], b_end;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int ans = 0;
        b_end = 1;
        b[1] = 1e9 + 1;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            for(int j = 1; j <= b_end; ++j)
                if(a[i] < b[j]) {
                    ++b_end;
                    for(int k = b_end; k >= j + 1; --k)
                        b[k] = b[k - 1], ans++;
                    ans -= 1;
                    b[j] = a[i];
                    ans += j;
                    break;
                }
        }
        for(int j = 1; j <= n + 1; ++j)
            b[j] = 0;
        printf("%d\n", ans);
    }
}