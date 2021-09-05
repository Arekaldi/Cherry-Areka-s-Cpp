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

signed main() {
    // 20021231
    int n = read();
    
    for(int i = 1; i <= n; ++i) {
        int x = i;
        if(x * ((x & -x) + ((x - (x & -x)) & -(x - (x & -x)))) == 1463030063184) {
            cout << x << endl;
            system("pause");
        }
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}