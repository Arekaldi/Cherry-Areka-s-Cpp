#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

#define Rint register int

const int maxn = 1e6 + 1, maxM = 1e6 + 1;

int n, m, r;

int head[maxn], tot;
class Edge {
    public :
        int to, nxt;
}E[maxM];

inline void Add_edge(int u, int v) {
    E[++tot].to = v, E[tot].nxt = head[u];
    head[u] = tot;
}

int a[maxn];

class Cut_Tree {
    private :
        class Tree {
            public :
                int l, r;
                int Mark, sum;
            #define Ls p << 1
            #define Rs p << 1 | 1
        }T[maxn << 2];

        class Point {
            public :
                int Fa, dep, sz, Ms, id, top;
        }P[maxn];
        int cnt = 0;
        int Wei[maxn];

        inline void Upd(int p) {
            T[p].sum = T[Ls].sum + T[Rs].sum;
        }

        inline void Spread(int p) {
            T[Ls].sum += T[p].Mark * (T[Ls].r - T[Ls].l + 1);
            T[Rs].sum += T[p].Mark * (T[Rs].r - T[Rs].l + 1);
            T[Ls].Mark += T[p].Mark;
            T[Rs].Mark += T[p].Mark;
            T[p].Mark = 0;
        }

        inline void Add(int p, int L, int R, int k) {
            if(T[p].l >= L and T[p].r <= R) {
                T[p].sum += k * (T[p].r - T[p].l + 1);
                T[p].Mark += k;
                return;
            }
            Spread(p);
            int mid = (T[p].l + T[p].r) >> 1;
            if(L <= mid)
                Add(Ls, L, R, k);
            if(R > mid)
                Add(Rs, L, R, k);
            Upd(p);
            return;
        }

        inline int Ask(int p, int L, int R) {
            if(T[p].l >= L and T[p].r <= R) 
                return T[p].sum;
            
            Spread(p);
            int mid = (T[p].l + T[p].r) >> 1;
            int ans = 0;
            if(L <= mid)
                ans += Ask(Ls, L, R);
            if(R > mid)
                ans += Ask(Rs, L, R);
            return ans;
        }


    public :
    
        inline void Build(int p, int L, int R) {
            T[p].l = L, T[p].r = R;
            if(L == R) {
                T[p].sum = Wei[L];
                T[p].Mark = 0;
                return;
            }
            int mid = (L + R) >> 1;
            Build(Ls, L, mid);
            Build(Rs, mid + 1, R);
            Upd(p);
            return;
        }

        inline void Dfs1(int x, int Fa, int dep) {
            P[x].dep = dep, P[x].Fa = Fa, P[x].sz = 1;
            int Ms1 = -1;
            for(Rint i = head[x]; i; i = E[i].nxt) {
                int y = E[i].to;
                if(y == Fa) continue;
                Dfs1(y, x, dep + 1);
                P[x].sz += P[y].sz;
                if(P[y].sz > Ms1) P[x].Ms = y, Ms1 = P[y].sz;
            }
        }

        inline void Dfs2(int x, int Top) {
            P[x].id = ++cnt;
            Wei[cnt] = a[x];
            P[x].top = Top;
            if(!P[x].Ms)
                return;
            Dfs2(P[x].Ms, Top);
            for(Rint i = head[x]; i; i = E[i].nxt) {
                int y = E[i].to;
                if(y == P[x].Fa or y == P[x].Ms)
                    continue;
                Dfs2(y, y);
            }
        }

        inline int Askrange(int x, int y) {
            int ans = 0;
            while(P[x].top != P[y].top) {
                if(P[P[x].top].dep < P[P[y].top].dep)
                    swap(x, y);
                ans += Ask(1, P[P[x].top].id, P[x].id);
                x = P[P[x].top].Fa;
            }

            if(P[x].dep > P[y].dep)
                swap(x, y);
            ans += Ask(1, P[x].id, P[y].id);
            return ans;
        }

        inline void Addrange(int x, int y, int k) {
            while(P[x].top != P[y].top) {
                if(P[P[x].top].dep < P[P[y].top].dep)
                    swap(x, y);
                Add(1, P[P[x].top].id, P[x].id, k);
                x = P[P[x].top].Fa;
            }
            if(P[x].dep > P[y].dep)
                swap(x, y);
            Add(1, P[x].id, P[y].id, k);
        }

        inline void Addson(int x, int k) {
            Add(1, P[x].id, P[x].id + P[x].sz - 1, k);
        }

        inline int Askson(int x) {
            return Ask(1, P[x].id, P[x].id + P[x].sz - 1);
        }
}S;

signed main() {

    n = read(), m = read(), r = 1;
    for(Rint i = 1; i <= n; ++i) a[i] = read();
    for(Rint i = 1; i < n; ++i) {
        int a = read(), b = read();
        Add_edge(a, b), Add_edge(b, a);
    }

    S.Dfs1(r, 0 ,1), S.Dfs2(r, r);
    S.Build(1, 1, n);

    for(int i = 1; i <= m; ++i) {
        int k = read();
        switch(k) {
            case 1 : {
                int x = read(), z = read();
                S.Addrange(x, x, z);
                break;
            }
            case 2 : {
                int x = read(), y = read();
                S.Addson(x, y);
                break;
            }
            default : {
                int x = read();
                printf("%lld\n", S.Askrange(x, r));
            }
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
