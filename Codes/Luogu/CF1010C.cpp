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

// ssds

int a, g, n, k;
vector <int> v;

bool vis[300001];

signed main() {
    n = read(), k = read();
    
    g = read();
    for(int i = 2; i <= n; ++i)
        g = __gcd(a = read(), g);
    g = __gcd(g, k);

    for(int i = 0; i < k; ++i) {
        int x = (g * i) % k;
        if(!vis[x])
            vis[x] = true, v.push_back(x);
    }
    
    cout << v.size() << endl;
    for(int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
