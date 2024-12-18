#include <stdio.h>
#include <stack>
#include <string.h>

const int maxn = 1e4 + 1;
std :: stack <int> s;
int p[maxn], vis[maxn];

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        while(!s.empty())
            s.pop();
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i)
            scanf("%d", &p[i]);
        int flag = 1;
        for(int i = 1; i <= n; ++i) {
            if(!vis[p[i]]) {
                for(int j = 1; j <= p[i]; ++j) {
                    if(!vis[j])
                        s.push(j), vis[j] = 1;
                }
                s.pop();
            }
            else {
                if(s.top() != p[i]) {
                    flag = 0;
                    break;
                }
                s.pop();
            }
        }
        puts(flag ? "YES" : "NO");
    }
}