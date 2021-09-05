#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

#define int long long

const int maxn = 5e4 + 1;

int n, m;

namespace F {
    int Rt, tot;

    class Tree {
        public:
            int ls, rs;
            int sz, vl;
            int dat;
            int mx, ad, rev;
    };
    Tree T[maxn];

    inline int New_Node(int k) {
        int p = ++tot;
        T[p].ls = T[p].rs = T[p].ad = T[p].rev = 0;
        T[p].sz = 1, T[p].mx = T[p].vl = k;
        T[p].dat = rand();
        return p;
    }


    inline void Upd(int p) {
        int l = T[p].ls, r = T[p].rs;
        T[p].sz = T[l].sz + T[r].sz + 1;
        T[p].mx = T[p].vl;
        if(l)
            T[p].mx = max(T[p].mx, T[l].mx);
        if(r)
            T[p].mx = max(T[p].mx, T[r].mx);
        return;
    }

    inline void Pushdown(int p) {
        int &l = T[p].ls, &r = T[p].rs;

        if(T[p].rev) {
            if(l)
                T[l].rev ^= 1;
            if(r)
                T[r].rev ^= 1;
            swap(T[p].ls, T[p].rs);
            T[p].rev = 0;
        }

        if(T[p].ad) {
            if(l) {
                T[l].ad += T[p].ad;
                T[l].vl += T[p].ad;
                T[l].mx += T[p].ad;
            }
            if(r) {
                T[r].ad += T[p].ad;
                T[r].vl += T[p].ad;
                T[r].mx += T[p].ad;
            }
            T[p].ad = 0;
            Upd(p);
        }
    }

    inline void Split(int p, int k, int &x, int &y) {
        if(p == 0) {
            x = y = 0;
            return;
        }

        Pushdown(p);

        // int &l = T[p].ls, &r = T[p].rs;
        // if(T[l].sz >= k) {
        //     y = p;
        //     Split(l, k, x, l);
        // }
        // else {
        //     x = p;
        //     Split(r, k - T[l].sz - 1, r, y);
        // }
        // Upd(p);

        if(T[T[p].ls].sz >= k) {
            y = p;
            Split(T[p].ls, k, x, T[p].ls);
        }
        else {
            x = p;
            Split(T[p].rs, k - T[T[p].ls].sz - 1, T[p].rs, y);
        }

        Upd(p);
        return;
    }

    inline int Merge(int x, int y) {
        if(x)
            Pushdown(x);
        if(y)
            Pushdown(y);
        if(!x or !y)
            return x + y;

        
		if(T[x].dat < T[y].dat) {
			T[x].rs = Merge(T[x].rs, y);
			Upd(x);
			return x;
		}
		else {
			T[y].ls = Merge(x, T[y].ls);
			Upd(y);
			return y;
		}
    }

    inline void Insert(int k) {
        int x, y;
        Split(Rt, k, x, y);
        Rt = Merge(Merge(x, New_Node(k)), y);
        return;
    }

    inline void Add(int pos, int len, int v) {
        int x, y, z;
        Split(Rt, pos - 1, x, y);
        Split(y, len, y, z);
        T[y].vl += v;
        T[y].mx += v;
        T[y].ad += v;
        Rt = Merge(Merge(x, y), z);
        return;
    }

    inline void Reverse(int pos, int len) {
        int x, y, z;
        Split(Rt, pos - 1, x, y);
        Split(y, len, y, z);
        T[y].rev ^= 1;
        Rt = Merge(Merge(x, y), z);
        return;
    }

    inline int Ask(int pos, int len) {
        int x, y, z;
        Split(Rt, pos - 1, x, y);
        Split(y, len, y, z);
        int ans = T[y].mx;
        Rt = Merge(Merge(x, y), z);
        return ans;
    }
}

signed main() {
    n = read(), m = read();
    
    for(int i = 1; i <= n; ++i)
        F :: Insert(0);

    for(int i = 1; i <= m; ++i) {
        int opt = read(), x = read(), y = read();
        if(opt == 1) {
            int z = read();
            F :: Add(x, y - x + 1, z);
        }

        if(opt == 2)
            F :: Reverse(x, y - x + 1);
        
        if(opt == 3) {
            int ans = F :: Ask(x, y - x + 1);
            printf("%lld\n", ans);
        }
    }
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
