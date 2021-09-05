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

const int maxn = 5e5 + 1;

namespace Left_More_Tree {
    class Tree {
        public:
            int val, dis, ls, rs, fa;
            int ml, ad;
            Tree() {
                val = dis = ls = rs = 0;
            }
    };
    Tree T[maxn];

    inline void PushDn(int x) {
        if(T[x].ml == 1 and T[x].ad == 0)
            return;
        int m = T[x].ml, a = T[x].ad;
        int ls = T[x].ls, rs = T[x].rs;
        if(ls) {
            T[ls].ml *= m, T[ls].ad = T[ls].ad * m + a;
            T[ls].val = (T[ls].val * m + a);
        }
        if(rs) {
            T[rs].ml *= m, T[rs].ad = T[rs].ad * m + a;
            T[rs].val = (T[rs].val * m + a);
        }
        T[x].ml = 1, T[x].ad = 0;
        return;
    }

    inline int Find(int x) {
        return T[x].fa == x ? x : T[x].fa = Find(T[x].fa);
    }

    inline int Merge(int x, int y) {
        if(!x or !y)
            return x | y;
        PushDn(x), PushDn(y);
        if(T[x].val > T[y].val or (T[x].val == T[y].val and x > y))
            swap(x, y);
        T[x].rs = Merge(T[x].rs, y);
        if(T[T[x].ls].dis < T[T[x].rs].dis)
            swap(T[x].ls, T[x].rs);
        T[T[x].ls].fa = T[T[x].rs].fa = T[x].fa = x;
        T[x].dis = T[T[x].rs].dis + 1;
        return x;
    }

    inline void Delete(int x) {
        T[x].val = -1;
        PushDn(x);
        T[T[x].ls].fa = T[x].ls, T[T[x].rs].fa = T[x].rs;
        T[x].fa = Merge(T[x].ls, T[x].rs);
    }
}
using namespace Left_More_Tree;

int n, m;

int dep[maxn], fa[maxn], v[maxn],
    ad[maxn], ml[maxn], str[maxn],
    rt[maxn], ans1[maxn], ans2[maxn];

signed main() {
    // #define Areka
    #ifdef Areka
        freopen("data.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif

    T[0].val = 0, T[0].dis = -1;
    dep[1] = 1, fa[1] = 1;
    
    n = read(), m = read();
    for(int i = 1; i <= n; ++i)
        v[i] = read(), rt[i] = -1;

    for(int i = 2; i <= n; ++i)
        fa[i] = read(), ad[i] = read(),
        ml[i] = read(), dep[i] = dep[fa[i]] + 1;

    for(int i = 1; i <= m; ++i) {
        T[i].val = read(), str[i] = read();
        if(rt[str[i]] == -1)
            rt[str[i]] = i;
        else
            rt[str[i]] = Merge(rt[str[i]], i);
    }

    for(int i = n; i >= 1; --i) {
        while(rt[i] != -1) {
            if(T[rt[i]].val < v[i]) {
                ans1[rt[i]] = i;
                PushDn(rt[i]);
                if(!T[rt[i]].ls)
                    rt[i] = -1;
                else
                    rt[i] = Merge(T[rt[i]].ls, T[rt[i]].rs);
            }
            else
                break;
        }
        if(i == 1)
            break;
        if(rt[i] == -1)
            continue;
        
        if(ad[i] == 1)
            T[rt[i]].ml *= ml[i], T[rt[i]].ad *= ml[i], T[rt[i]].val *= ml[i];
        else
            T[rt[i]].ad += ml[i], T[rt[i]].val += ml[i];
        
        PushDn(rt[i]);
        if(rt[fa[i]] == -1)
            rt[fa[i]] = rt[i];
        else
            rt[fa[i]] = Merge(rt[i], rt[fa[i]]);
    }

    for(int i = 1; i <= m; ++i)
        ans2[ans1[i]]++;
    for(int i = 1; i <= n; ++i)
        printf("%lld\n", ans2[i]);
    
    for(int i = 1; i <= m; ++i)
        printf("%lld\n", dep[str[i]] - dep[ans1[i]]);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
