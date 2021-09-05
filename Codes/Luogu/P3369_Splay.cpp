#include <bits/stdc++.h>

using namespace std;

#define Re register

const int maxn = 100010;
int Rt, tot;

class Splay_Tree {
    private :
        class Tree {
            public :
                int ch[2];
                int Fa, cnt, dat;
                int siz;
        }T[maxn];

        inline bool Get(int p) {
            return T[T[p].Fa].ch[1] == p;
        }

        inline void Init(int p) {
            T[p].ch[0] = T[p].ch[1] = T[p].Fa = 0;
            T[p].siz = T[p].dat = T[p].cnt = 0;
            return;
        }

        inline void Upd(int p) {
            T[p].siz = T[p].cnt + (T[p].ch[0] ? T[T[p].ch[0]].siz : 0) + (T[p].ch[1] ? T[T[p].ch[1]].siz : 0);
            return;
        }


        // #define Ls T[(x)].ch[0]
        // #define Rs T[(x)].ch[1]
        // inline void Right_Rotate(int x) {
        //     int y = T[x].Fa, z = T[y].Fa;
        //     T[y].Ls = T[x].Rs;
        //     if(T[x].Rs != 0)
        //         T[T[x].Rs].Fa = y;
        //     T[x].Fa = z;
        //     if(z != 0) 
        //         Get(y) ? T[z].Rs = x : T[z].Ls = x;
        //     T[x].Rs = y; T[y].Fa = x;
        //     return;
        // }

        // inline void Left_Rotate(int x) {
        //     int y = T[x].Fa, z = T[y].Fa;
        //     T[y].Rs = T[x].Ls;
        //     if(T[x].Ls != 0)
        //         T[T[x].Ls].Fa = y;
        //     T[x].Fa = z;
        //     if(z != 0)
        //         Get(y) ? T[z].Rs = x : T[z].Ls = x;
        //      T[x].Ls = y, T[y].Fa = x;
        // }

        // inline void Splay(int x, int Tar) {
        //     while(T[x].Fa != Tar) {
        //         int y = T[x].Fa, z = T[y].Fa;
        //         if(z == Tar)
        //             if(T[y].Ls == x)
        //                 Right_Rotate(x);
        //             else
        //                 Left_Rotate(x);
        //         else 
        //             if(T[z].Ls == y)
        //                 if(T[y].Ls == x)
        //                     Right_Rotate(y), Right_Rotate(x);
        //                 else
        //                     Left_Rotate(x), Right_Rotate(x);
        //             else
        //                 if(T[y].Rs == x)
        //                     Left_Rotate(y), Left_Rotate(x);
        //                 else
        //                     Right_Rotate(x), Left_Rotate(x);
        //     }
        //     if(Tar == 0) Rt = x;
        // }

        inline void Rotate(int x) {
            int y = T[x].Fa, z = T[y].Fa;
            int Type = Get(x);
            if(z)
                T[z].ch[Get(y)] = x;
            T[x].Fa = z;
            T[y].ch[Type] = T[x].ch[!Type];
            T[T[y].ch[Type]].Fa = y;
            T[y].Fa = x;
            T[x].ch[!Type] = y;
            Upd(y), Upd(x);
            return;
        }

        inline void Splay(int x, int Tar) {
            while(T[x].Fa != Tar) {
                int y = T[x].Fa, z = T[y].Fa;
                if(z != Tar)
                    Get(y) == Get(x) ? Rotate(y) : Rotate(x);
                Rotate(x);
            }

            if(Tar == 0)
                Rt = x;

            return;
        }

    public :
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
                // if(T[p].dat < x)
                //     p = T[p].ch[0];
                // else
                //     p = T[p].ch[1];
                p = T[p].ch[T[p].dat < x];
                if(!p) {
                    p = ++tot;
                    T[p].ch[0] = T[p].ch[1] = 0;
                    T[p].Fa = fa;
                    T[p].siz = T[p].cnt = 1;
                    T[p].dat = x;
                    // if(T[fa].dat < x)
                    //     T[fa].ch[1] = New;
                    // else
                    //     T[fa].ch[0] = New;
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
                    // int Size = T[p].cnt;
                    // if(T[p].ch[0]) Size += T[T[p].ch[0]].siz;
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
                    // if(T[p].ch[0])
                    //     ans += T[T[p].ch[0]].siz;
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
}S;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n;
const int Max = 0x7f7f7f7f, Min = -0x7f7f7f7f;

signed main() {
    n = read();
    S.Insert(Max), S.Insert(Min);
    for(int i = 1; i <= n; ++i) {
        int opt = read();
        int x = read();
        switch (opt) {
            case 1 : {
                S.Insert(x); break;
            }
            case 2 : {
                S.Del(x); break;
            }
            case 3 : {
                printf("%d\n", S.Find_Rk(x) - 1); break;
            }
            case 4 : {
                printf("%d\n", S.Find_Dat(x + 1)); break;
            }
            case 5 : {
                S.Insert(x);
                printf("%d\n", S.Get_Pre(x, 1));
                S.Del(x);
                break;
            }
            case 6 : {
                S.Insert(x);
                printf("%d\n", S.Get_Nxt(x, 1));
                S.Del(x);
                break;
            }
        }
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
