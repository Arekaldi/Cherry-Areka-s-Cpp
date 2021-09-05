#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 4e4 + 1, maxt = 2e2 + 1;

int n, m;
int a[maxn], b[maxn], c[maxn];

class Town {
    public:
        int id, num;
};

Town t[maxn];

inline bool Camp(Town a, Town b) {
    if(a.num == b.num)
        return a.id < b.id;
    return a.num > b.num;
}

int last = 0;

signed main() {

    // #define Areka
    #ifdef Areka
        freopen("a.txt", "r", stdin);
        freopen("w.txt", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; ++i)
        a[i] = read(), c[i] = a[i];

    sort(a + 1, a + n + 1);

    int n1 = unique(a + 1, a + n + 1) - a - 1;

    for(int i = 1; i <= n; ++i)
        b[i] = lower_bound(a + 1, a + n1 + 1, c[i]) - a;
    
    swap(a, b);

    for(int i = 1; i <= m; ++i) {
        int l = read(), r = read();

        l = ((l + last - 1) % n) + 1, r = ((r + last - 1) % n) + 1;

        if(l > r)
            swap(l, r);

        memset(t, 0, sizeof(t));

        for(int i = l; i <= r; ++i)
            t[a[i]].id = a[i], t[a[i]].num++;

        int maxx = 0;
        for(int j = 1; j <= n; ++j)
            if(t[j].num > maxx)
                maxx = t[j].num, last = b[t[j].id];

        printf("%d\n", last);
    }

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
