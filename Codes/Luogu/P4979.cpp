#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

int n, a[maxn];

class SegMent {
    private:
        class Tree {
            public:
                int l, r, mk;
                int col;
        };
        Tree T[maxn * 20];

        inline void Upd(int p) {
            int ls = p << 1, rs = (p << 1) | 1;
            T[p].col = (T[ls].col == T[rs].col) ? T[ls].col : -1;
        }

        inline void PushDn(int p) {
            if(!T[p].mk)
                return;
            int ls = p << 1, rs = (p << 1) | 1;
            int sl = T[p].mk;
            T[ls].mk = T[rs].mk = sl;
            T[ls].col = T[rs].col = sl;
            T[p].mk = 0;
            return;
        }

    public:
        inline void Build(int p, int l, int r) {
            T[p].l = l, T[p].r = r;
            if(l == r) {
                T[p].col = a[l];
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
                T[p].col = v, T[p].mk = v;
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
                return T[p].col;
            int mid = (T[p].l + T[p].r) >> 1;
            int ans = -1, res1 = -2, res2 = -2;
            if(l <= mid)
                res1 = Ask(p << 1, l, r);
            if(r > mid)
                res2 = Ask((p << 1) | 1, l, r);
            if(res1 == -2 or res2 == -2)
                ans = res1 + res2 + 2;
            else
                ans = (res1 == res2) ? res1 : -1;
            return ans;
        }
};

SegMent S;

string ss;
signed main() {

    // #define Areka
    #ifdef Areka
        freopen("hack.in", "r", stdin);
        freopen("w.out", "w", stdout);
    #endif


    n = read();

    for(int i = 1; i <= n; ++i) {
        char ch;
        cin >> ch;
        a[i] = ch - 'A' + 1;
    }
    a[n + 1] = a[n + 2] = 0;
    S.Build(1, 1, n + 1);

    int k = read();
    
    for(int i = 1; i <= k; ++i) {
        char opt;
        cin >> opt;
        if(opt == 'A') {
            int x = read(), y = read();
            char op;
            cin >> op;
            int v = op - 'A' + 1;
            S.Change(1, x, y, v);
        }
        if(opt == 'B') {
            int x = read(), y = read();
            int res1 = S.Ask(1, x - 1, x - 1), res2 = S.Ask(1, y + 1, y + 1);
            if(x == 1 or y == n) {
                int ans = S.Ask(1, x, y);
                if(ans < 0)
                    puts("No");
                else
                    puts("Yes");
                continue;
            }
            if(res1 == res2) {
                puts("No");
                continue;
            }
            int ans = S.Ask(1, x, y);
            if(ans < 0)
                puts("No");
            else
                puts("Yes");
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}