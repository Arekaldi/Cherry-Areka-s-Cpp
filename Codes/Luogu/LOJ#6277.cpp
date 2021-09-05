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

const int maxn = 1e5 + 10, Sn = 1e5 + 10;
double st;

int a[maxn], add[maxn];
int L[Sn], R[Sn],pos[maxn];
int m, n, t;

void Change(int l, int r, int d) {
    int p = pos[l], q = pos[r];
    if(p == q) {
        for(int i = l; i <= r; ++i)
            a[i] += d;
        return;
    }
    for(int i = p + 1; i <= q - 1; ++i)
        add[i] += d;
    for(int i = l; i <= R[p]; ++i)
        a[i] += d;
    for(int i = L[q]; i <= r; ++i)
        a[i] += d;
    return;
}

int Ask(int r) {
    return a[r] + add[pos[r]];
}

signed main() {
    n = read(), m = read();

    st = sqrt(n);
    
    for(int i = 1; i <= n; ++i) a[i] = read();

    t = st;

    for(int i = 1; i <= t; ++i) 
        L[i] = (i - 1) * st + 1, R[i] = i * st;
    
    if(R[t] < n) t++, L[t] = R[t - 1] + 1, R[t] = n;

    for(int i = 1; i <= t; ++i) 
        for(int j = L[i]; j <= R[i]; ++j)
            pos[j] = i;
    
    for(int i = 1; i <= m; ++i) {
        int opt = read(), l = read(), r = read(), c = read();
        if(opt == 1) {
            int x = Ask(r); cout << x << endl;
        }
        else {
            Change(l, r, c);
            for(int i = 1; i <= n; ++i) {
                cout << a[i] + add[pos[i]] << endl;
            }
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
