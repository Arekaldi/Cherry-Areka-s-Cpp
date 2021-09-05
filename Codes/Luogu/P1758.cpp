#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch = getchar();
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 501;

int f[2][maxn][maxn];
int n, m;
int a[maxn], b[maxn];

signed main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) a[i] = getchar() == 'A' ? 0 : 1;
    cout << endl;
    for(int i = 1; i <= m; ++i) b[i] = getchar() == 'A' ? 0 : 1;
    
    for(int i = 1; i <= n; ++i) cout << a[i] << " ";
    cout << endl;
    for(int j = 1; j <= m; ++j) cout << b[j] << " ";
    
    // int p = l = n, q = r = m;
    for(int i = n; i >= 1; --i) {
        for(int j = m; j >= 1; --j) {
            int I = i & 1;
            for(int k = n; k >= 1; --k) {
                int q = i + j - k;
                if(a[i] == b[k]) f[I][j][k] += f[I ^ 1][j][k + 1];
                if(a[i] == b[q]) f[I][j][k] += f[I ^ 1][j][k];
                // if()
            }
        }
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
