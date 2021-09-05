#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxn = 1e6 + 1;
const int N = maxn << 1;

class Equal {
    public:
        int l, r;
};

Equal q[maxn];
int n, tot;

class Tree_Array {
    private:
        int t[N];
        inline int lowbit(int x) {
            return x & (-x);
        }
    public:

        inline void Add(int pos, int v) {
            pos += maxn + 1;
            while(pos <= N) {
                t[pos] += v;
                pos += lowbit(pos);
            }
        }

        inline int Ask(int pos) {
            pos += maxn + 1;
            int ans = 0;
            while(pos) {
                ans += t[pos];
                pos -= lowbit(pos);
            }
            return ans;
        }
};

Tree_Array T;
bool deled[maxn];

signed main() {
    // freopen("1.txt", "r", stdin);
    // freopen("a.txt", "w", stdout);

    n = read();
    for(int i = 1; i <= n; ++i) {
        string opt;
        cin >> opt;
        if(opt == "Add") {
            int a = read(), b = read(), c = read();
            double x = a * 1.0, y = b * 1.0, z = c * 1.0;
            int l, r;
            double W = (z - y) / x;
            if(a > 0) {
                if((c - b) % a) {
                    if((c - b) / a < 0)
                        l = W;
                    else if((c - b) / a != 0)
                        l = ceil(W);
                    else
                        l = 1;
                }
                else
                    l = (W) + 1;
                if(l < -maxn)
                    l = -maxn;
                r = maxn;
            }
            else if(a != 0) {
                if((c - b) % a) {
                    if((c - b) / a < 0)
                        r = floor(W);
                    else if((c - b) / a != 0)
                        r = W;
                    else
                        r = -1;
                }
                else
                    r = W - 1;
                if(r > maxn)
                    r = maxn;
                l = -maxn;
            }
            else {
                if(b > c)
                    l = -maxn, r = maxn;
                else
                    l = r = maxn + 1;
            }



            q[++tot].l = l, q[tot].r = r;

            if((l == r and r == maxn + 1))
                continue;
            if(l > r or r < l)
                continue;
            T.Add(l, 1), T.Add(r + 1, -1);

        }

        if(opt == "Query") {
            int pos = read();
            
            printf("%d\n", T.Ask(pos));
        }

        if(opt == "Del") {
            int p = read();
            if(deled[p])
                continue;
            deled[p] = true;
            int l = q[p].l, r = q[p].r;
            if((l == r and r == maxn + 1))
                continue;
            if(l > r or r < l)
                continue;
            T.Add(l, -1), T.Add(r + 1, 1);
        }
    }
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}
