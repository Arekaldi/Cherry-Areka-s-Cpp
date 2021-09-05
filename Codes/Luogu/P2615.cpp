#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 40;

int n, a[maxn][maxn];
pair <int, int> pos[maxn * maxn];

signed main() {
    n = read();
    a[1][(n >> 1) + 1] = 1;
    pos[1] = make_pair(1, (n >> 1) + 1);

    for(int i = 2; i <= n * n; ++i) {
        int x = pos[i - 1].first, y = pos[i - 1].second;
        if(x == 1 and y != n) {
            a[n][y + 1] = i;
            pos[i] = make_pair(n, y + 1);
        }
        if(x != 1 and y == n) {
            a[x - 1][1] = i;
            pos[i] = make_pair(x - 1, 1);
        }
        if(x == 1 and y == n) {
            a[2][n] = i;
            pos[i] = make_pair(2, n);
        }
        if(x != 1 and y != n) {
            if(a[x - 1][y + 1] == 0)
                a[x - 1][y + 1] = i, pos[i] = make_pair(x - 1, y + 1);
            else
                a[x + 1][y] = i, pos[i] = make_pair(x + 1, y);
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            printf("%d ", a[i][j]);
        puts("");
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
