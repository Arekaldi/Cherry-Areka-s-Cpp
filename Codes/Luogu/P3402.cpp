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

class Historical_Set {
    
    private :

        class Set {
            private :
                int cnt = 0;

                class Point {
                    public :
                        int ls, rs;
                        int F;
                }T[maxn << 2];

            public :

                int Rt[maxn], Bg[maxn];

                inline int Build(int l, int r) {
                    int p = ++cnt;
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
                    int p = ++cnt;
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

    public :

        inline void Oper(int now, int x) {
            Fa.Rt[now] = Fa.Rt[x];
            Sz.Rt[now] = Sz.Rt[x];
            return;
        }

        inline void init() {
            for(int i = 1; i <= n; ++i) 
                Fa.Bg[i] = i, Sz.Bg[i] = 1;
            Fa.Rt[0] = Fa.Build(1, n);
            Sz.Rt[0] = Sz.Build(1, n);
            return;
        }

        inline int Find(int now, int x) {
            int ff = Fa.Ask(Fa.Rt[now], 1, n, x);
            while(ff != x)
                x = ff, ff = Fa.Ask(Fa.Rt[now], 1, n, x);
            return x;
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
}S;

int tot = 1;

signed main() {
    n = read(), m = read();

    S.init();

    for(int i = 1; i <= m; ++i, ++tot) {
        int opt = read();

        // cout << opt << endl;

        S.Oper(tot, tot - 1);
        switch(opt) {
            case 1 : {
                int x = read(), y = read();
                S.Marge(tot, x, y);
                break;
            }
            case 2 : {
                int x = read();
                S.Oper(tot, x);
                break;
            }
            case 3 : {
                int x = read(), y = read();
                if(S.Find(tot, x) == S.Find(tot, y))
                    puts("1");
                else
                    puts("0");

                break;
            }
        }
    }
    
    
    return 0;
}
