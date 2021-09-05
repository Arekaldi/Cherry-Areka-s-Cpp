#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

int n = 6, m = 10;

signed main() {

    #define Areka
    #ifdef Areka
        // freopen("", "r", stdin);
        freopen("1.txt", "w", stdout);
    #endif

    srand(time(0));

    printf("%d %d\n", n, m);

    for(int i = 1; i <= n; ++i)
        printf("%d ", rand());
    puts("");
    
    for(int i = 1; i <= m; ++i) {
        int opt = rand() % 3 + 1;
        cout << opt << " ";
        if(opt == 2) {
            cout << (rand() % i) << endl;
        }
        else 
            cout << (rand() % n + 1) << " " << (rand() % n + 1) << endl;
    }
    
    return 0;
}
