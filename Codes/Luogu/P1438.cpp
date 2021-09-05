#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ls p << 1
#define rs (p << 1) | 1

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e7 + 1;

int b[maxn], a[maxn];

class Seg {
    private:
        class Tree {
            public:
                int l, r, dt, sum;
        };

        Tree T[maxn * 4];

        inline void Upd(int p) {
            T[p].sum = T[ls].sum + T[rs].sum;
        }

        inline void Pushdn(int p) {
            int d = T[p].dt;
            if(!d)
                return;
            T[ls].dt += d, T[rs].dt += d;
            T[ls].sum += (T[ls].r - T[ls].l + 1) * d;
            T[rs].sum += (T[rs].r - T[rs].l + 1) * d;
            T[p].dt = 0;
            return;
        }

    public:
        inline void Build(int p, int l, int r) {
            T[p].l = l, T[p].r = r;
            if(l == r) {
                T[p].sum = a[l], T[p].dt = 0;
                return;
            }
            int mid = (l + r) >> 1;
            Build(ls, l, mid);
            Build(rs, mid + 1, r);
            Upd(p);
            return;
        }

        inline void Change(int p, int l, int r, int v) {
            Pushdn(p);
            if(T[p].l >= l and T[p].r <= r) {
                T[p].sum += (T[p].r - T[p].l + 1) * v;
                T[p].dt += v;
                return;
            }
            int mid = (T[p].l + T[p].r) >> 1;
            if(l <= mid)
                Change(ls, l, r, v);
            if(r > mid)
                Change(rs, l, r, v);
            Upd(p);
            return;
        }

        inline int Ask(int p, int l, int r) {
            Pushdn(p);
            if(T[p].l >= l and T[p].r <= r)
                return T[p].sum;
            int mid = (T[p].l + T[p].r) >> 1, res = 0;
            if(l <= mid)
                res += Ask(ls, l, r);
            if(r > mid)
                res += Ask(rs, l, r);
            return res;
        }
}S;

signed main() {
    int n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        b[i] = read();

    for(int i = 1; i <= n; ++i)
        a[i] = b[i] - b[i - 1];

    S.Build(1, 1, n + 1);

    for(int i = 1; i <= m; ++i) {
        int opt = read();
        if(opt == 1) {
            int l = read(), r = read(), s = read(), d = read();
            int e = s + (r - l) * d;
            S.Change(1, l + 1, r, d);
            S.Change(1, l, l, s);
            S.Change(1, r + 1, r + 1, -e);
        }
        else {
            int p = read();
            printf("%lld\n", S.Ask(1, 1, p));
        }
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
