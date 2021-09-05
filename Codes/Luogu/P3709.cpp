#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e5 + 1;

int a[maxn], b[maxn];
int n, m, k;
double Sn;

int pos[maxn], cnt[maxn];
int L[maxn], R[maxn];
int t, ans;

class Ask{
    public :
        int id, l, r;
        int ans;
}Q[maxn];

bool Comp1(Ask a, Ask b) {
    return pos[a.l] == pos[b.l] ? ((pos[a.l] & 1) ? pos[a.r] < pos[b.r] : pos[a.r] > pos[b.r]) : (pos[a.l] < pos[b.l]);
}

bool Comp2(Ask a, Ask b) {
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


signed main() {

    #define Areka
    #ifdef Areka
        freopen("1.in", "r", stdin);
        freopen("w.out", "w", stdout);
    #endif

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

    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i) {
        while(l > Q[i].l) {
            l--;
            cnt[a[l]]++;
            if(cnt[a[l]] > 1)
                ans++;
        }
        while(l < Q[i].l) {
            l++;
            cnt[a[l - 1]]--;
            if(cnt[a[l - 1]] > 1)
                ans--;
        }
        while(r < Q[i].r) {
            r++;
            cnt[a[r]]++;
            if(cnt[a[r]] > 1)
                ans++;
        }
        while(r > Q[i].r) {
            r--;
            cnt[a[r + 1]]--;
            if(cnt[a[r + 1]] > 1)
                ans--;
        }
        Q[i].ans = -ans - 1;
    }

    sort(Q + 1, Q + m + 1, Comp2);

    for(int i = 1; i <= m; ++i)
        printf("%d\n", Q[i].ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}