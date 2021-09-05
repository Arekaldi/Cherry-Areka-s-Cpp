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
                int ch[2], sz;
                int Fa, cnt, dat;
                int ans;
                bool laz;
        }T[maxn];


        inline bool Get(int p) {
            return T[T[p].Fa].ch[1] == p;
        }

        inline void Push_up(int p) {
            T[p].ans = T[T[p].ch[0]].ans ^ T[T[p].ch[1]].ans ^ v[p];
            T[p].sz = T[T[p].ch[0]].sz + T[T[p].ch[1]].sz + 1;
            return;
        }
        inline bool is_Root(int p) {
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
        }

        inline void Rotate(int x) {
			int y = T[x].Fa, z = T[y].Fa;
            bool k = Get(x);
            if(!is_Root(y))
                T[z].ch[T[z].ch[1] == y] = x;
            T[y].ch[k] = T[x].ch[!k], T[T[x].ch[!k]].Fa = y;
            T[x].ch[!k] = y, T[y].Fa = x, T[x].Fa = z;
            Push_up(y), Push_up(x);
            return;
        }

        inline void Splay(int x) {
            int y = x, top = 0, z;
            st[++top] = y;

            while(Son_Root(y))
                y = T[y].Fa, st[++top] = y;
            while(top)
                Push_down(st[top--]);

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

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}