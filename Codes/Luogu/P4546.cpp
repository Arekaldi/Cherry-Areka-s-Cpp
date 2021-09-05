#include <bits/stdc++.h>

using namespace std;

#define Re register

const int maxn = 1000010;
int Rt, tot;
queue <int> qv;
int st[maxn];

class Node {
    public:
        int Type;
        double a, b;
        inline double Get_ans(double x) {
            if(Type == 1)
                return a * x + b;
            else if(Type == 2)
                return 0;
            else
                return 0;
        }
}v[maxn];

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

        inline void Push_up(int p) {
            T[p].ans = T[T[p].ch[0]].ans + T[T[p].ch[1]].ans + v[p].Get_ans(1);
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
        }

        inline void Rotate(int x) {
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
string Type;
const int Max = 0x7f7f7f7f, Min = -0x7f7f7f7f;

signed main() {
    n = read(), m = read();
    scanf("%s", Type);

    for(int i = 1; i <= n; ++i) {
        v[i].Type = read();
        scanf("%lf%lf", &v[i].a, v[i].b);
    }

    for(int i = 1; i <= m; ++i) {
        string opt;
        scanf("%s", opt);
        if(opt == "appear") {
            int x = read(), y = read();
            Lct :: Link(x, y);
        }
        else if(opt == "disappear") {
            int x = read(), y = read();
            Lct :: Cut(x, y);
        }
        else if(opt == "magic") {
            int c = read(), f = read();
            double a, b;
            scanf("%lf%lf", &a, &b);
            v[c].Type = f, v[c].a = a, v[c].b = b;
        }
        else {
            int u = read(), v = read();
            double x;
            scanf("%lf", &x);
            int Rtu = Lct :: Find_Root(u), Rtv = Lct :: Find_Root(v);
            if(Rtu != Rtv)
                puts("unreachable");
            else {
                
            }
        }
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
