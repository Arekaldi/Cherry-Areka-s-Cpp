#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e5 + 1;

int tot = 0;

int n, m;

namespace Hs {
        class Set {
            private :

                class Point {
                    public :
                        int ls, rs;
                        int F;
                }T[maxn * 20];

            public :
                int Rt[maxn], Bg[maxn];

                inline int Build(int l, int r) {
                    int p = ++tot;
                    if(l == r) {
                        T[p].F = Bg[l];
                        return p;
                    }
                    int mid = (l + r) >> 1;
                    T[p].ls = Build(l, mid);
                    T[p].rs = Build(mid + 1, r);
                    return p;
                }

                inline int Change(int last, int l, int r, int x, int Fa) {
                    int p = ++tot;
                    T[p].ls = T[last].ls, T[p].rs = T[last].rs;
                    if(l == r) {
                        T[p].F = Fa;
                        return p;
                    }
                    int mid = (l + r) >> 1;
                    if(x <= mid)
                        T[p].ls = Change(T[last].ls, l, mid, x, Fa);
                    else
                        T[p].rs = Change(T[last].rs, mid + 1, r, x, Fa);
                    return p;
                }

                inline int Ask(int p, int l, int r, int x) {
                    if(l == r)
                        return T[p].F;
                    int mid = (l + r) >> 1;
                    if(x <= mid)
                        return Ask(T[p].ls, l, mid, x);
                    else
                        return Ask(T[p].rs, mid + 1, r, x);
                }
        }Fa, Sz;

        inline void Oper(int now, int x) {
            Fa.Rt[now] = Fa.Rt[x];
            Sz.Rt[now] = Sz.Rt[x];
            return;
        }

        inline void init() {
            for(int i = 1; i <= n; ++i) 
                Fa.Bg[i] = i, Sz.Bg[i] = 1;
            Fa.Rt[0] = Fa.Build(1, maxn);
            Sz.Rt[0] = Sz.Build(1, maxn);
            return;
        }

        inline int Find(int now, int x) {
            int ff = Fa.Ask(Fa.Rt[now], 1, n, x);
            while(x != ff)
                x = ff, ff = Fa.Ask(Fa.Rt[now], 1, n, x);
            return ff;
        }

        inline void Marge(int now, int x, int y) {
            int a = Find(now, x), b = Find(now, y);
            if(a == b)
                return;
            
            int Nx = Sz.Ask(Sz.Rt[now], 1, n, a), Ny = Sz.Ask(Sz.Rt[now], 1, n, b);

            if(Nx <= Ny) {
                Fa.Rt[now] = Fa.Change(Fa.Rt[now], 1, n, a, b);
                Sz.Rt[now] = Sz.Change(Sz.Rt[now], 1, n, b, Nx + Ny);
            }

            else {
                Fa.Rt[now] = Fa.Change(Fa.Rt[now], 1, n, b, a);
                Sz.Rt[now] = Sz.Change(Sz.Rt[now], 1, n, a, Nx + Ny);
            }
            return;
        }
};


int ppo = 0;
namespace F{
        class Tree{
            public :
                int ls, rs;
                int dat, val;
                int sz;
        }T[maxn * 20];

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
                    x = ++ppo, T[x] = T[p];
                    Split(T[p].rs, k, T[p].rs, y);
                }
                else {
                    y = ++ppo, T[y] = T[p];
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
            int p = ++ppo;
            T[p].sz = 1; T[p].rs = T[p].ls = 0;
            T[p].dat = rand(), T[p].val = k;
            return p;
        }

        inline void Insert(int &Rt, int p) {
            int x, y;
            int k = T[p].val;
            Split(Rt, k, x, y);
            Rt = Marge(Marge(x, p), y);
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
        
        inline void Tknrt(int &id, int k) {
            id = New_Node(k);
            return;
		}
};

inline void MMarge(int now, int x, int y) {
    int a = Hs::Find(now, x), b = Hs::Find(now, y);
    if(a == b)
        return;
    int Nx = Hs::Sz.Ask(Hs::Sz.Rt[now], 1, n, x), Ny = Hs::Sz.Ask(Hs::Sz.Rt[now], 1, n, y);

    if(Nx <= Ny) {
        Hs::Fa.Rt[now] = Hs::Fa.Change(Hs::Fa.Rt[now], 1, n, a, b);
        Hs::Sz.Rt[now] = Hs::Sz.Change(Hs::Sz.Rt[now], 1, n, b, Nx + Ny);
    }

    else {
        Hs::Fa.Rt[now] = Hs::Fa.Change(Hs::Fa.Rt[now], 1, n, b, a);
        Hs::Sz.Rt[now] = Hs::Sz.Change(Hs::Sz.Rt[now], 1, n, a, Nx + Ny);
    }

    int Nrt = F::ReMarge(a, b);
    Hs::Fa.Rt[now] = Hs::Fa.Change(Hs::Fa.Rt[now], 1, n, a, Nrt);
    Hs::Fa.Rt[now] = Hs::Fa.Change(Hs::Fa.Rt[now], 1, n, b, Nrt);
    return;
}

signed main() {


    #define Areka
    #ifdef Areka
        freopen("1.txt", "r", stdin);
        freopen("wrong.txt", "w", stdout);
    #endif

    n = read(), m = read();

    Hs::init();

    for(int i = 1; i <= n; ++i) {
        int a = read();
        int Nrt;
        F::Tknrt(Nrt, a);
        Hs::Fa.Rt[0] = Hs::Fa.Change(Hs::Fa.Rt[0], 1, n, i, Nrt);
    }

    int cnt = 0;
    for(int i = 1; i <= m; ++i) {
        int x, y;
        int opt = read();

        cnt++;
        Hs::Oper(cnt, cnt - 1);

        if(opt == 1) {
            x = read(), y = read();
            MMarge(cnt, x, y);
        }

		if(opt == 2) {
			int w = read();
			Hs::Oper(cnt, w);
		}

        if(opt == 3) {
            x = read(), y = read();
            int ff = Hs::Find(cnt, x);
            int ss = F::Size(ff);
            if(y > ss)
                puts("-1");
            else
                printf("%d\n", F::Val(ff, y));
        }
        
    }

    return 0;
}