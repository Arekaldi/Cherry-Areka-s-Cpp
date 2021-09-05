#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 25, Mod = 1e9 + 7;

int n, m, a[maxn], dis[1 << maxn], f[1 << maxn];
int bad_a, bad_b;
inline void Dfs(int x, int now, int now_dis) {
    if(dis[now])
        return;
    if(x == n) {
        dis[now] = now_dis;
        return;
    }
    Dfs(x + 1, now | (1 << x), now_dis + a[x + 1]);
    Dfs(x + 1, now, now_dis);
}

inline int lowbit(int x) {
    return x & (-x);
}

inline int Count(int n) {
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
    return n;
}

char ch[26];
inline void Zhuan(int x) {
    int tot = 0;
    while(x)
        ch[++tot] = (x & 1) + '0', x >>= 1;
    for(int i = tot; i >= 1; --i)
        cout << ch[i];
    if(tot == 0)
        cout << "0";
}

signed main() {
    n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read(), dis[1 << (i - 1)] = a[i];
    m = read();
    for(int i = 1; i <= m; ++i)
        if(i & 1)
            bad_a = read();
        else
            bad_b = read();
    
    // Dfs(0, 0, 0);

    f[0] = 1;
    for(int j = 1; j < (1 << n); ++j) {
        dis[j] = dis[j - lowbit(j)] + dis[lowbit(j)];
        // Zhuan(j), cout << " " << dis[j] << endl;
        if(dis[j] == bad_a or dis[j] == bad_b)
            continue;
        int p = j;
        while(p) {
            int now = j - lowbit(p);
            // if(dis[now] != bad_a and dis[now] != bad_b)
                f[j] = (f[j] + f[now]) % Mod;
            p -= lowbit(p);
        }
    }
    
    cout << f[(1 << n) - 1] << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}