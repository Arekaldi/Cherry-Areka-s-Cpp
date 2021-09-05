#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1;

int n, m;

namespace Left_More_Tree {
    class Tree {
        public:
            int val, dis, ls, rs, fa;
    };
    Tree T[maxn];

    inline int Find(int x) {
        return T[x].fa == x ? x : T[x].fa = Find(T[x].fa);
    }

    inline int Merge(int x, int y) {
        if(!x or !y)
            return x | y;
        if(T[x].val > T[y].val or (T[x].val == T[y].val and x > y))
            swap(x, y);
        T[x].rs = Merge(T[x].rs, y);
        if(T[T[x].ls].dis < T[T[x].rs].dis)
            swap(T[x].ls, T[x].rs);
        T[T[x].ls].fa = T[T[x].rs].fa = T[x].fa = x;
        T[x].dis = T[T[x].rs].dis + 1;
        return x;
    }

    inline void Delete(int x) {
        T[x].val = -1;
        T[T[x].ls].fa = T[x].ls, T[T[x].rs].fa = T[x].rs;
        T[x].fa = Merge(T[x].ls, T[x].rs);
    }
}

using namespace Left_More_Tree;

signed main() {
    n = read(), m = read();
    T[0].dis = -1;
    for(int i = 1; i <= n; ++i)
        T[i].val = read(), T[i].fa = i;
    
    for(int i = 1; i <= m; ++i) {
        int opt = read(), x = read();
        if(opt == 1) {
            int y = read();
            if(T[x].val == -1 or T[y].val == -1)
                continue;
            int Fx = Find(x), Fy = Find(y);
            if(Fx == Fy)
                continue;
            T[Fx].fa = T[Fy].fa = Merge(Fx, Fy);
        }
        else {
            if(T[x].val == -1) {
                puts("-1");
                continue;
            }
            int Rtx = Find(x);
            printf("%d\n", T[Rtx].val);
            Delete(Rtx);
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
