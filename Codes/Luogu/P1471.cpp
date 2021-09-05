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

int n, m;
double a[maxn];

inline pair <double, double> operator + (const pair <double, double> &g, const pair <double, double> &f) {
    pair <double, double> ans;
    ans.first = g.first + f.first;
    ans.second = g.second + f.second;
    return ans;
}

class SegMentTree {
    private:
        class Tree {
            public:
                int l, r;
                double dt, sum1, sum2;
                double len;
        };
        Tree T[maxn * 4];
        #define ls p << 1
        #define rs (p << 1) | 1
    
        inline void PushDn(int p) {
            double d = T[p].dt;
            if(!d)
                return;
            double lenl = T[ls].len, lenr = T[rs].len;
            T[ls].sum2 += (d * d) * lenl + T[ls].sum1 * d * 2.0;
            T[rs].sum2 += (d * d) * lenr + T[rs].sum1 * d * 2.0;
            T[ls].sum1 += lenl * d, T[rs].sum1 += lenr * d;
            T[ls].dt += d, T[rs].dt += d;
            T[p].dt = 0.0;
            return;
        }
        
        inline void Upd(int p) {
            T[p].sum1 = T[ls].sum1 + T[rs].sum1;
            T[p].sum2 = T[ls].sum2 + T[rs].sum2;
            return;
        }

    public:
        inline void Build(int p, int l, int r) {
            T[p].l = l, T[p].r = r;
            T[p].len = r - l + 1.0;
            if(l == r) {
                T[p].sum1 = a[l], T[p].sum2 = a[l] * a[l];
                T[p].dt = 0;
                return;
            }
            int mid = (l + r) >> 1;
            Build(ls, l, mid);
            Build(rs, mid + 1, r);
            Upd(p);
            return;
        }

        inline void Add(int p, int l, int r, double v) {
            PushDn(p);
            if(T[p].l >= l and T[p].r <= r) {
                T[p].sum2 += T[p].len * v * v + T[p].sum1 * v * 2.0;
                T[p].sum1 += T[p].len * v;
                T[p].dt += v;
                return;
            }
            int mid = (T[p].l + T[p].r) >> 1;
            if(l <= mid)
                Add(ls, l, r, v);
            if(r > mid)
                Add(rs, l, r, v);
            Upd(p);
            return;
        }

        inline pair <double, double> Ask(int p, int l, int r) {
            PushDn(p);
            if(T[p].l >= l and T[p].r <= r)
                return make_pair(T[p].sum1, T[p].sum2);
            int mid = (T[p].l + T[p].r) >> 1;
            pair <double, double> res;
            if(l <= mid)
                res = res + Ask(ls, l, r);
            if(r > mid)
                res = res + Ask(rs, l, r);
            return res;
        }
};

SegMentTree S;

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        scanf("%lf", &a[i]);
    
    S.Build(1, 1, n);

    for(int i = 1; i <= m; ++i) {
        int opt = read(), x = read(), y = read();
        if(opt == 1) {
            double k; scanf("%lf", &k);
            S.Add(1, x, y, k);
        }
        else {
            pair <double, double> res = S.Ask(1, x, y);
            double ans;
            double ll = (double)(y - x + 1.0);
            double a1 = res.first, a2 = res.second;
            if(opt == 2)
                ans = a1 / ll;
            else
                ans = (a2 / ll) - (a1 / ll) * (a1 / ll);
            printf("%.4f\n", ans);
        }
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
