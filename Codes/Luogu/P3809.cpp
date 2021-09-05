#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e6 + 2;

char s[maxn];
int x[maxn];
int n, m;
int c[maxn], sa[maxn];
int y[maxn];

signed main() {
    cin >> (s + 1);
    n = strlen(s + 1);
    m = 122;
    for(int i = 1; i <= n; ++i) x[i] = s[i], ++c[x[i]];
    for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
    for(int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
    for(int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for(int i = n - k + 1; i <= n; ++i) y[++num] = i;
        for(int i = 1; i <= n; ++i) if(sa[i] > k) y[++num] = sa[i] - k;
        memset(c, 0, sizeof(c));
        for(int i = 1; i <= n; ++i) c[x[i]]++;
        for(int i = 2; i <= m; ++i) c[i] += c[i - 1];
        for(int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
        swap(x, y);
        num = 1, x[sa[1]] = 1;
        for(int i = 2; i <= n; ++i)
            if(y[sa[i]] == y[sa[i - 1]] and y[sa[i] + k] == y[sa[i - 1] + k]) x[sa[i]] = num;
            else x[sa[i]] = ++num;
        if(num == n) break; m = num;
    }
    
    for(int i = 1; i <= n; ++i) printf("%d ", sa[i]);
    cout << endl;

    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif

    return 0;
}
