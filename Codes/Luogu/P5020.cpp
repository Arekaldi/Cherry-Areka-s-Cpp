#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e4 + 1;

int n, a[maxn];

bool f[maxn];

signed main() {
    int T = read();
    while(T--) {
        n = read();
        memset(f, false, sizeof(f));
        int m = n;
        for(int i = 1; i <= n; ++i)
            a[i] = read();
        sort(a + 1, a + n + 1);
        // 因为 B <= A
        f[0] = 1;
        for(int i = 1; i <= n; ++i) {
            if(f[a[i]] != 0)
                // 如果 a[i] 能被表示出
                m--;
            else
                for(int j = a[i]; j <= a[n]; ++j)
                    f[j] = f[j] | f[j - a[i]];
        }
        printf("%d\n", m);
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
