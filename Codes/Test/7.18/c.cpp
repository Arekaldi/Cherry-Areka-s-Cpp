#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e5 + 1;

int n, m;
int st[maxn], top;
int L[maxn], R[maxn];



class Tree_Array {
    int t[maxn];
    private:
        inline int lowbit(int x) {
            return x & -x;
        }
    public:
        inline void Add(int pos, int v) {
            while(pos <= n) {
                t[pos] += v;
                pos += lowbit(pos);
            }
        }
        inline int Ask(int pos) {
            int ans = 0;  
            while(pos) {
                ans += t[pos];
                pos -= lowbit(pos);
            }
            return ans;
        }
}Ans, T;

class Segment_Tree {
    private:
        set <int> s[maxn << 2];
        set <int> :: iterator it;
    public:
        inline void Insert(int p, int l, int r, int x, int y, int v) {
            if(x <= l and r <= y) {
                s[p].insert(v);
                return;
            }
            int mid = (l + r) >> 1;
            int ls = p << 1, rs = (p << 1 | 1);
            if(x <= mid)
                Insert(ls, l, mid, x, y, v);
            if(mid + 1 <= y)
                Insert(rs, mid + 1, r, x, y, v);
            return;
        }

        inline void Upd(int p, int l, int r, int pos) {
            for(it = s[p].begin(); it != s[p].end(); ++it)
                st[++top] = *it;
            if(l == r)
                return;
            int mid = (l + r) >> 1;
            int ls = p << 1, rs = (p << 1 | 1);
            if(pos <= mid)
                Upd(ls, l, mid, pos);
            else
                Upd(rs, mid + 1, r, pos);
            return;
        }

        inline void Del(int p, int l, int r, int x, int y, int v) {
            if(x <= l and r <= y) {
                s[p].erase(v);
                return;
            }
            int mid = (l + r) >> 1;
            int ls = (p << 1), rs = (p << 1 | 1);
            if(x <= mid)
                Del(ls, l, mid, x, y, v);
            if(mid + 1 <= y)
                Del(rs, mid + 1, r, x, y, v);
            return;
        }
}S;

signed main() {
    // #define Areka
    #ifdef Areka
        freopen("c.in", "r", stdin);
        freopen("c.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; ++i) {
        Ans.Add(i, 1), S.Insert(1, 1, n, 1, i, i);
        L[i] = 1, R[i] = i;
    }
    
    for(int i = 1; i <= m; ++i) {
        int opt = read();
        if(opt == 2) {
            int L = read(), R = read();
            int ans = Ans.Ask(R) - Ans.Ask(L - 1);
            printf("%d\n", ans);
        }
        if(opt == 1) {
            int h = read();
            top = 0;
            S.Upd(1, 1, n, h);
            T.Add(h, 1);
            int v, l, r;
            for(int i = 1; i <= top; ++i) {
                v = st[i];
                S.Del(1, 1, n, L[v], R[v], v);
                l = L[v], r = R[v];
                while(true) {
                    if(T.Ask(r) - T.Ask(l - 1))
                        Ans.Add(v, 1);
                    else {
                        L[v] = l, R[v] = r;
                        S.Insert(1, 1, n, l, r, v);
                        break;
                    }
                    l = r + 1, r = min(n, l + v - 1);
                    if(l == n + 1)
                        break;
                }
            }
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}