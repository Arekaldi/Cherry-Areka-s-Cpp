#include <bits/stdc++.h>

using namespace std;

#define Re register

const int maxn = 1000010;
int Rt, tot;
queue <int> qv;
int st[maxn], v[maxn];

namespace Lct {
        class Tree {
            public :
                int ch[2];
                int Fa, cnt, dat;
                int ans;
                bool laz;
        }T[maxn];


        inline bool Get(int p) {
            return T[T[p].Fa].ch[1] == p;
        }

        // inline void Init(int p) {
        //     T[p].ch[0] = T[p].ch[1] = T[p].Fa = 0;
        //     T[p].dat = T[p].cnt = 0;
        //     return;
        // }

        inline void Push_up(int p) {
            T[p].ans = T[T[p].ch[0]].ans ^ T[T[p].ch[1]].ans ^ v[p];
            return;
        }
        inline bool Son_Root(int p) {
            return (T[T[p].Fa].ch[0] == p) or (T[T[p].Fa].ch[1] == p);
        }

        inline void Push_Lz(int p) {
            swap(T[p].ch[0], T[p].ch[1]);
            T[p].laz ^= 1;
            return;
        }

        inline void Push_down(int p) {
            if(T[p].laz) {
                if(T[p].ch[0])
                    Push_Lz(T[p].ch[0]);
                if(T[p].ch[1])
                    Push_Lz(T[p].ch[1]);
                T[p].laz = false;
            }
            return;
        }// Maybe wrong

        inline void Rotate(int x) {
            // int y = T[x].Fa, z = T[y].Fa;
            // int Type = Get(x);
            // if(z)
            //     T[z].ch[Get(y)] = x;
            // T[x].Fa = z;
            // T[y].ch[Type] = T[x].ch[!Type];
            // T[T[y].ch[Type]].Fa = y;
            // T[y].Fa = x;
            // T[x].ch[!Type] = y;
            // Push_up(y);
			int y = T[x].Fa;
			int z = T[y].Fa;
		    bool k = (T[y].ch[1] == x);
			int w = T[x].ch[!k];
			if(Son_Root(y)) T[z].ch[T[z].ch[1] == y] = x;
			T[x].ch[!k] = y;
			T[y].ch[k] = w;
			if(w) T[w].Fa = y;
			T[y].Fa = x;
			T[x].Fa = z;
			Push_up(y);
            return;
        }

        inline void Splay(int x) {
            int y = x, top = 0, z;
            st[++top] = y;

            while(Son_Root(y))
                y = T[y].Fa, st[++top] = y;
            while(top)
                Push_down(st[top--]);

            // while(T[x].Fa != Tar) {
            //     int y = T[x].Fa, z = T[y].Fa;
            //     if(z != Tar)
            //         Get(y) == Get(x) ? Rotate(y) : Rotate(x);
            //     Rotate(x);
            // }

            while(Son_Root(x)) {
                y = T[x].Fa, z = T[y].Fa;
                if(Son_Root(y))
                    Rotate(((T[y].ch[0] == x) + (T[z].ch[0] == y) == 1) ? x : y);
                    Rotate(x);
            }

            Push_up(x);
            return;
        }
        inline void Access(int x) {
            int y = 0;
            while(x) {
                Splay(x);
                T[x].ch[1] = y;
                Push_up(x);
                y = x;
                x = T[x].Fa;
            }
            return;
        }

        inline void Make_Root(int x) {
            Access(x), Splay(x);
            Push_Lz(x);
        }

        inline int Find_Root(int x) {
            Access(x), Splay(x);
            while(T[x].ch[0])
                Push_down(x), x = T[x].ch[0];
            Splay(x);
            return x;
        }

        inline void Split(int x, int y) {
            Make_Root(x);
            Access(y), Splay(y);
            return;
        }

        inline void Link(int x, int y) {
            Make_Root(x);
            if(Find_Root(y) != x)
                T[x].Fa = y;
            return;
        }

