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

const int maxn = 1e6 + 1;

int a[maxn], k;

signed main() {
    a[1] = read(), a[2] = read(), k = read();

    if(k <= 2) {
        cout << a[k] << endl;
        return 0;
    }
    
    for(int i = 3; i <= k; ++i)
        a[i] = (a[i - 1] * a[i - 2]) % 10;
    cout << a[k];
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
