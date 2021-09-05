#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

signed main() {

    #define Areka
    #ifdef Areka
    freopen("1.txt", "w", stdout);
    #endif

    srand(time(0));

    int n = 10, m = rand() % 10 + 1;
    
    printf("%d %d\n", n, m);
    for(int i = 1; i <= n; ++i)
        printf("%d ", rand());
    puts("");
    
    return 0;
}
