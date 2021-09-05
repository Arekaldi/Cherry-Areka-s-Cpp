#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 1e6 + 1, Inf = (1 << 30);

class Col {
    public :
        int u, d, l, r;
        bool vis, vis1;
        Col() : u(Inf), d(0), l(Inf), r(0) {}
}C[maxm];

int sum[maxm], ccc[maxm];
int n, m, k, ans, num;

inline int id(int i, int j) {
    return (i - 1) * m + j;
}

inline void Upd(int k) {
    sum[id(C[k].u, C[k].l)]++;
    sum[id(C[k].u, C[k].r + 1)]--;
    sum[id(C[k].d + 1, C[k].l)]--;
    sum[id(C[k].d + 1, C[k].r + 1)]++;
}

signed main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);

    n = read(), m = read(), k = read();

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int col = read();
            if(!C[col].vis1) {
                C[col].vis1 = true;
                num++;
            }
            ccc[id(i, j)] = col;
            C[col].u = min(C[col].u, i);
            C[col].d = max(C[col].d, i);
            C[col].l = min(C[col].l, j);
            C[col].r = max(C[col].r, j);
        }
    }

    if(num == 1) {
        cout << (k == 1 ? 1 : k - 1) << endl;
        return 0;
    }

    for(int i = 1; i <= k; ++i) {
        if(C[i].l == C[i].u and C[i].u == Inf)
            continue;
        Upd(i);
    }
    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            sum[id(i, j)] += sum[id(i - 1, j)] + sum[id(i, j - 1)] - sum[id(i - 1, j - 1)];
            if(sum[id(i, j)] > 1)
                C[ccc[id(i, j)]].vis = true;
        }
    }

    for(int i = 1; i <= k; ++i)
        if(!C[i].vis)
            ans++;

    printf("%d\n", ans);

    // #ifndef ONLINE_JUDGE
    //     getchar();
    // #endif
    return 0;
}