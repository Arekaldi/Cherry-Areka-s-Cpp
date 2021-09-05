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

int Rt[maxn], tot = 0;

namespace F{
        class Tree{
            public :
                int ls, rs;
                int dat, val;
                int sz;
        }T[maxn];

        inline void Upd(int p) {
            T[p].sz = T[T[p].ls].sz + T[T[p].rs].sz + 1;
        }

        inline void Split(int p, int k, int& x, int& y) {
            if(p == 0) {
                x = y = 0;
                return;
            }
            
            else {
                if(T[p].val <= k) {
                    x = p;
                    Split(T[p].rs, k, T[p].rs, y);
                }
                else {
                    y = p;
                    Split(T[p].ls, k, x, T[p].ls);
                }
            }
            Upd(p);
            return;
        }

        inline int Marge(int x, int y) {
            if(x == y)
                return x;
            if(x == 0 or y == 0)
                return x + y;

            if(T[x].dat < T[y].dat) {
                T[x].rs = Marge(T[x].rs, y);
                Upd(x);
                return x;
            }
            else {
                T[y].ls = Marge(x, T[y].ls);
                Upd(y);
                return y;
            }
        }

        inline int New_Node(int k) {
            int p = ++tot;
            T[p].sz = 1; T[p].rs = T[p].ls = 0;
            T[p].dat = rand(), T[p].val = k;
            return p;
        }

        inline void Insert(int &Rt, int k) {
            int x, y;
            Split(Rt, k, x, y);
            int New = New_Node(k);
            Rt = Marge(Marge(x, New), y);
            return;
        }

        inline int Val(int &Rt, int k) {
            int p = Rt;
            while(true) {
                if(T[T[p].ls].sz + 1 == k)
                    break;
                if(T[T[p].ls].sz + 1 > k) 
                    p = T[p].ls;
                else {
                    k -= (T[T[p].ls].sz + 1);
                    p = T[p].rs;
                }
            }
            return T[p].val;
        }

        inline int Size(int p) {
            return T[p].sz;
        }

        inline void Dfs(int x, int &y) {
            if(!x)
                return;
            Dfs(T[x].ls, y), Dfs(T[x].rs, y);
            T[x].ls = T[x].rs = 0;
            Insert(y, x);
        }

        inline int ReMarge(int x, int y) {
            if(T[x].sz > T[y].sz)
                swap(x, y);
            Dfs(x, y);
            return y;
        }
};

namespace U {
    
    inline int Find(int x) {
        return x == Rt[x] ? x : Rt[x] = Find(Rt[x]);
    }

}

inline void MMarge(int a, int b) {
    int Fas = U :: Find(a), Fb = U :: Find(b);
    if(Fas == Fb)
        return;
    int Nrt = F :: ReMarge(Rt[a], Rt[b]);
    Rt[Fas] = Rt[Fb] = Nrt;
    Rt[Nrt] = Nrt;
}

int n, m;

signed main() {
    n = read(), m = read();

    for(int i = 1; i <= n; ++i) {
        int a = read();
        F :: Insert(Rt[i], a);
    }

    for(int i = 1; i <= m; ++i) {
        int a = read(), b = read();
        MMarge(a, b);
    }

    int q = read();

    for(int i = 1; i <= q; ++i) {
        char opt;
        scanf("%c", &opt);

        int x = read(), y = read();

        if(opt == 'Q') {
            // int ss = F :: Size(Rt[x]);
            int ff = U :: Find(x);
            int ss = F :: Size(ff);
            // cout << ss << endl;
            if(y > ss)
                puts("-1");
            else
                printf("%d\n", F :: Val(Rt[x], y));
        }
        
        else
            MMarge(x, y);
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
