#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

signed main() {
    // for(int fa = 0; ;fa = a[fa]) {
    //     if(fa == -1) break;
    //     cout << fa << endl;
    // }

    for(int fa = 0;fa = a[fa];) {
        cout << fa << endl;
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
