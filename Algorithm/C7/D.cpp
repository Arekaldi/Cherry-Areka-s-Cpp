/* 
 Author: 李一鸣
 Result: AC	Submission_id: 7175564
 Created at: Wed Dec 11 2024 19:30:11 GMT+0800 (China Standard Time)
 Problem_id: 8941	Time: 285	Memory: 2460
*/

#include <stdio.h>
#include <algorithm>

const int maxn = 1e5 + 1;

int a[maxn], b[maxn];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);

    std :: sort(a + 1, a + n + 1);
    std :: sort(b + 1, b + n + 1);

    int p = 1, q = 1, ans = 0;
    while(p <= n && q <= n) {
        while(a[p] >= b[q] && q <= n)
            q++;
        p++, q++, ans++;
    }
    printf("%d\n", ans);
    return 0;
}