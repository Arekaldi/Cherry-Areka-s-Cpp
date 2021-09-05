#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e6 + 1;

int n, a[maxn];
unsigned long long c[maxn];

class Tree_Array {
    private:
        unsigned long long t[maxn];
    public:
        inline int lowbit(int x) {
            return (x & (-x));
        }
        inline void Add(int pos, unsigned long long x) {
            while(pos <= n) {
                t[pos] += x;
                pos += lowbit(pos);
            }
            return;
        }
        inline unsigned long long Ask(int pos) {
            unsigned long long ans = 0;
            while(pos) {
                ans += t[pos];
                pos -= lowbit(pos);
            }
            return ans;
        }
};

Tree_Array T1, T2;

inline bool check(int x) {
    int len = min(x, n - x + 1);
    unsigned long long u = T1.Ask(x) - T1.Ask(x - len);
    unsigned long long v = T2.Ask(x + len - 1) - T2.Ask(x - 1);
    T1.Add(x, c[x]), T2.Add(x, c[n - x + 1]);
    return u * c[n - x - len + 2] != v * c[x - len + 1];
}

signed main() {

    #define Areka
    #ifdef Areka
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif

    n = read();

    c[0] = 1;
    for(int i = 1; i <= n; ++i) {
        a[i] = read();
        c[i] = c[i - 1] * 131;
    }

    for(int i = 1; i <= n; ++i)
        if(check(a[i])) {
            puts("YES");
            return 0;
        }
    puts("NO");
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
