#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1010;

int a[maxn], vis[maxn];

int main() {
    int n, k, T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &k);
        int ans = 0;
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i)
            a[i] = i;
        for(int i = 1; i <= k; ++i) {
            int pp = i + 1;
            ans = 0; 
            for(int j = 1; j <= n; ++j)
                if(a[j] % pp == 0 && vis[j] == 0)
                    ans++, vis[j] = 1;
            printf("%d ", ans);
        }
        puts("");
    }
}