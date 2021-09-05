#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e4 + 1, maxt = 3e5 + 1, Inf = (1 << 30);

class Bird {
    public :
        int A1, A2;
        int Tg, Wg;
        int x, y, wh;
        bool vis;
}B[maxn];

int Rt[maxn], tot;

class Splay_Tree {
    private :
        stack <int> s;
        class Tree {
            public :
                int ch[2], id, Max;
                int Fa, cnt, val;
                int siz, m1, m2;
        }T[maxn];

        inline bool Get(int p) {
            return T[T[p].Fa].ch[1] == p;
        }

        inline void Upd(int p) {
            T[p].siz = T[p].cnt + (T[p].ch[0] ? T[T[p].ch[0]].siz : 0) + (T[p].ch[1] ? T[T[p].ch[1]].siz : 0);
            T[p].Max = max(max(T[T[p].ch[0]].Max, T[T[p].ch[1]].Max), T[p].val);
            return;
        }

        inline void Push(int p) {
            int u1 = T[p].id;
            B[u1].A1 = max(B[u1].A1, T[p].m1);
            B[u1].A2 = max(B[u1].A2, T[p].m2);
            if(T[p].ch[0]) {
                int ls = T[p].ch[0];
                int u = T[ls].id;
                B[u].A1 = max(B[u].A1, T[p].m1);
                B[u].A2 = max(B[u].A2, T[p].m2);
                T[ls].m1 = max(T[p].m1, T[ls].m1);
                T[ls].m2 = max(T[p].m2, T[ls].m2);
            }
            if(T[p].ch[1]) {
                int rs = T[p].ch[0];
                int u = T[rs].id;
                B[u].A1 = max(B[u].A1, T[p].m1);
                B[u].A2 = max(B[u].A2, T[p].m2);
                T[rs].m1 = max(T[p].m1, T[rs].m1);
                T[rs].m2 = max(T[p].m2, T[rs].m2);
            }
            T[p].m1 = T[p].m2 = 0;
        }

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

        inline void Splay(int &Rt, int x, int Tar) {

            while(!s.empty())
                s.pop();

            int p = x;
            while(p != Tar)
                s.push(p), p = T[p].Fa;
            
            if(p)
                Push(p);

            while(!s.empty()) {
                int ww = s.top();
                Push(ww);
                s.pop();
            }

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
        inline void Insert(int &Rt, int x, int u) {
            if(!Rt) {
                int New = ++tot;
                T[New].siz = T[New].cnt = 1;
                T[New].ch[0] = T[New].ch[1] = T[New].Fa = 0;
                Rt = New, T[New].val = x;
                T[Rt].id = u;
                return;
            }
            int p = Rt, fa = 0;
            while(true) {
                Push(p);
                if(T[p].val == x) {
                    T[p].cnt++;
                    Upd(p), Upd(fa);
                    Splay(Rt, p, 0);
                    return;
                }
                fa = p;
                p = T[p].ch[T[p].val < x];
                if(!p) {
                    p = ++tot;
                    T[p].Fa = fa;
                    T[p].siz = T[p].cnt = 1;
                    T[p].val = x;
                    T[fa].ch[T[fa].val < x] = p;
                    T[p].id = u;
                    Upd(fa);
                    Splay(Rt, p, 0);
                    return;
                }
            }
        }

        inline void Position(int &Rt, int x) {
            int p = Rt;
            if(!p) return;
            while(T[p].ch[x > T[p].val] and x != T[p].val)
                p = T[p].ch[x > T[p].val];
            Splay(Rt, p, 0);
        }

        inline int Get_Pre(int &Rt, int x, bool Type) {
            Position(Rt, x);
            int p = T[Rt].ch[0];
            while(T[p].ch[1])
                p = T[p].ch[1];
            return Type ? T[p].val : p;
        }

        inline int Get_Nxt(int &Rt, int x, bool Type) {
            Position(Rt, x);
            int p = T[Rt].ch[1];
            while(T[p].ch[0])
                p = T[p].ch[0];
            return Type ? T[p].val : p;
        }

        inline void Del(int &Rt, int x) {
            int La = Get_Pre(Rt, x, 0), Nx = Get_Nxt(Rt, x, 0);
            Splay(Rt, La, 0), Splay(Rt, Nx, La);
            int Newx = T[Nx].ch[0];
            if(T[Newx].cnt > 1)
                T[Newx].cnt--, Splay(Rt, Newx, 0);
            else
                T[Nx].ch[0] = 0;
        }
}S;

int n, t;

class Command {
    public :
        int u, x, y;
}Com[maxt];

int order[maxn];

map < pair <int, int>, int> M;

int cnt, tt;
inline int id(int x, int y) {
    int &t = M[make_pair(x, y)];
    if(t == 0)
        t = ++cnt;
    return t;
}

signed main() {
    n = read();
    
    for(int i = 1; i <= n; ++i) {
        B[i].Wg = read();
        B[i].x = read(), B[i].y = read();
        order[++tt] = B[i].x, order[++tt] = B[i].y;
    }

    t = read();
    for(int i = 1; i <=t; ++i) {
        Com[i].u = read(), Com[i].x = read(), Com[i].y = read();
        order[++tt] = Com[i].u, order[++tt] = Com[i].x, order[++tt] = Com[i].y;
    }


    sort(order + 1, order + tt + 1);
    int nt = unique(order + 1, order + n + 1) - order;


    for(int i = 1; i <= n; ++i) {
        B[i].x = lower_bound(order + 1, order + nt + 1, B[i].x) - order - 1;
        B[i].y = lower_bound(order + 1, order + nt + 1, B[i].y) - order - 1;
        int j = id(B[i].x, B[i].y);
        if(j == cnt)
            S.Insert(Rt[j], -Inf, 0), S.Insert(Rt[j], Inf, 0);
        S.Insert(Rt[j], B[i].Wg, i);
    }
    

    for(int i = 1; i <= t; ++i) {
        Com[i].x = lower_bound(order + 1, order + tt + 1, Com[i].x) - order - 1;
        Com[i].y = lower_bound(order + 1, order + nt + 1, Com[i].y) - order - 1;
        int u = Com[i].u;
        int j1 = id(Com[i].x, Com[i].y), j2 = id(B[u].x, B[u].y);
        S.Del(Rt[j2], B[u].Wg);
        B[u].x = Com[i].x, B[u].y = Com[i].y;
        if(j1 == cnt)
            S.Insert(Rt[j1], -Inf, 0), S.Insert(Rt[j1], Inf, 0);

        S.Insert(Rt[j1], B[u].Wg, u);
    }

    for(int i = 1; i <= n; ++i) {

        cout << i << " " << B[i].A1 << " " << B[i].A2 << endl;
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
