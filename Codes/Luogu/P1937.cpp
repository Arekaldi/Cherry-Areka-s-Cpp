#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int n, m, a[maxn];

class SegMent {
    private:
        class Tree {
            public:
                int mn, l, r, mk;
        };
        Tree T[maxn * 10];

        inline void Upd(int p) {
            T[p].mn = min(T[p << 1].mn, T[(p << 1) | 1].mn);
        }

        inline void PushDn(int p) {
            int ls = p << 1, rs = (p << 1) | 1;
            if(!T[p].mk)
                return;
            if(T[p].l == T[p].r) {
                T[p].mk = 0;
                return;
            }
            T[ls].mk += T[p].mk, T[rs].mk += T[p].mk;
            T[ls].mn += T[p].mk, T[rs].mn += T[p].mk;
            T[p].mk = 0;
            return;
        }

    public:
        inline void Build(int p, int l, int r) {
            T[p].l = l, T[p].r = r;
            if(l == r) {
                T[p].mn = a[l];
                T[p].mk = 0;
                return;
            }
            int mid = (l + r) >> 1;
            Build(p << 1, l, mid);
            Build((p << 1) | 1, mid + 1, r);
            Upd(p);
            return;
        }
        
        inline void Change(int p, int l, int r, int v) {
            PushDn(p);
            if(T[p].l >= l and T[p].r <= r) {
                T[p].mn += v, T[p].mk += v;
                return;
            }
            int mid = (T[p].l + T[p].r) >> 1;
            if(l <= mid)
                Change(p << 1, l, r, v);
            if(r > mid)
                Change((p << 1) | 1, l, r, v);
            Upd(p);
            return;
        }

        inline int Ask(int p, int l, int r) {
            PushDn(p);
            if(T[p].l >= l and T[p].r <= r)
                return T[p].mn;
            int mid = (T[p].l + T[p].r) >> 1;
            int ans = (1 << 30);

            if(l <= mid)
                ans = min(ans, Ask(p << 1, l, r));
            if(r > mid)
                ans = min(ans, Ask((p << 1) | 1, l, r));
            return ans;
        }
};


SegMent S;

class Cow {
    public:
        int l, r, len;
        inline bool operator < (const Cow &a) const {
            if(a.r == r)
                return a.l < l;
            return a.r > r;
        }
};

Cow c[maxn];

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("w.txt", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();

    S.Build(1, 1, n);

    int ans = 0;
    for(int i = 1; i <= m; ++i)
        c[i].l = read(), c[i].r = read();
    
    sort(c + 1, c + m + 1);
    
    for(int i = 1; i <= m; ++i) {
        if(S.Ask(1, c[i].l, c[i].r) > 0) {
            ans++;
            S.Change(1, c[i].l, c[i].r, -1);
        }
    }

    printf("%d\n", ans);

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
