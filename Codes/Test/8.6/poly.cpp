#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 5;
int a[maxn];

signed main() {

    #define Areka
    #ifdef Areka
        freopen("poly.in", "r", stdin);
        freopen("poly.out", "w", stdout);
    #endif

    int n = read();
    for(int i = 1; i <= n; ++i)
        a[i] = read();
    
    if(n == 1) {
        if(a[1] > 2) {
            cout << a[1] - 2 << endl << 2 << endl << 0 << endl;
        }
        else if(a[1] == 2) {
            cout << 0 << endl << 2 << endl << 0 << endl;
        }
        else {
            cout << 0 << endl << 0 << endl << 1 << endl;
        }
    }

    else if(n == 2) {
        if(a[1] * a[2] == 1)
            cout << "0\n0\n0\n0\n1\n";
        else if(a[1] * a[2] == 2)
            cout << "0\n0\n0\n2\n0\n";
        else if(a[1] * a[2] == 3)
            cout << "0\n0\n1\n2\n0\n";
        else if(a[1] * a[2] == 4) {
            if(a[1] == 1 or a[2] == 1)
                cout << "0\n0\n2\n2\n0\n";
            else
                cout << "0\n4\n0\n0\n0\n";
        }
        else {
            cout << (a[1] - 2) * (a[2] - 2) << endl;
            cout << (a[1] - 2 + a[2] - 2) * 2 << endl;
            cout << 4 << endl;
            cout << "0\n0\n";
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
