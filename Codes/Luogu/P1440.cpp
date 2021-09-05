#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e6 + 1;

int n, m;
int a[maxn];

const int Inf = (1 << 30);

inline int Min(int a, int b) {
    if(a == b) return a;
    if(a > b) return b;
    return a;
}

class Segment_Tree {
    private :
        class Tree {
            public :
                int l, r;
                int dat;
            #define Ls p << 1
            #define Rs p << 1 | 1
        }T[maxn << 2];

        inline void Upd(int p) {
            T[p].dat = Min(T[Ls].dat, T[Rs].dat);
        }

    public :

        inline void Build(int p, int L, int R) {
            T[p].l = L, T[p].r = R;
            if(L == R) {
                T[p].dat = a[L];
                return;
            }
            int mid = (L + R) >> 1;
            Build(Ls, L, mid);
            Build(Rs, mid + 1, R);
            Upd(p);
            return;
        }

        inline void Ask(int p, int L, int R, int& ans) {
            if(T[p].l >= L and T[p].r <= R) {
                ans = Min(ans, T[p].dat);
                return;
            }

            int mid = (T[p].l + T[p].r) >> 1;

            if(L <= mid)
                Ask(Ls, L, R, ans);
            if(R > mid)
                Ask(Rs, L, R, ans);
            
            return;
        }
}S;

signed main() {
    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    S.Build(1, 1, n);
    
    for(int i = 1; i <= n; ++i) {
        if(i == 1) {
            puts("0");
            continue;
        }
        else {
            int ans = (1 << 30);
            S.Ask(1, i - m <= 0 ? 1 : i - m, i - 1, ans);
            printf("%d\n", ans);
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
