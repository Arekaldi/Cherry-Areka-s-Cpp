#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int k;
int F[42];

signed main() {
    k = read();
    F[1] = 1, F[2] = 1;
    for(int i = 3; i <= 41; ++i)
        F[i] = F[i - 1] + F[i - 2];
    
    cout << F[k] << " " << F[k + 1] << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
