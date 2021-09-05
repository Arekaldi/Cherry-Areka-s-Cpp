#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e2 + 1;

int n, k, T;
bool vis[maxn];

signed main() {
    T = read();
    while(T--) {
        n = read(), k = read();
        memset(vis, 0, sizeof(vis));
        if(n < 64 and (1ll << (n - 1)) < k) {
            puts("-1");
            continue;
        }
        for(int i = 1; i <= n - 63; ++i)
            cout << i << " ";
        int l = n;
        n = min(n, 63ll);
        int c = l - n;
        for(int i = 1; i <= n; ++i) {
            int ans = -1;
            for(int j = 1; j <= n; ++j) {
                if(!vis[j]) {    
                    int cnt = max(1ll << (n - j - 1), 1ll);
                    if(k <= cnt) {
                        ans = j;
                        break;
                    }
                    k -= cnt;
                }
            }
            if(ans == -1)
                continue;
            vis[ans] = true;
            cout << ans + c << " ";
            for(int j = ans - 1; j >= 1; --j)
                if(!vis[j])
                    vis[j] = true, cout << j + c << " ";
        }
        cout << endl;
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
