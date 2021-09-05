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

int Sum[maxn], n, m;

signed main() {
    n = read(), m = read();

    for(int i = 1; i <= m; ++i)
        Sum[i] = read();

    sort(Sum + 1, Sum + m + 1);

    for(int i = 1; i <= m; ++i)
        printf("%d ", Sum[i]);
    
    puts("");
    
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
