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

const int maxn = 2e5 + 1;

int n;
class Tree_Array {
    private:
        int t[maxn];
        inline int lowbit(int x) {
            return x & (-x);
        }

    public:
        inline void Add(int pos, int v) {
            while(pos <= n)
                t[pos] += v, pos += lowbit(pos);
            return;
        }
        inline int Ask(int pos) {
            int res = 0;
            while(pos)
                res += t[pos], pos -= lowbit(pos);
            return res;
        }
};

Tree_Array T;
int a[maxn], t[maxn];

int pre[maxn], nxt[maxn];

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("w.out", "w", stdout);
    #endif

    
    n = read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read(), T.Add(i, a[i]);
        nxt[i] = i + 1, pre[i] = i - 1;
    }
    
    for(int i = 1; i <= n; ++i) {
        if(a[i] == 1) {
            int x = pre[i], y = nxt[i];
            nxt[x] = nxt[i], pre[y] = pre[i];
        }
    }

    nxt[n] = n + 1;

    int m = read();
    for(int i = 1; i <= m; ++i) {
        int k = read(), l = read(), r = read();
        if(l > r)
            swap(l, r);
        if(k == 0) {
            for(int x, i = l; i <= r; i = nxt[i]) {
                x = sqrt(a[i]), T.Add(i, x - a[i]), a[i] = x;
                if(x == 1) {
                    int xx = pre[i], yy = nxt[i];
                    nxt[xx] = yy, pre[yy] = xx;
                }
            }
        }
        else
            printf("%lld\n", T.Ask(r) - T.Ask(l - 1));
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
