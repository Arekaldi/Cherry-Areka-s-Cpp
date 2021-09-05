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

const int maxn = 1e5 + 1;

double Sn;
int n, m, t, ans;
int a[maxn], b[maxn], pos[maxn], cnt[maxn],
    L[maxn], R[maxn], tot[maxn];

class Ask{
    public :
        int id, l, r;
        int ans;
}Q[maxn];

inline bool Comp1(Ask a, Ask b) {
    return pos[a.l] == pos[b.l] ? a.r < b.r :
        pos[a.l] < pos[b.l];
}

inline bool Comp2(Ask a, Ask b) {
    return a.id < b.id;
}

inline void init() {
    Sn = sqrt(n);
    t = Sn;

    for(int i = 1; i <= t; ++i) 
        L[i] = (i - 1) * Sn + 1, R[i] = i * Sn;
        
    if(R[t] < n) {
        ++t;
        L[t] = R[t - 1] + 1;
        R[t] = n;
	}
    
    for(int i = 1; i <= t; ++i)
        for(int j = L[i]; j <= R[i]; ++j)
            pos[j] = i;
    
}

inline void Add(int &x, int k, int &ans) {
    x += k;
    cnt[a[x]]++;
    ans = max(ans, b[a[x]] * cnt[a[x]]);
}

inline void Del(int &x, int k) {
    cnt[a[x]]--;
    x += k;
}

signed main() {
	n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read(), b[i] = a[i];
    sort(b + 1, b + n + 1);
    int nn = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; ++i)
        a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;
    
    init();

    for(int i = 1; i <= m; ++i)
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;

    sort(Q + 1, Q + m + 1, Comp1);

    int l = 1, r = 0, lst = 0;
    int newans;
    for(int i = 1; i <= m; ++i) {
        if(pos[Q[i].l] == pos[Q[i].r]) {
            int xans = 0;
            for(int j = Q[i].l; j <= Q[i].r; ++j)
                tot[a[j]]++;
            for(int j = Q[i].l; j <= Q[i].r; ++j)
                xans = max(xans, b[a[j]] * tot[a[j]]);
            for(int j = Q[i].l; j <= Q[i].r; ++j)
                tot[a[j]]--;
            Q[i].ans = xans;
            continue;
        }
        if(pos[Q[i].l] != lst) {
            int p = pos[Q[i].l];
            while(r > R[p])
                Del(r, -1);
            while(l < R[p] + 1)
                Del(l, 1);
            lst = pos[Q[i].l];
            ans = 0;
        }
        int newl = l;
        while(r < Q[i].r)
            Add(r, 1, ans);
        newans = ans;
        while(newl > Q[i].l)
            Add(newl, -1, newans);
        while(newl < l)
            Del(newl, 1);
        Q[i].ans = newans;
    }

    sort(Q + 1, Q + m + 1, Comp2);

    for(int i = 1; i <= m; ++i)
        printf("%lld\n", Q[i].ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}