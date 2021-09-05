#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;

int f[maxn], S[maxn], Q[maxn];
int head, tail;
int n, m;

inline double b(int x) {
    return -S[x] - S[x] * S[x];
}

inline double X(int x) {
    return S[x];
}

inline double Y(int x) {
    return S[x] * S[x] - 2 * S[x] + f[x];
}

inline double K(int x, int y) {
    return (Y(x) - Y(y)) / (X(x) - X(y));
}

int p[maxn];

inline bool check(int mid) {
    memset(f, 0x7f, sizeof(f));
    memset(p, 0, sizeof(p));
    f[0] = 0;
    head = tail = 1;
    for(int i = 1; i <= n; ++i) {
        while(K(Q[head], Q[head + 1]) < S[i] * 2 and head < tail)
            head++;
        int j = Q[head];
        p[i] = p[j] + 1;
        f[i] = f[j] + (S[i] - S[j] + 1) * (S[i] - S[j] + 1) + mid;
        while(K(Q[tail - 1], Q[tail]) > K(Q[tail - 1], i) and head < tail)
            tail--;
        Q[++tail] = i;
    }
    return p[n] > m;
}

signed main() {
    n = read(), m = read();

    for(int i = 1, x; i <= n; ++i)
        S[i] = S[i - 1] + (x = read());
    
    int l = 0, r = 1e18, ans;

    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid))
            l = mid + 1;
        else
            r = mid - 1, ans = mid;
    }

    check(ans);

    cout << f[n] - ans * m << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
