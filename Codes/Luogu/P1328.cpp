#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 2e2 + 1;

int Winner[5][5] = {
    {0, -1, 1, 1, -1},
    {1, 0, -1, 1, -1},
    {-1, 1, 0, -1, 1},
    {-1, -1, 1, 0, 1},
    {1 ,1, -1, -1, 0}
};

int a[maxn], b[maxn];
int sa, sb;

signed main() {
    int n = read(), na = read(), nb = read();
    for(int i = 1; i <= na; ++i)
        a[i] = read();
    for(int i = 1; i <= nb; ++i)
        b[i] = read();
    
    int p1 = 1, p2 = 1;
    for(int i = 1; i <= n; ++i) {
        int ss = Winner[a[p1]][b[p2]];
        if(ss < 0)
            sb++;
        else if(ss != 0)
            sa++;
        p1 = p1 % na + 1, p2 = p2 % nb + 1;
    }
    
    cout << sa << " " << sb << endl;
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
