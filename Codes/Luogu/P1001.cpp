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

int n, m;
int a[maxn];

class Segment_Tree {
    private :
        class Tree {
            public :
                int l, r;
                int Mark, sum;
            #define Ls p << 1
            #define Rs p << 1 | 1
        }T[maxn << 2];

        inline void Upd(int p) {
            T[p].sum = T[Ls].sum + T[Rs].sum;
        }

        inline void Spread(int p) {
            T[Ls].sum += T[p].Mark * (T[Ls].r - T[Ls].l + 1);
            T[Rs].sum += T[p].Mark * (T[Rs].r - T[Rs].l + 1);
            T[Ls].Mark += T[p].Mark;
            T[Rs].Mark += T[p].Mark;
            T[p].Mark = 0;
        }

    public :

        inline void Build(int p, int L, int R) {
            T[p].l = L, T[p].r = R;
            if(L == R) {
                T[p].sum = a[L];
                T[p].Mark = 0;
                return;
            }
            int mid = (L + R) >> 1;
            Build(Ls, L, mid);
            Build(Rs, mid + 1, R);
            Upd(p);
            return;
        }

        inline void Add(int p, int L, int R, int k) {
            if(T[p].l >= L and T[p].r <= R) {
                T[p].sum += k * (T[p].r - T[p].l + 1);
                T[p].Mark += k;
                return;
            }
            Spread(p);
            int mid = (T[p].l + T[p].r) >> 1;
            if(L <= mid)
                Add(Ls, L, R, k);
            if(R > mid)
                Add(Rs, L, R, k);
            Upd(p);
            return;
        }

        inline int Ask(int p, int L, int R) {
            if(T[p].l >= L and T[p].r <= R) 
                return T[p].sum;
            
            Spread(p);
            int mid = (T[p].l + T[p].r) >> 1;
            int ans = 0;
            if(L <= mid)
                ans += Ask(Ls, L, R);
            if(R > mid)
                ans += Ask(Rs, L, R);
            
            return ans;
        }
}S;

signed main() {
    n = 2, m = 1;

    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    S.Build(1, 1, n);

    for(int i = 1; i <= m; ++i) {
        int opt = 2, x = 1, y = 2;
        switch(opt) {
            case 1 : {
                int k = read();
                S.Add(1, x, y, k);
                break;
            }
            case 2 : {
                printf("%lld\n", S.Ask(1, x, y));
                break;
            }
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
