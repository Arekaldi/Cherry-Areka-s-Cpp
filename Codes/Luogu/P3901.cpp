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

class Seg_Ment {

    private :
        int tot = 0;
        struct Node {
            int dat;
            int ls, rs;
            Node() : dat(0), ls(0), rs(0) {}
            #define Ls(p) T[p].ls
            #define Rs(p) T[p].rs
        }T[maxn << 2];

    public :
        int Rt[maxn];
        inline void Upd(int p) {
            T[p].dat = (Ls(p) == 0 ? 0 : T[Ls(p)].dat) + (Rs(p) == 0 ? 0 : T[Rs(p)].dat);
        }
        
        inline int Build(int L, int R) {
            int p = ++tot;
            if(L == R) {
                T[p].dat = 0;
                return p;
            }
            
            int mid = (L + R) >> 1;
            Ls(p) = Build(L, mid), Rs(p) = Build(mid + 1, R);
            T[p].dat = 0;
            Upd(p);
            return p;
        }
        
        inline int Add(int Last, int L, int R, int x) {
            int p = ++tot;
            T[p] = T[Last];
            if(L == R) {
                T[p].dat++;
                return p;
            }
            int mid = (L + R) >> 1;
            if(x <= mid)
                Ls(p) = Add(Ls(p), L, mid, x);
            else
                Rs(p) = Add(Rs(p), mid + 1, R, x);
            Upd(p);
            return p;
        }
        
        inline int Ask(int p, int q, int L, int R, int k) {
            if(L == R)
                return T[p].dat - T[q].dat;
            int mid = (L + R) >> 1;
            if(k <= mid)
                return Ask(T[p].ls, T[q].ls, L, mid, k) + T[Rs(p)].dat - T[Rs(q)].dat;
            else
                return Ask(T[p].rs, T[q].rs, mid + 1, R, k);
        }
}Sg;

int n, a[maxn], nxt[maxn];
int vis[maxn];
int m;

signed main() {
    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();

    for(int i = n; i >= 1; --i) {
        if(vis[a[i]] != 0) nxt[i] = vis[a[i]];
        vis[a[i]] = i;
    }

    for(int i = 1; i <= n; ++i) {
        if(nxt[i] == 0) nxt[i] = n + 1;
        Sg.Rt[i] = Sg.Add(Sg.Rt[i - 1], 1, n + 1, nxt[i]);
    }

    for(int i = 1; i <= m; ++i) {
        int L = read(), R = read();
        int ans = Sg.Ask(Sg.Rt[R], Sg.Rt[L - 1], 1, n + 1, R + 1);
        puts(ans == (R - L + 1) ? "Yes" : "No");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}