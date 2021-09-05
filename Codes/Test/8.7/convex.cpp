#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 3e2 + 1;

class Node {
    public:
        int x, y;
        inline bool operator < (const Node &a) const {
            return y == a.y ? x < a.x : y < a.y;
        }
};

Node a[maxn];

int s[maxn], head, tail, n, ans;

map < pair<int, int>, int > M;

vector < pair<int, int> > v[maxn];

signed main() {

    #define Areka
    #ifdef Areka
        freopen("convex.in", "r", stdin);
        freopen("convex.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; ++i)
        a[i].x = read(), a[i].y = read();

    sort(a + 1, a + n + 1);
    
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            int k;
            if(a[i].x == a[j].x)
                k = 0;
            else 
                k = (a[i].y - a[j].y) / (a[i].x - a[j].x);
            int b = a[i].y - k * a[i].x;
            if(M[make_pair(k, b)] != 0)
                continue;
            v[i].push_back(make_pair(k, b)), v[j].push_back(make_pair(k, b));
            int res = 2;
            for(int p = 1; p <= n; ++p) {
                if(p == i or p == j)
                    continue;
                if(a[p].x * k == a[p].y)
                    res++, v[p].push_back(make_pair(k, b));
            }
            M[make_pair(k, b)] = res;
        }
    }

    cout << n << endl;

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}