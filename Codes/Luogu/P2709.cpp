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

const int maxn = 5e4 + 1;

int a[maxn];
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
	n = read(), m = read(), k = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read();
    init();

    for(int i = 1; i <= m; ++i)
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;

    sort(Q + 1, Q + m + 1, Comp1);

    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i) {
        while(l > Q[i].l) {
            l--;
            cnt[a[l]]++;
            ans += 2 * cnt[a[l]] - 1;
        }
        while(l < Q[i].l) {
            l++;
            cnt[a[l - 1]]--;
            ans -= 2 * cnt[a[l - 1]] + 1;
        }
        while(r < Q[i].r) {
            r++;
            cnt[a[r]]++;
            ans += 2 * cnt[a[r]] - 1;
        }
        while(r > Q[i].r) {
            r--;
            cnt[a[r + 1]]--;
            ans -= 2 * cnt[a[r + 1]] + 1;
        }
        Q[i].ans = ans;
    }

    sort(Q + 1, Q + m + 1, Comp2);

    for(int i = 1; i <= m; ++i)
        printf("%d\n", Q[i].ans);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}