#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int Rt, tot;

const int maxn = 1e6 + 1;

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

        inline void Splitp(int p, int k, int& x, int& y) {
            if(p == 0) {
                x = y = 0;
                return;
            }

            if(T[T[p].ls].sz + 1 <= k) {
                x = p;
                Splitp(T[p].rs, k - T[T[p].ls].sz - 1, T[p].rs, y);
            }
            else {
                y = p;
                Splitp(T[p].ls, k, x, T[p].ls);
            }

            Upd(p);
            return;
        }

        inline int Marge(int x, int y) {
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

        inline void Tknbook(int id, int pos) {
            int x, y, z;
            Splitp(Rt, pos, x, y);
            int New = New_Node(id);
            Rt = Marge(Marge(x, New), y);
        }

        inline int Val(int k) {
            int x, y, z;
            Splitp(Rt, k, x, y);
            Splitp(y, 1, y, z);
            int ans = T[y].val;
            Rt = Marge(x, Marge(y, z));
            return ans;
        }

        inline int Size(int p) {
            return T[p].sz;
        }
};

int n, m, cnt;

const int maxm = 1e6 + 1;
string name[maxm];

signed main() {
    n = read();
    
    for(int i = 1; i <= n; ++i) {
        string ss;
        cin >> ss;
        name[++cnt] = ss;
        F :: Tknbook(cnt, i - 1);
    }

    int m = read();
    for(int i = 1; i <= m; ++i) {
        string ss;
        cin >> ss;
        int x = read();
        name[++cnt] = ss;
        F :: Tknbook(cnt, x);
    }


    int Q = read();

    for(int i = 1; i <= Q; ++i) {
        int x = read();
        int ud = F :: Val(x);
        for(int j = 0; name[ud][j]; ++j)
            putchar(name[ud][j]);
        puts("");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}


// 1 2 3 4 5
// Math Al Picture Pro