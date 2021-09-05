#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int INF = INT_MAX;

const int maxn = 5e6 + 1;

int tot, a[maxn];

class Fhq_Treap{
    private :
        class Tree{
            public :
                int ls, rs;
                int dat, val;
                int sz;
        }T[maxn * 10];

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


    public :

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

        inline void Remove(int &Rt, int k) {
            int x, y, z;
            Split(Rt, k, x, z);
            Split(x, k - 1, x, y);
            y = Marge(T[y].ls, T[y].rs);
            Rt = Marge(Marge(x, y), z);
        }

        inline int Rank(int &Rt, int k) {
            int x, y, ans;
            Split(Rt, k - 1, x, y);
            ans = T[x].sz;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Pre(int &Rt, int k) {
            int x, y, p;
            Split(Rt, k - 1, x, y);
            p = x;
            if(!p)
                return -INF;
            while(T[p].rs)
                p = T[p].rs;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Nxt(int &Rt, int k) {
            int x, y, p;
            Split(Rt, k, x, y);
            p = y;
            if(!p)
                return INF;
            while(T[p].ls)
                p = T[p].ls;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }
}F;

namespace Seg_MentTree {
    class Tree {
        public:
            int l, r;
            int rt;
    };
    
    Tree T[maxn * 10];

    inline void Build(int p, int l, int r) {
        T[p].l = l, T[p].r = r;
        if(l == r) {
            T[p].rt = F.New_Node(a[l]);
            return;
        }
        for(int i = l; i <= r; ++i)
            F.Insert(T[p].rt, a[i]);
        int mid = (l + r) >> 1;
        Build(p << 1, l, mid);
        Build((p << 1) | 1, mid + 1, r);
    }

    inline int Get_Rank(int p, int l, int r, int k) {
        if(T[p].l >= l and T[p].r <= r)
            return F.Rank(T[p].rt, k);
        int mid = (T[p].l + T[p].r) >> 1;
        int ans = 0;
        if(l <= mid)
            ans += Get_Rank(p << 1, l, r, k);
        if(r > mid)
            ans += Get_Rank((p << 1) | 1, l, r, k);
        return ans;
    }

    inline int Val(int l, int r, int k) {
        int L = 0, R = 1e8 + 1, ans = 0;
        while(L < R) {
            int mid = (L + R) >> 1;
            if(Get_Rank(1, l, r, mid) + 1 <= k)
                ans = mid, L = mid + 1;
            else
                R = mid;
        }
        return ans;
    }

    inline void Change(int p, int pos, int k) {
        F.Remove(T[p].rt, a[pos]), F.Insert(T[p].rt, k);
        if(T[p].l == T[p].r)
            return;
        int mid = (T[p].l + T[p].r) >> 1;
        if(pos <= mid)
            Change(p << 1, pos, k);
        if(pos > mid)
            Change((p << 1) | 1, pos, k);
    }

    inline int Pre(int p, int l, int r, int k) {
        if(T[p].l >= l and T[p].r <= r)
            return F.Get_Pre(T[p].rt, k);
        int mid = (T[p].l + T[p].r) >> 1;
        int ans = -INT_MAX;
        if(l <= mid)
            ans = max(ans, Pre(p << 1, l, r, k));
        if(r > mid)
            ans = max(ans, Pre((p << 1) | 1, l, r, k));
        return ans;
    }

    inline int Nxt(int p, int l, int r, int k) {
        if(T[p].l >= l and T[p].r <= r)
            return F.Get_Nxt(T[p].rt, k);
        int mid = (T[p].l + T[p].r) >> 1;
        int ans = INT_MAX;
        if(l <= mid)
            ans = min(ans, Nxt(p << 1, l, r, k));
        if(r > mid)
            ans = min(ans, Nxt((p << 1) | 1, l, r, k));
        return ans;
    }
}

signed main() {

    int n = read(), m = read();

    for(int i = 1 ; i <= n ; ++i)
        a[i] = read();

    Seg_MentTree :: Build(1, 1, n);
    for(int i = 1 ; i <= m ; ++i) {
        int opt = read();
        if(opt == 1) {
            int l = read(), r = read(), k = read();
            printf("%d\n", Seg_MentTree :: Get_Rank(1, l, r, k) + 1);
        }
        else if(opt == 2) {
            int l = read(), r = read(), k = read();
            printf("%d\n", Seg_MentTree :: Val(l, r, k));
        }
        else if(opt == 3) {
            int pos = read(), k = read();
            Seg_MentTree :: Change(1, pos, k);
            a[pos] = k;
        }
        else if(opt == 4) {
            int l = read(), r = read(), k = read();
            printf("%d\n", Seg_MentTree :: Pre(1, l, r, k));
        }
        else if(opt == 5) {
            int l = read(), r = read(), k = read();
            printf("%d\n", Seg_MentTree :: Nxt(1, l, r, k));
        }
    }
    
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
