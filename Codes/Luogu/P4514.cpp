#include <bits/stdc++.h>

using namespace std;

#define ls p << 1
#define rs (p << 1) | 1

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2049;

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
                T[p].sum = 0, T[p].dt = 0;
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
};

class SegMent {
    public:
        Seg S;
};

SegMent a[2049];

int n, m;
char opt;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        a[i].S.Build(1, 1, m);
    while(cin >> opt) {
        if(opt == 'L') {
            int as = read(), b = read(), c = read(), d = read(), det = read();
            for(int i = as; i <= c; ++i)
                a[i].S.Change(1, b, d, det);
        }
        else {
            int res = 0;
            int as = read(), b = read(), c = read(), d = read();
            for(int i = as; i <= c; ++i)
                res += a[i].S.Ask(1, b, d);
            printf("%d\n", res);
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
