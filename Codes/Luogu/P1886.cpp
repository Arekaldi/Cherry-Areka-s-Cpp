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

inline int Max(int a, int b) {
    if(a == b) return a;
    if(a > b) return a;
    return b;
}

class Segment_Tree {
    private :
        class Tree {
            public :
                int l, r;
                int dat1, dat2;
            #define Ls p << 1
            #define Rs p << 1 | 1
        }T[maxn << 2];

        inline void Upd(int p) {
            T[p].dat1 = Min(T[Ls].dat1, T[Rs].dat1);
            T[p].dat2 = Max(T[Ls].dat2, T[Rs].dat2);
        }

    public :

        inline void Build(int p, int L, int R) {
            T[p].l = L, T[p].r = R;
            if(L == R) {
                T[p].dat1 = T[p].dat2 = a[L];
                return;
            }
            int mid = (L + R) >> 1;
            Build(Ls, L, mid);
            Build(Rs, mid + 1, R);
            Upd(p);
            return;
        }

        inline void Ask(int p, int L, int R, int& ans1, int& ans2) {
            if(T[p].l >= L and T[p].r <= R) {
                ans1 = Min(ans1, T[p].dat1);
                ans2 = Max(ans2, T[p].dat2);
                return;
            }

            int mid = (T[p].l + T[p].r) >> 1;

            if(L <= mid)
                Ask(Ls, L, R, ans1, ans2);
            if(R > mid)
                Ask(Rs, L, R, ans1, ans2);
            
            return;
        }
}S;

queue <int> Q1, Q2;

signed main() {
    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    S.Build(1, 1, n);
    
    for(int i = 1; i + m - 1 <= n; ++i) {
        int ans1 = (1 << 30), ans2 = -(1 << 30);
        S.Ask(1, i, i + m - 1, ans1, ans2);
        Q1.push(ans1), Q2.push(ans2);
    }

    while(!Q1.empty()) printf("%d ", Q1.front()), Q1.pop();
    puts("");
    while(!Q2.empty()) printf("%d ", Q2.front()), Q2.pop();
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
