#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5e5 + 1;

int Rt, tot;

class Fhq_Treap{
    private :
        class Tree{
            public :
                int ls, rs;
                int dat, val, kl;
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

        inline int New_Node(int k, int k1) {
            int p = ++tot;
            T[p].sz = 1; T[p].rs = T[p].ls = 0;
            T[p].dat = rand(), T[p].val = k;
            T[p].kl = k1;
            return p;
        }

    public :

        inline void Insert(int k, int k1) {
            int x, y;
            // cout << Rt << endl;
            Split(Rt, k, x, y);
            int New = New_Node(k, k1);
            Rt = Marge(Marge(x, New), y);
            return;
        }

        inline void Remove(int k) {
            int x, y, z;
            Split(Rt, k, x, z);
            Split(x, k - 1, x, y);
            y = Marge(T[y].ls, T[y].rs);
            Rt = Marge(Marge(x, y), z);
        }

        inline int Val(int k) {
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

        inline int Rank(int k) {
            int x, y, ans;
            Split(Rt, k - 1, x, y);
            ans = T[x].sz + 1;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Pre(int k) {
            int x, y, p;
            Split(Rt, k - 1, x, y);
            p = x;
            while(T[p].rs)
                p = T[p].rs;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }

        inline int Get_Nxt(int k) {
            int x, y, p;
            Split(Rt, k, x, y);
            p = y;
            while(T[p].ls)
                p = T[p].ls;
            int ans = T[p].val;
            Rt = Marge(x, y);
            return ans;
        }

        inline bool Find(int k) {
            int x, y, z;
            Split(Rt, k, x, y);
            Split(x, k - 1, x, z);
            bool ans = T[z].sz > 0;
            Rt = Marge(Marge(x, z), y);
            return ans;
        }

        inline int Size() {
            return T[Rt].sz;
        }

        inline bool empty() {
            return T[Rt].sz == 0;
        }

        inline void Get(int p, int &u, int &c) {
            u += T[p].kl, c += T[p].val;
            if(T[p].ls)
                Get(T[p].ls, u, c);
            if(T[p].rs)
                Get(T[p].rs, u, c);
            return;
        }
}F;

signed main() {
    while(true) {
        int opt = read();
        if(opt == -1)
            break;
        

        if(opt == 1) {
            int u = read(), c = read();
            if(F.Find(c))
                continue;
            F.Insert(c, u);
        }

        else
            if(opt == 3 and !F.empty())
                F.Remove(F.Val(1));
            else if(!F.empty())
                F.Remove(F.Val(F.Size()));
    }
    
    int ans1 = 0, ans2 = 0;

    F.Get(Rt, ans1, ans2);

    printf("%d %d\n", ans1, ans2);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
