#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int a[maxn];
set < pair <int, int> > M;

signed main() {
    int T = read();
    for(int p = 1; p <= T; ++p) {
        int n = read();
        if(p == 1) {
            for(int i = 1; i <= n; ++i)
                a[i] = read();
        }
        else {
            for(int i = 1; i <= n; ++i) {
                int x = read(), y = read();
                a[x] = y;
            }
        }
        M.clear();
        for(int i = 1; i <= n; ++i)
            M.insert(make_pair(a[i], i));
        
        int flag = 0, ans;
        
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
