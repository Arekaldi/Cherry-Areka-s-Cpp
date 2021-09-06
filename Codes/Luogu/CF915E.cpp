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

int n, cnt, Rt;

class SegMentTree {
    private:
        class Tree {
            public:
                int sum, ad;
                int ls, rs;
                #define ls T[p].ls
                #define rs T[p].rs
        };

        #define ls T[p].ls
        #define rs T[p].rs
        Tree T[maxn * 15];

        inline void Upd(int p) {
            T[p].sum = T[ls].sum + T[rs].sum;
        }

        inline void PushDown(int p, int L, int R) {
            if(T[p].ad == -1)
                return;
            int d = T[p].ad, mid = (L + R >> 1);
            if(!ls)
                ls = ++cnt;
            if(!rs)
                rs = ++cnt;
            T[ls].ad = d, T[ls].sum = d * (mid - L + 1);
            T[rs].ad = d, T[rs].sum = d * (R - (mid + 1) + 1);
            T[p].ad = -1;
            return;
        }

    public:
        inline void Change(int &p, int L, int R, int l, int r, int v) {
            if(!p)
                p = ++cnt;
            if(L >= l and R <= r) {
                T[p].sum = (R - L + 1) * v;
                T[p].ad = v;
                return;
            }
            PushDown(p, L, R);
            int mid = (L + R >> 1);
            if(l <= mid)
                Change(ls, L, mid, l, r, v);
            if(r > mid)
                Change(rs, mid + 1, R, l, r, v);
            Upd(p);
            return;
        }

        inline int Ask() {
            return T[Rt].sum;
        }
};

SegMentTree T;

signed main() {
    n = read();
    int q = read();
    for(int i = 1; i <= q; ++i) {
        int l = read(), r = read(), opt = read();
        T.Change(Rt, 1, n, l, r, 2 - opt);
        printf("%d\n", n - T.Ask());
    }

    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
