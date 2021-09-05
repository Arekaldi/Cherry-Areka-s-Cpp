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

int T, n, a[maxn];

signed main() {
    T = read();

    while(T--) {
        n = read();

        int l = 1, r = n;

        for(int i = 1; i <= n; ++i)
            a[i] = read();

        for(int i = 1; i <= n; ++i) {
            l = i;
            if(a[i] != i)
                break;
        }

        for(int i = n; i >= l; --i) {
            r = i;
            if(a[i] != i)
                break;
        }

        int p1 = r, p2 = l; //p1为当前区间的左指针， p2为当前区间的右指针
        int h = 0, ans = 0;
        for(int i = l; i <= r; ++i) {
            if(a[i] != i) {
                h += (a[i] - i);
                p1 = min(p1, i), p2 = max(p2, i);
                if(h == 0) {
                    ans += p2 - p1 + 1;
                    p2 = l, p1 = r;
                }
            }
        }
        cout << ans << endl;
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
