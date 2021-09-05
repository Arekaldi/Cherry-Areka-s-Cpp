#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e6 + 1;

int n, m;
int a[maxn];

class SegMent {
    private:
        class Tree {
            public:
                int l, r;
                int minx, sum;
                int ad;
        };
        Tree T[maxn * 20];

        inline void Upd(int p) {
            T[p].minx = min(T[p << 1].minx, T[(p << 1) | 1].minx);
            T[p].sum = (T[p << 1].sum + T[(p << 1) | 1].sum);
        }

        inline void Pushdown(int p) {
            int l = p << 1, r = (p << 1) | 1;
            int d = T[p].ad;
            if(T[p].l == T[p].r) {
                T[p].ad = 0;
                return;
            }
            if(T[p].ad and T[p].l != T[p].r) {
                // if(p == 3) {
                    // cout << T[p].ad << endl;
                // }
                T[l].sum += (T[l].r - T[l].l + 1) * d, T[l].ad += d, T[l].minx += d;
                T[r].sum += (T[r].r - T[r].l + 1) * d, T[r].ad += d, T[r].minx += d;
                T[p].ad = 0;
                Upd(p);
            }
            return;
        }
    public:
        inline void Build(int p, int l, int r) {
            T[p].l = l, T[p].r = r;
            if(l == r) {
                T[p].minx = T[p].sum = a[l];
                return;
            }
            int mid = (l + r) >> 1;
            Build(p << 1, l, mid);
            Build((p << 1) | 1, mid + 1, r);
            Upd(p);
            return;
        }

        inline void Change(int p, int l, int r, int v) {
            Pushdown(p);
            if(l <= T[p].l and r >= T[p].r) {
                T[p].ad += v, T[p].sum += (T[p].r - T[p].l + 1) * v, T[p].minx += v;
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

        inline int Ask(int p, int l, int r, int opt) {
            Pushdown(p);
            if(T[p].l >= l and T[p].r <= r)
                return opt ? T[p].minx : T[p].sum;

            int mid = (T[p].l + T[p].r) >> 1;
            int ans = (1 << 30), res = 0;

            if(l <= mid) {
                ans = opt ? min(ans, Ask(p << 1, l, r, opt)) : 0;
                res = !opt ? res + Ask(p << 1, l, r, opt) : 0;
            }
            if(r > mid) {
                ans = opt ? min(ans, Ask((p << 1) | 1, l, r, opt)) : 0;
                res = !opt ? res + Ask((p << 1) | 1, l, r, opt) : 0;
            }
            return opt ? ans : res;
        }
};

SegMent S;

// 28467695240

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("s.in", "r", stdin);
        freopen("w.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    S.Build(1, 1, n);

    for(int i = 1; i <= m; ++i) {
        char opt;
        int l, r, v;
        scanf("%c", &opt);
        if(opt == 'M') {
            l = read(), r = read();
            // printf("%lld\n", S.Ask(1, l, r, 1));
            cout << S.Ask(1, l, r, 1) << endl;
        }
        else if(opt == 'P') {
            l = read(), r = read(), v = read();
            S.Change(1, l, r, v);
        }
        else {
            l = read(), r = read();
            // printf("%lld\n", S.Ask(1, l, r, 0));
            cout << S.Ask(1, l, r, 0) << endl;
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}


/*
3 2 3 4
*/