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

class Node {
    public:
        int hse;
        string s;
        inline bool operator < (const Node &g) const {
            return g.hse > hse;
        }
};

Node a[maxn];

const int Mod = 998244353, p = 133;

inline int Get_Hs(string s) {
    int ans = 0;
    for(int i = 0; s[i]; ++i)
        ans = (ans * p + (s[i] + p)) % Mod;
    return ans;
}

signed main() {
    int n = read();
    for(int i = 1; i <= n; ++i)
        cin >> a[i].s, a[i].hse = Get_Hs(a[i].s);
    sort(a + 1, a + n + 1);
    int res = 0;
    for(int i = 1; i <= n; ++i)
        if(a[i].hse != a[i - 1].hse)
            res++;
    cout << res;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
