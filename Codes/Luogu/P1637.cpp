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

const int maxn = 1e6 + 1;

int n;

class Tree_Array {
    private:
        int t[maxn];
        inline int lowbit(int x) {
            return x & (-x);
        }
    public:
        inline void Add(int pos, int v) {
            if(pos <= 0)
                return;
            while(pos <= n) {
                t[pos] = (t[pos] + v);
                pos += lowbit(pos);
            }
        }

        inline int Ask(int pos) {
            if(pos <= 0)
                return 0;
            int res = 0;
            while(pos) {
                res = (res + t[pos]);
                pos -= lowbit(pos);
            }
            return res;
        }
};

Tree_Array T, T1;

int a[maxn], b[maxn];

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read(), b[i] = a[i];
    
    sort(b + 1, b + n + 1);
    int nn = unique(b + 1, b + n + 1) - b - 1;

    for(int i = 1; i <= n; ++i)
        a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;

    for(int i = n; i >= 2; --i)
        T1.Add(a[i], 1);

    T.Add(a[1], 1);
    int res = 0;
    for(int i = 2; i <= n; ++i) {
        res = (res + T.Ask(a[i] - 1) * (T1.Ask(n) - T1.Ask(a[i])));
        T.Add(a[i], 1);
        T1.Add(a[i], -1);
    }

    printf("%lld\n", res);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
