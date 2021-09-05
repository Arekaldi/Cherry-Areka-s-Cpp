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

int n;
int x;
int tot1, tot2;

signed main() {
    n = read();
    
    for(int i = 1; i <= n; ++i) {
        x = read();
        if(x % 4 == 0)
            tot1++;
        if(x % 2 == 0)
            tot2++;
    }
    
    if(n - (tot2 >> 1) <= tot1)
        puts("Yes");
    else
        puts("No");

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
