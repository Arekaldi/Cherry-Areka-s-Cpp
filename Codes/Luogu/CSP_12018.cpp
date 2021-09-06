#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n, d[101], res;
bool v[101];

signed main() {
    n = read();
    for(int i = 0; i < n; ++i) {
        scanf("%d", d + i);
        v[i] = false;
    }
    for(int i = 0; i < n; ++i)
        cout << d[i] << " ";
    cout << endl;
    for(int i = 0; i < n; ++i) {
        if(!v[i]) {
            for(int j = i; !v[j]; j = d[j])
                v[j] = true;
            res++;
        }
    }
    
    cout << res;
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
