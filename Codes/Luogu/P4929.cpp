#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int n, m, cnt;

class Point {
    public :
        int l, r, u, d, col, row;
        Point() : l(0), r(0), u(0), d(0), col(0), row(0) {}
}P[maxn];
int h[maxn], s[maxn];
int ans;
bool use[maxn];

class Dincing_Lines {
    public :
        inline void init(int y) {
            for(int i = 0; i <= y; ++i) {
                P[i].r = i + 1, P[i].l = i - 1;
                P[i].u = P[i].d = i;
            }
            P[m].r = 0, P[0].l = m;
            memset(h, -1, sizeof(h));
            memset(s, 0, sizeof(s));
            cnt = m + 1;
            return;
        }

        inline void Add(int r, int c) {
            s[c]++;
            P[cnt].row = r, P[cnt].col = c;
            P[cnt].u = c, P[cnt].d = P[c].d;
            P[P[c].d].u = cnt;
            P[c].d = cnt;
            if(h[r] < 0)
                h[r] = P[cnt].r = P[cnt].l = cnt;
            else {
                P[cnt].r = h[r];
                P[cnt].l = P[h[r]].l;
                P[P[h[r]].l].r = cnt;
                P[h[r]].l = cnt;
            }
            cnt++;
            return;
        }

        inline void Del(int c) {
            P[P[c].l].r = P[c].r, P[P[c].r].l = P[c].l;
            for(int i = P[c].d; i != c; i = P[i].d) 
                for(int j = P[i].r; j != i; j = P[j].r)
                    P[P[j].d].u = P[j].u, P[P[j].u].d = P[j].d, s[P[j].col]--;

            return;
        }

        inline void Rec(int c) {
            for(int i = P[c].u; i != c; i = P[i].u) 
                for(int j = P[i].l; j != i; j = P[j].l)
                    P[P[j].d].u = P[P[j].u].d = j, s[P[j].col]++;
            P[P[c].l].r = P[P[c].r].l = c;
            return;
        }

        inline bool Dance(int dep) {
            if(P[0].r == 0) 
                return true;

            int c = P[0].r;
            for(int i = P[0].r; i != 0; i = P[i].r) 
                if(s[i] < s[c])
                    c = i;
            Del(c);

            for(int i = P[c].d; i != c; i = P[i].d) {
                use[P[i].row] = true;
                for(int j = P[i].r; j != i; j = P[j].r)
                    Del(P[j].col);
                if(Dance(dep + 1)) return 1;
                for(int j = P[i].l; j != i; j = P[j].l)
                    Rec(P[j].col);
                use[P[i].row] = false;
            }

            Rec(c);
            return false;
        }
}D;

signed main() {
    n = read(), m = read();

    D.init(m);

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int opt = read();
            if(opt)
                D.Add(i, j);
        }

    if(!D.Dance(0))
        printf("No Solution!");
    
    else
        for(int i = 1; i <= n; ++i)
            if(use[i])
                printf("%d ", i);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