        inline void Cut(int x, int y) {
            Make_Root(x);
            if(Find_Root(y) == x and T[y].Fa == x and !T[y].ch[0]) {
                T[y].Fa = T[x].ch[1] = 0;
                Push_up(x);
            }
        }
        /*
        inline void Insert(int x) {
            if(!Rt) {
                int New = ++tot;
                T[New].siz = T[New].cnt = 1;
                T[New].ch[0] = T[New].ch[1] = T[New].Fa = 0;
                Rt = New, T[New].dat = x;
                return;
            }
            int p = Rt, fa = 0;
            while(true) {
                if(T[p].dat == x) {
                    T[p].cnt++;
                    Upd(p), Upd(fa);
                    Splay(p, 0);
                    return;
                }
                fa = p;
                p = T[p].ch[T[p].dat < x];
                if(!p) {
                    p = ++tot;
                    T[p].ch[0] = T[p].ch[1] = 0;
                    T[p].Fa = fa;
                    T[p].siz = T[p].cnt = 1;
                    T[p].dat = x;
                    T[fa].ch[T[fa].dat < x] = p;
                    Upd(fa);
                    Splay(p, 0);
                    return;
                }
            }
        }

        inline int Find_Dat(int Rk) {
            int p = Rt;
            while(true) {
                if(T[p].ch[0] and Rk <= T[T[p].ch[0]].siz)
                    p = T[p].ch[0];
                else {
                    int Size = (T[p].ch[0] ? T[T[p].ch[0]].siz : 0) + T[p].cnt;
                    if(Rk <= Size) 
                        return T[p].dat;
                    Rk -= Size;
                    p = T[p].ch[1];
                }
            }
        }

        inline int Find_Rk(int dat) {
            int p = Rt, ans = 0;
            while(true) {
                if(dat < T[p].dat)
                    p = T[p].ch[0];
                else {
                    ans += (T[p].ch[0] ? T[T[p].ch[0]].siz : 0);
                    if(dat == T[p].dat) {
                        Splay(p, 0);
                        return ans + 1;
                    }
                    ans += T[p].cnt;
                    p = T[p].ch[1];
                }
            }
        }

        inline void Position(int x) {
            int p = Rt;
            if(!p) return;
            while(T[p].ch[x > T[p].dat] and x != T[p].dat)
                p = T[p].ch[x > T[p].dat];
            Splay(p, 0);
        }

        inline int Get_Pre(int x, bool Type) {
            Position(x);
            int p = T[Rt].ch[0];
            while(T[p].ch[1])
                p = T[p].ch[1];
            return Type ? T[p].dat : p;
        }

        inline int Get_Nxt(int x, bool Type) {
            Position(x);
            int p = T[Rt].ch[1];
            while(T[p].ch[0])
                p = T[p].ch[0];
            return Type ? T[p].dat : p;
        }

        inline void Del(int x) {
            int La = Get_Pre(x, 0), Nx = Get_Nxt(x, 0);
            Splay(La, 0), Splay(Nx, La);
            int Newx = T[Nx].ch[0];
            if(T[Newx].cnt > 1)
                T[Newx].cnt--, Splay(Newx, 0);
            else
                T[Nx].ch[0] = 0;
        }
        */
};

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, m;
const int Max = 0x7f7f7f7f, Min = -0x7f7f7f7f;

signed main() {
    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        v[i] = read();

    for(int i = 1; i <= m; ++i) {
        int opt = read(), x = read(), y = read();
        switch(opt) {
            case 0: {
                Lct::Split(x, y);
                printf("%d\n", Lct::T[y].ans);
                break;
            }
            case 1: {
                Lct::Link(x, y);
                break;
            }
            case 2: {
                Lct::Cut(x, y);
                break;
            }
            case 3: {
                Lct::Splay(x), v[x] = y;
                break;
            }
        }
    }


    // n = read();
    // S.Insert(Max), S.Insert(Min);
    // for(int i = 1; i <= n; ++i) {
    //     int opt = read();
    //     int x = read();
    //     switch (opt) {
    //         case 1 : {
    //             S.Insert(x); break;
    //         }
    //         case 2 : {
    //             S.Del(x); break;
    //         }
    //         case 3 : {
    //             printf("%d\n", S.Find_Rk(x) - 1); break;
    //         }
    //         case 4 : {
    //             printf("%d\n", S.Find_Dat(x + 1)); break;
    //         }
    //         case 5 : {
    //             S.Insert(x);
    //             printf("%d\n", S.Get_Pre(x, 1));
    //             S.Del(x);
    //             break;
    //         }
    //         case 6 : {
    //             S.Insert(x);
    //             printf("%d\n", S.Get_Nxt(x, 1));
    //             S.Del(x);
    //             break;
    //         }
    //     }
    // }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
