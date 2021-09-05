#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

double m, s, t, x;

signed main() {
    scanf("%lf%lf%lf", &m, &t, &s);

    if(t == 0) {
        puts("0");
        goto Areka;
    }

    x = ceil((s / t));

    printf("%d\n", m - x < 0 ? 0 : (int)(m - x));
    
    Areka :
        #ifndef ONLINE_JUDGE
            getchar();
        #endif
        return 0;
}
